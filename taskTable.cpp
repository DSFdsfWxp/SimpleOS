#include "taskTable.h"

void taskTable_t::addDymaticTask(appList_t name, baseApp_t* foreground, baseApp_t* background, void* sharedData){
    void* ptr = (void*)(foreground==0 ? (background==0 ? sharedData : background) : foreground);
    if (taskExist(ptr)){
        return;
    }
    baseTaskTable_t result;
    result.appName = name;
    result.background = background;
    result.foreground = foreground;
    result.sharedData = sharedData;
    this->dymaticTask.push(result);
}

baseTaskTable_t* taskTable_t::taskTableFind(void* Case){
    if (Case==0){
        throw -1;
    }
    for (long i = 0;i<this->dymaticTask.length();i++){
        baseTaskTable_t &table = this->dymaticTask[i];
        if (table.foreground==Case || table.background==Case || table.sharedData==Case){
            return &(this->dymaticTask[i]);
        }
    }
    return 0;
}

baseTaskTable_t* taskTable_t::taskTableFind(appList_t name){
    for (long i = 0;i<this->dymaticTask.length();i++){
        baseTaskTable_t &table = this->dymaticTask[i];
        if (table.appName==name){
            return &(this->dymaticTask[i]);
        }
    }
    return 0;
}

bool taskTable_t::taskExist(void* Case){
    try{
        if(this->taskTableFind(Case)!=0){
            return true;
        }
    }catch(int i){}
    return false;
}

bool taskTable_t::taskExist(appList_t name){
    try{
        if(this->taskTableFind(name)!=0){
            return true;
        }
    }catch(int i){}
    return false;
}

baseApp_t* taskTable_t::getAnotherApp(baseApp_t* app){
    baseTaskTable_t *table = this->taskTableFind((void*)(app));
    if (table==0){
        throw -1;
    }
    baseApp_t *result = table->foreground==app ? table->background : table->foreground;
    if (result==0){
        throw -1;
    }
    return result;
}

void* taskTable_t::getSharedData(baseApp_t* app){
    baseTaskTable_t *table = this->taskTableFind((void*)(app));
    if (table==0){
        throw -1;
    }
    void *result = table->sharedData;
    if (result==0){
        throw -1;
    }
    return result;
}

void taskTable_t::switchTaskTable(void* Case, byte status){
    baseTaskTable_t *table = this->taskTableFind(Case);
    switch(status){
        case 0x0:
            if (table->background!=0){
                table->background->stop();
                delete table->background;
            }
            break;
        case 0x1:
            if (table->foreground!=0){
                table->foreground->stop();
                delete table->foreground;
            }
            break;
        case 0x3:
            if (table->foreground!=0){
                table->foreground->stop();
                delete table->foreground;
            }
            if (table->background!=0){
                table->background->stop();
                delete table->background;
            }
            break;
    }
}

