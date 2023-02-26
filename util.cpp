
#include "util.h"

argList_t::argList_t(va_list source){
    va_copy(this->list,source);
    va_end(source);
}

argList_t::~argList_t(){
    va_end(this->list);
}