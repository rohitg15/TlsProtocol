#ifndef _MARSHAL_H_
#define _MARSHAL_H_

#include <vector>
#include "tlsmessages.h"
#include "utils.h"

namespace Marshal
{
    template <typename T>
    std::vector<uint8_t> Encode(
        const T& t
    );

    template <typename T>
    T Decode(
        const std::vector<uint8_t>& v
    );

    // ClientHello

    template<>
    std::vector<uint8_t> Encode<ClientHello>(
        const ClientHello& t
    )
    {
        uint32_t total_size = 0;
        std::cout << "Encode ClientHello" << std::endl;
        std::cout << sizeof(ProtocolVersion) << std::endl;
        std::cout << sizeof(Random) << std::endl;
        std::cout << sizeof(CipherSuite) << std::endl;
        std::cout << sizeof(Extension) << std::endl;
        
        return std::vector<uint8_t> {0};
    }

    template<>
    ClientHello Decode(
        const std::vector<uint8_t>& v
    );

    //  SessionId
    template<>
    std::vector<uint8_t> Encode<SessionId>(
        const SessionId& s
    )
    {
        auto length = sizeof(s.length) + sizeof(s.session_id);
        std::vector<uint8_t> data(length, 0x00);
        data[0] = s.length;
        std::copy(s.session_id.begin(), s.session_id.end(), data.begin() + 1);
        return data;
    }

    template<>
    std::vector<uint8_t> Encode<CipherSuites>(
        const CipherSuites& c
    )
    {
        auto length = sizeof(c.length) + c.ciphers.size() * sizeof(CipherSuite);
        std::vector<uint8_t> data(length, 0x00);

        auto length_bytes = Utils::GetBigEndianBytes(c.length);
        std::copy(length_bytes.begin(), length_bytes.end(), data.begin());
        auto i = length_bytes.size();
        for (auto it = c.ciphers.begin(); it != c.ciphers.end(); ++it)
        {
            auto cipher_bytes = Utils::GetBigEndianBytes(*it);
            std::copy(cipher_bytes.begin(), cipher_bytes.end(), data.begin() + i);
            i += 2;
        }
        
        return data;
    }

    // ServerHello

};

#endif  //  _MARSHAL_H_