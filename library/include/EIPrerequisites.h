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
     * @brief Byte type. Used for the @ref Transport layer.
     */
    typedef char Byte;

    typedef std::map<std::string, std::string> StringMap;
    typedef std::vector<Byte> ByteVector;
}

#endif
