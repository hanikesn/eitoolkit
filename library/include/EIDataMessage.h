#ifndef EIDataMessage_H
#define EIDataMessage_H

#include "EIPrerequisites.h"
#include "EIValue.h"
#include "EIMessage.h"

#include <map>

namespace EI
{

/**
 * @brief Used to send values over via the EIToolkit
 *
 * All values are saved as a Value. The *String and *Double methods are helpers.
 *
 */
class EITOOLKIT_EXPORT DataMessage : public Message
{
public:
    /**
     * @brief IDENTIFIER The identifier used for the MsgType.
     */
    static char const* const IDENTIFIER;

    /**
     * @brief DataMessage
     * @param sender The sender of the message
     */
    DataMessage(std::string const& sender);
    /**
     * @copy_constructor
     */
    DataMessage(DataMessage const& other);
    /**
     * @move_constructor
     */
    DataMessage(DataMessage && other);
    /**
     * @assignment_operator
     */
    DataMessage& operator=(DataMessage other);
    ~DataMessage();

    /**
     * @brief Set a value.
     */
    void set(std::string const& name, Value const& value);
    /**
     * @brief Get a value.
     */
    Value get(std::string const& name) const;
    /**
     * @brief Get all contained values.
     */
    std::map<std::string, Value> getContent() const;

    /**
     * @brief Set a string value
     */
    void setString(std::string const& name, std::string const& value);
    /**
     * @brief Get a string value.
     * @return The value or "" if it does not exist.
     */
    std::string getString(std::string const& name) const;

    /**
     * @brief Set a double value.
     */
    void setDouble(std::string const& name, double value);
    /**
     * @brief Get a double value
     * @return The value or 0.0 if it does not exist.
     */
    double getDouble(std::string const& name) const;

private:
    void swap(DataMessage& other) throw ();

private:
    class DataMessageImpl;
    DataMessageImpl* pimpl;
};

}

#endif
