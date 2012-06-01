#ifndef EISender_H__
#define EISender_H__

#include "EIPrerequisites.h"
#include "EITransport.h"
#include "EIPresentation.h"
#include "EIMessage.h"
#include "EIDescription.h"

#include <map>
#include <string>

namespace EI
{

/**
 * @brief The Sender class allows you to send messages via the EIToolkit.
 *
 * @section Example
 * @code
 * EI::Sender()
 *
 *asöldksa d
 * @endcode
 *
 * @note This class can not be copied or assigned
 */
class EITOOLKIT_EXPORT Sender
{
public:
    Sender(Description const&, StringMap const& options);
    Sender(Description const&, StringMap const& options, Transport& transport, Presentation& presentation);
    ~Sender();

    void sendMessage(const Message& msg);
private:
    // Disable copying
    Sender(const Sender &);
    Sender &operator=(const Sender &);
private:
    class SenderImpl;
    SenderImpl* const pimpl;
};

}

#endif
