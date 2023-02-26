
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"
#include "simpleos.h"

void simpleOS_t::setup(){


    // 删除 Arduino的loopTask 任务
    vTaskDelete(NULL);
}
