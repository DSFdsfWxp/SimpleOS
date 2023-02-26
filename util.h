#ifndef simpleOS_util_h
#define simpleOS_util_h

#include <stdarg.h>

class argList_t{
    public:
        argList_t(va_list source);

        template <typename args_t,typename argsBase_t>
        args_t getValue(){
            return (args_t)(va_arg(this->list,argsBase_t));
        }
        
        ~argList_t();
    private:
        va_list list;
};

#endif