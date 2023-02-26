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

template <typename ptr_t>
void byteArray_new(ptr_t zeroCase, int baseArrayLength);

template <typename baseArray_t, typename ptr_t>
baseArray_t byteArray_get(ptr_t zeroCase, int pos, int caseLen, int length, int baseArrayLength);

template <typename baseArray_t, typename ptr_t>
void byteArray_set(ptr_t zeroCase, int pos, baseArray_t val, int caseLen, int length, int baseArrayLength);

/*
template <typename return_t, typename baseArray_t>
return_t byteArray_get(baseArray_t baseArray, int pos, int caseLen, int length);

template <typename val_t, typename baseArray_t>
void byteArray_set(baseArray_t baseArray, int pos, val_t val, int caseLen, int length);
*/

#endif