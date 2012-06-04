#ifndef EIValue_H
#define EIValue_H

#include "EIPrerequisites.h"

#include <string>

namespace EI
{

/**
 * @brief Holds different values.
 *
 * This class is used to save different values in @ref DataMessage
 */
class EITOOLKIT_EXPORT Value
{
public:
    /**
     * @brief The data types that can be saved in a @ref Value.
     */
    enum Type {
        EMPTY,  /**< No value is saved. */
        DOUBLE, /**< A floating point number with double precision is saved. */
        STRING  /**< A string is saved. */
    };

    /**
     * @brief Constructs a empty Value.
     */
    Value();
    /**
     * @brief Constructs a Value object holding a string.
     */
    Value(std::string const& value);
    /**
     * @brief Value Constructs a Value object holding a double.
     */
    Value(double value );
    /**
     * @brief Move constructor.
     */
    Value(Value&& other);
    /**
     * @brief Copy constructor.
     */
    Value(Value const& other);
    /**
     * @brief Assignment operator.
     */
    Value& operator=(Value other);
    ~Value();

    /**
     * @brief get the Type of the contained value.
     */
    Type getType() const;

    /**
     * @brief Get the contained string or try to convert the contained value to a string.
     * @return A empty string if the value can not be converted.
     */
    std::string const& asString() const;
    /**
     * @brief Get the containd double or try to convert the contained value to a double.
     * @return 0.0 if the value can not be converted.
     */
    double asDouble() const;

private:
    void swap(Value& other) throw ();

private:
    class ValueImpl;
    ValueImpl* pimpl;
};


/**
 * @brief Prints a \ref Value to the stream
 */
EITOOLKIT_EXPORT std::ostream& operator<< (std::ostream& stream, const Value& value);

}

#endif
