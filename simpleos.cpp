
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"
#include "simpleos.h"
#include "keyScanD.h"

void simpleOS_t::setup(){

    Serial.begin(115200);

    this->daemon.startDaemon<keyScanD>(this->daemon.keyScanD);


    // 删除 Arduino的loopTask 任务
    vTaskDelete(NULL);
}
