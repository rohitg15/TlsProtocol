#ifndef _TLS_MESSAGES_H_
#define _TLS_MESSAGES_H_

#include "types.h"
#include <vector>

//  https://tools.ietf.org/html/draft-ietf-tls-tls13-28#section-4.2
//  https://github.com/facebookincubator/fizz/blob/e049e67cd7624fc03ff7263a4d047970c16008e5/fizz/record/Types.h 

struct ClientHello
{
    ProtocolVersionEnum legacy_version = ProtocolVersionEnum::TLS_1_2;
    // Random random;
    SessionId legacy_session_id;
    CipherSuites ciphers;
    Compression compression;
    Extensions extensions;

    uint32_t GetSize();
    std::vector<uint8_t> Encode();
    TlsBuffer buf_;
};

uint32_t ClientHello::GetSize()
{
    return sizeof(ProtocolVersionEnum);
        //    legacy_session_id.GetSize() +
        //    ciphers.GetSize() +
        //    compression.GetSize() +
        //    extensions.GetSize();
}

std::vector<uint8_t> ClientHello::Encode()
{
    // write legacy protocol version
    buf_.AddTwoBytes(static_cast<uint16_t>(legacy_version));
    // // write legacy session id
    // buf_.AddVector(legacy_session_id.Encode());
    // // write ciphers
    // buf_.AddVector(ciphers.Encode());
    // // write compression
    // buf_.AddVector(compression.Encode());
    // // write extensions
    // buf_.AddVector(extensions.Encode());
    return buf_.GetBytes();
}


#endif  //  _TLS_MESSAGES_H_