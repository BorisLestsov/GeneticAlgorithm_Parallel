#ifndef GEN_EXCEPTION_H
#define GEN_EXCEPTION_H

#include <exception>

class Exception: public std::exception {
    const char* errmsg;
public:
    explicit Exception(const char* str);
    const char* what() const noexcept;
};

#endif //GEN_EXCEPTION_H
