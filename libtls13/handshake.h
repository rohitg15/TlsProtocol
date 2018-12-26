#ifndef _HANDSHAKE_H_
#define _HANDSHAKE_H_


#include <stdint.h>
#include <vector>

enum class HandshakeType : uint8_t
{
    client_hello = 1,
    server_hello = 2,
    new_session_ticket = 4,
    end_of_early_data = 5,
    encrypted_extensions = 8,
    certificate = 11,
    certificate_request = 13 ,
    certificate_verify = 15,
    finished = 20,
    key_update = 24,
    message_hash = 254
};

struct Handshake
{
    HandshakeType msg_type;
    uint24_t length;

    std::vector<uint8_t> data;
};

#endif  //  _HANDSHAKE_H_