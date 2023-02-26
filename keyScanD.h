#ifndef simpleOS_keyScanD_h
#define simpleOS_keyScanD_h

#include "daemon.h"

class keyScanD : public daemon_t
{
public:
    void start();
    ~keyScanD();
};

#endif