#ifndef simpleOS_keyScanD_h
#define simpleOS_keyScanD_h

#include "daemon.h"

class keyScanD : public daemon_t{
    void start();
    ~keyScanD();
};

#endif