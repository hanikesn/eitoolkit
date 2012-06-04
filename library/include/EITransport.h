#ifndef EITransport_H__
#define EITransport_H__

#include "EIPrerequisites.h"

#include <vector>

namespace EI
{

class PacketListener;

/**
 * @brief Abstract base class for all transports.
 *
 * Transports are used to send packets (byte arrays) around.
 * Each transport has to support two different channels:
 * A data channel and a communication channel.
 * The different channels are used to minimize interfering communication,
 * when a lot of @ref DataMessage "DataMessages" are being sent.
 *
 * @note All methods should be @ref threadsafe "thread-safe".
 *
 * @warning It is considered unsafe to add or remove listeners in the callback of a listener. It is likely that a deadlock will occur.
 */
class EITOOLKIT_EXPORT Transport
{
public:
    /**
     * @brief The Channel enum
     */
    enum Channel {
        ALL,          /**< Synonym for all channels. */
        DATA,         /**< The data channel on which @ref DataMessage "DataMessages" are sent. */
        COMMUNICATION /**< The communication channel for all other @ref Message "messages". */
    };

    virtual ~Transport();

    /**
     * @brief Send a packet over the specified channel.
     * @param channel The channel over which to send the packet. With ALL the packet will be sent over both channels.
     * @param packet The packet to be sent.
     */
    virtual void sendPacket(Channel channel, ByteVector const& packet) = 0;
    /**
     * @brief Add a listener for packets.
     *
     * The listener will be asynchronously called when a new packet arrives.
     *
     * @param channel The channel to listen on.
     * @param listener The listener should live as long as the Transport or should be removed before the Transport is destroyed.
     */
    virtual void addPacketListener(Channel channel, PacketListener& listener) = 0;
    /**
     * @brief Remove a PacketListener.
     */
    virtual void removePacketListener(PacketListener& listener) = 0;
};

/**
 * @brief A callback interface for packets.
 *
 * Used by the Transport interface.
 */
class EITOOLKIT_EXPORT PacketListener
{
public:
    virtual ~PacketListener();
    /**
     * @brief The function called when a packet arrives on in the Transport.
     * @param channel The Channel on which the packet arrived. ALL is not used.
     * @param packet The ByteVector which contains the packet. \warning The packet object will be destroyed after this method returns. It is therefore unsafe to safe references to the packet object.
     *
     * @warning This method will be called asynchronously. That means that the implementation has to be @ref threadsafe "thread-safe".
     */
    virtual void onPacket(Transport::Channel channel, ByteVector const& packet) = 0;
};

}

#endif
