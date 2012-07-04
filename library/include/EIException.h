#include "EIPrerequisites.h"

#ifndef EIException_H
#define EIException_H

#include <exception>

namespace EI
{

class EITOOLKIT_EXPORT Exception : public virtual std::exception
{
public:
    Exception(const char * file, const char * line, const char * msg) throw ();
    ~Exception () throw ();

    const char* what() const throw ();
private:
    const char* const file;
    const char* const line;
    const char* const msg;
};

}

#define EI_STR_HELPER(x) #x
#define EI_STR(x) EI_STR_HELPER(x)

#define EI_EXCEPTION(message) EI::Exception(__FILE__, EI_STR(__LINE__), __FILE__ ":" EI_STR(__LINE__) " " message);

#endif
