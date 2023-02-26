#ifndef SimpleOS_h
#define SimpleOS_h

#include "daemon/daemon.h"

class simpleOS_t{
    public:
        void setup();

    private:
        daemonGroup_t daemon;
};

#endif
