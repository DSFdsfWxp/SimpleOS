
#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "simpleos.h"
#include "keyScanD.h"
#include "config.h"
#include "util.h"

void keyScanD::start()
{
    Serial.println("hello keyScanD !");

    this->isPress = 0x0;
    this->scanTick = 50;
    this->checkPressTick = 25;
    this->holdTick = 14;
    this->comboTick = 3;
    this->scanClockResetCount = 0;
    this->scanClock = 0x0;
    this->mode = 0;
    this->comboCount = 32767;
    this->eventRaiseTick = 0;

    TaskHandle_t tmp = NULL;
    xTaskCreate(&(this->keyScanTask), "", scanKeyDaemonTaskStackSize, (void *)(this), scanKeyDaemonTaskPriority, &tmp);
    this->task = tmp;
    attachInterruptArg(scanKeyISR_IOPort, &(scanKeyD_isr), (void *)(this), CHANGE);
}

keyScanD::~keyScanD()
{
    Serial.println("goodbye keyScanD !");
    vTaskDelete(this->task);
    detachInterrupt(scanKeyISR_IOPort);
}

void IRAM_ATTR scanKeyD_isr(void *ptr)
{
    keyScanD *p = (keyScanD *)(ptr);
    if (p->scanClockResetCount >= 0)
    {
        return;
    }
    vTaskResume(p->task);
    p->scanClockResetCount = 0;
}

void keyScanD::keyScanTask(void *args)
{
    keyScanD *p = (keyScanD *)(args);
    while (true)
    {
        p->scanKey();
        p->scanClockTick();
        delay(p->scanTick);
    }
}

void keyScanD::scanKey()
{
    byte a = this->isPress;
    this->scanKey_hal();
    byte b = this->isPress;
    simpleOS.scanIC_extraPort = (this->isPress & 0xc0) >> 6;
    byte mask = this->isPress ^ a;
    short mode = this->mode;
    if (isPress != a)
    {
        this->scanClockResetCount = 0;
        for (short i = 0; i < 8; i++)
        {
            if (byteArray_get<byte, byte *>(&mask, i, 1, 6, 8) == 0x1)
            {
                byte c = byteArray_get<byte, byte *>(&b, i, 1, 6, 8);
                switch (byteArray_get<short,short*>(&mode,i,2,6,16))
                {
                case 1:
                    if (c == 0x0)
                    {
                        eventRaiseTick = scanClock + comboTick;
                        mode = 2;
                        Serial.println("KeyUp");
                    }
                    break;
                case 0:
                    if (c == 0x1)
                    {
                        eventRaiseTick = scanClock + holdTick;
                        mode = 1;
                        Serial.println("KeyDown");
                    }
                    break;
                case 2:
                    if (c == 0x1)
                    {
                        comboCount++;
                        eventRaiseTick = scanClock + holdTick;
                        mode = 1;
                        Serial.println("KeyDown");
                    }
                    break;
                }
            }
        }
    }
}