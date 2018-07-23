#ifndef _CLIENT_HELLO_H_
#define _CLIENT_HELLO_H_

#include "record.h"

namespace tls
{
    struct Random
    {
        uint32_t gmtUnixTime;
        uint8_t randomBytes[28];
    }__attribute__((packed));

    struct Session
    {
        uint8_t length;
        uint8_t sessionId[1];           // variable length
    }__attribute__((packed));

    struct CipherSuites
    {
        uint16_t length;
        uint32_t numCiphers;
        uint16_t cipherSuites[1];       // variable length
    }__attribute__((packed));

    struct Compression
    {
        uint8_t length;
        uint8_t compressionMethods[1];
    }__attribute__((packed));

    struct ClientHello
    {
        ProtocolVersion clientVersion;
        Random random;
        Session session;
        CipherSuites cipherSuites;
        Compression compression;
    };
}

#endif  //  _CLIENT_HELLO_H_