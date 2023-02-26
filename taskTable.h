#ifndef simpleOS_taskTable_h
#define simpleOS_taskTable_h

#include "Arduino.h"
#include "libs/lfarray.hpp"
#include "systemUI.h"
#include "desktop.h"
#include "app.h"

struct  baseTaskTable_t{
    appList_t appName;
    baseApp_t* foreground;
    baseApp_t* background;
    void* sharedData;
};


class taskTable_t{
    public:
        lfArray<baseTaskTable_t> dymaticTask;
        desktop_t desktop;
        systemUI_t systemUI;

        void addDymaticTask(appList_t name, baseApp_t* foreground, baseApp_t* background, void* sharedData);
        baseApp_t* getAnotherApp(baseApp_t* app);
        void* getSharedData(baseApp_t* app);
        void switchTaskTable(void* Case, byte status);
        void deleteDymaticTask(void* Case);
        bool taskExist(void* Case);
        bool taskExist(appList_t name);
        baseTaskTable_t* taskTableFind(void* Case);
        baseTaskTable_t* taskTableFind(appList_t name);

};

#endif