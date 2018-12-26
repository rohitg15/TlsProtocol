#ifndef _TLS_MESSAGES_H_
#define _TLS_MESSAGES_H_

#include "types.h"
#include <vector>

//  https://tools.ietf.org/html/draft-ietf-tls-tls13-28#section-4.2
//  https://github.com/facebookincubator/fizz/blob/e049e67cd7624fc03ff7263a4d047970c16008e5/fizz/record/Types.h 

struct ClientHello
{
    ProtocolVersion legacy_version = ProtocolVersion::TLS_1_2;
    Random random;
    SessionId legacy_session_id;
    CipherSuites ciphers;
    Compression compression;
    Extensions extensions;
};

#endif  //  _TLS_MESSAGES_H_