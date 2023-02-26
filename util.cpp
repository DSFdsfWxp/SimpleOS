
#include "util.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

argList_t::argList_t(va_list source){
    va_copy(this->list,source);
    va_end(source);
}

argList_t::~argList_t(){
    va_end(this->list);
}

template <typename ptr_t>
void byteArray_new(ptr_t zeroCase, int baseArrayLength){
    for (int i=0;i<baseArrayLength;i++){
        *zeroCase = 0;
        zeroCase++;
    }
}

template <typename baseArray_t, typename ptr_t>
baseArray_t byteArray_get(ptr_t zeroCase, int pos, int caseLen, int length, int baseArrayLength){
    ptr_t ptr = zeroCase;
    if (caseLen*length>sizeof(baseArray_t)*baseArrayLength){
        throw -1;
    }

    baseArray_t result = 0x0;

    int bpos = pos*caseLen/sizeof(baseArray_t);
    int bbpos = pos*caseLen%sizeof(baseArray_t);
    for (int i=0;i<caseLen;i++){
        if (bbpos==sizeof(baseArray_t)){
            bbpos = 0;
            bpos++;
        }
        baseArray_t mask = 0x1 << bbpos;
        ptr = zeroCase + bpos;
        result += (*ptr & mask) >> bbpos;
        result = result << 1;
        bbpos++;
    }

    return result;
}

template <typename baseArray_t, typename ptr_t>
void byteArray_set(ptr_t zeroCase, int pos, baseArray_t val, int caseLen, int length, int baseArrayLength){
    ptr_t ptr = zeroCase;
    if (caseLen*length>sizeof(baseArray_t)*baseArrayLength){
        throw -1;
    }

    vTaskSuspendAll();

    int rpos = 0;
    int bpos = pos*caseLen/sizeof(baseArray_t);
    int bbpos = pos*caseLen%sizeof(baseArray_t);
    for (int i=0;i<caseLen;i++){
        if (bbpos==sizeof(baseArray_t)){
            bbpos = 0;
            bpos++;
        }
        baseArray_t mask = 0x1 << rpos;
        baseArray_t rval = (val & mask) >> rpos;
        mask = 0x1 << bbpos;
        ptr = zeroCase + bpos;
        if ((*ptr & mask) >> bbpos != rval){
            *ptr = *ptr ^ mask;
        }
        bbpos++;
        rpos++;
    }

    xTaskResumeAll();

}
