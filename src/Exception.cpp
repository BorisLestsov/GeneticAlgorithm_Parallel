#include "Exception.h"

Exception::Exception(const char* str):
        errmsg(str)
{}

const char* Exception::what() const noexcept {
    return errmsg;
}
