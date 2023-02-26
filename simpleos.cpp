
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"
#include "simpleos.h"
#include "keyScanD.h"

void simpleOS_t::setup(){

    Serial.begin(115200);

    this->scanIC_extraPort = 0x0;

    this->daemon.startDaemon<keyScanD>(this->daemon.keyScanD);


    // 删除 Arduino的loopTask 任务
    vTaskDelete(NULL);
}
