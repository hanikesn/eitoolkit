#ifndef EIDescriptionMessage_H
#define EIDescriptionMessage_H

#include "EIPrerequisites.h"
#include "EIMessage.h"
#include "EIDescription.h"

namespace EI
{

/**
 * @brief A message used to send Description objects.
 */
class EITOOLKIT_EXPORT DescriptionMessage : public Message
{
public:
    /**
     * @brief Constructs a new DescriptionMessage object.
     * @param sender The sender of the message.
     * @param description The Description object to hold.
     */
    DescriptionMessage(std::string const& sender, Description const& description);

    virtual ~DescriptionMessage();
    /**
     * @copy_constructor
     */
    DescriptionMessage(const DescriptionMessage & other);
    /**
     * @move_constructor
     */
    DescriptionMessage(DescriptionMessage && other);
    /**
     * @assignment_operator
     */
    DescriptionMessage &operator=(DescriptionMessage other);

    /**
     * @brief Get the contained Description object.
     */
    Description getDescription() const;

    /**
     * @brief IDENTIFIER The identifier used for the MsgType.
     */
    static char const* const IDENTIFIER;

private:
    void swap(DescriptionMessage& other) throw ();

private:
    class DescriptionMessageImpl;
    DescriptionMessageImpl* pimpl;
};

}

#endif
