#ifndef _RECORD_H_
#define _RECORD_H_

#include <stdint.h>

namespace tls
{
    struct ProtocolVersion
    {
        uint8_t major;
        uint8_t minor;
    }__attribute__((packed));

    enum class ContentType : uint8_t
    {
        ChangeCipherSpec = 20,
        Alert = 21,
        Handshake = 22,
        ApplicationData = 23
    };

    struct TlsMessage
    {
        enum ContentType type;               // ContentType
        ProtocolVersion version;
        uint16_t length;
        uint8_t fragment[0];        // variable length
    }__attribute__((packed));
}

#endif  //  _RECORD_H_