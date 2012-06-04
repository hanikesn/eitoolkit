#ifndef EIPrerequisites_H__
#define EIPrerequisites_H__

#include "eitoolkit_export.h"
#include "EIToolkitConfig.h"
#include <map>
#include <string>
#include <vector>

/**
 * @brief Containts all EIToolkit classes.
 */
namespace EI
{
    /**
     * @brief A Byte as used in the @ref Transport layer.
     */
    typedef char Byte;

    /**
     * @brief A map from std::string to std::string.
     */
    typedef std::map<std::string, std::string> StringMap;
    /**
     * @brief A vector which stores @ref Byte "Bytes".
     */
    typedef std::vector<Byte> ByteVector;
}

#endif
