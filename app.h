#ifndef simpleOS_app_h
#define simpleOS_app_h

#include "util.h"

enum appList_t : byte {

};

class baseApp_t{
    public:
        virtual void start(argList_t args);
        virtual void stop();
        virtual void suspend();
        virtual void resume();
};

#endif