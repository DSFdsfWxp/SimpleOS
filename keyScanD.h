#ifndef simpleOS_keyScanD_h
#define simpleOS_keyScanD_h

#include "daemon.h"

class keyScanD : public daemon_t
{
    friend void scanKeyD_isr(void* ptr);
public:

    short scanTick;
    short checkPressTick;
    byte holdTick;
    byte comboTick;

    byte isPress;
    byte scanClock;
    int eventRaiseTick;
    short mode;
    short comboCount;
    short scanClockResetCount;

    TaskHandle_t task = NULL;

    void start();
    ~keyScanD();
    static void keyScanTask(void *args);
private:

    void scanKey_hal();
    void scanKey();
    void eventRaiseEvent();
    void eventRaiseCheck();
    void scanClockReset();
    void scanClockTick();

};

void IRAM_ATTR scanKeyD_isr(void* ptr);

#endif