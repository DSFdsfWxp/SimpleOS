#ifndef SimpleOS_h
#define SimpleOS_h

#include "daemon.h"
#include "taskTable.h"

class simpleOS_t{

    friend class keyScanD;

    public:
        void setup();

    private:
        daemonGroup_t daemon;
        taskTable_t taskTable;

        byte scanIC_extraPort;

};

simpleOS_t simpleOS;

#endif
