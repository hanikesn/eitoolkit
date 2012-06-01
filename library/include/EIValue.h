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
        EMPTY, /**< No value is saved. */
        DOUBLE, /**< A floating point number with double precision is saved. */
        STRING /**< A floating point number with double precision is saved. */
    };

    Value();
    Value(std::string const& value);
    Value(double value );

    Value(Value&& other);
    Value(Value const& other);
    Value& operator=(Value other);
    ~Value();

    Type getType() const;

    std::string const& asString() const;
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
