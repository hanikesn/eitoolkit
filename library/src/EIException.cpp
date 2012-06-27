#include "EIException.h"

namespace EI
{

Exception::Exception(const char *file, const char *line, const char *msg) throw ()
    : file(file), line(line), msg(msg)
{
}

Exception::~Exception() throw ()
{
}

const char* Exception::what() const throw ()
{
    return msg;
}

}
