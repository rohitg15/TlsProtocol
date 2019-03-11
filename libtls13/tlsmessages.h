#ifndef _TLS_MESSAGES_H_
#define _TLS_MESSAGES_H_

#include "types.h"
#include <vector>

//  https://tools.ietf.org/html/draft-ietf-tls-tls13-28#section-4.2
//  https://github.com/facebookincubator/fizz/blob/e049e67cd7624fc03ff7263a4d047970c16008e5/fizz/record/Types.h 

struct ClientHello : public Handshake
{
    ProtocolVersionEnum legacyVersion = ProtocolVersionEnum::TLS_1_2;
    TlsRandom random;
    SessionId legacySessionId;
    CipherSuites ciphers;
    Compression compression;
    Extensions extensions;


    ClientHello();
    ClientHello(
        const std::vector<CipherSuiteEnum>& cipherSuites
    );

    uint32_t GetSize();
    std::vector<uint8_t> Encode();
    TlsBuffer buf_;
};

ClientHello::ClientHello()
:   Handshake(HandshakeTypeEnum::CLIENT_HELLO) 
{
    // initialize default extensions here

    // initialize handshake parameters
    uint32_t hslen = 0;
    hslen += sizeof(ProtocolVersionEnum);
    hslen += random.GetSize();
    hslen += legacySessionId.GetSize();
    hslen += ciphers.GetSize();
    hslen += compression.GetSize();
    handshakePayloadLength.val = hslen;

    // NOTE: add extensions size here

    // initialize record parameters
    recordPayloadLength = 0;
    recordPayloadLength += sizeof(handshakeMsgType);
    recordPayloadLength += handshakePayloadLength.val;

}

ClientHello::ClientHello(
    const std::vector<CipherSuiteEnum>& cipherSuites
) :     Handshake(HandshakeTypeEnum::CLIENT_HELLO),
        ciphers(cipherSuites)
{
    // initialize handshake parameters
    uint32_t hslen = 0;
    hslen += sizeof(ProtocolVersionEnum);
    hslen += random.GetSize();
    hslen += legacySessionId.GetSize();
    hslen += ciphers.GetSize();
    hslen += compression.GetSize();
    handshakePayloadLength.val = hslen;

    // NOTE: add extensions size here

    // initialize record parameters
    recordPayloadLength = 0;
    recordPayloadLength += sizeof(handshakeMsgType);
    recordPayloadLength += handshakePayloadLength.val;
}

uint32_t ClientHello::GetSize()
{
    return sizeof(ProtocolVersionEnum);
        //    legacy_session_id.GetSize() +
        //    ciphers.GetSize() +
        //    compression.GetSize() +
        //    extensions.GetSize();
}

// std::vector<uint8_t> ClientHello::Encode()
// {
//     // write legacy protocol version
//     buf_.AddTwoBytes(static_cast<uint16_t>(legacy_version));
//     // // write legacy session id
//     // buf_.AddVector(legacy_session_id.Encode());
//     // // write ciphers
//     // buf_.AddVector(ciphers.Encode());
//     // // write compression
//     // buf_.AddVector(compression.Encode());
//     // // write extensions
//     // buf_.AddVector(extensions.Encode());
//     return buf_.GetBytes();
// }


#endif  //  _TLS_MESSAGES_H_