#ifndef EIToolkit_H__
#define EIToolkit_H__

/**
 * @mainpage
 *
 * @section intro_sec Introduction
 *
 * The Embedded Interaction Toolkit is a framework for the communication between different devices.
 *
 * Users should look at the @ref EI::Sender and @ref EI::Receiver classes.
 *
 * @note You should just include EIToolkit.h which contains all other headers for easy access.
 *
 * @warning The EIToolkit uses features of the C++11 standard and should be compiled with a compiler which supports C++11 (tested with GCC > 4.6, MSVC > 10, Clang > 3.0)
 *
 * @section intro_sec Bindings
 *
 * There are bindings available for Java and C#, which resemble the C++ API. Therefore this documentation is also valid for them.
 *
 *
 */

#include "EIPrerequisites.h"
#include "EISender.h"
#include "EIReceiver.h"
#include "EIBlockingReceiver.h"
#include "EIUDPTransport.h"
#include "EIJSONPresentation.h"
#include "EIMessage.h"
#include "EIDataMessage.h"
#include "EIDiscoveryMessage.h"
#include "EIDescriptionMessage.h"

#endif
