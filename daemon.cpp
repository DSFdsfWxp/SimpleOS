
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "daemon.h"

void daemon_t::start(){}
daemon_t::~daemon_t(){}


void daemonGroup_t::stopDaemon(daemon_t* &ptr){
    if (ptr==0){
        return;
    }
    delete ptr;
    ptr = 0;
}