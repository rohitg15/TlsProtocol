#ifndef _MARSHAL_H_
#define _MARSHAL_H_

#include <vector>
#include "tlsmessages.h"
#include "utils.h"



//  WireSerializer - A helper class to serialize objects into the TLS wire format or
//                   deserialize byte arrays into an appropriate TLS Record object
//                   Encode/Decode are specialized appropriately to serialize/deserialize 
//                   specific objects

// template <typename T>
class WireSerializer
{
    public:
        template <typename T>
        static TlsBuffer Encode(
            const T& obj
        );

        template <typename T>
        static T Decode(
            const TlsBuffer& buf
        );
};

template <>
TlsBuffer WireSerializer::Encode<Record>(
    const Record& obj
)
{
    TlsBuffer buf;
    buf.AddByte(static_cast<uint8_t>(obj.recordType));
    buf.AddTwoBytes(static_cast<uint16_t>(obj.compatVersion));
    buf.AddTwoBytes(obj.recordPayloadLength);
    return std::move(buf);
}

template <>
TlsBuffer WireSerializer::Encode<Handshake>(
    const Handshake& handshake
)
{
    TlsBuffer buf;
    buf.AddByte(static_cast<uint8_t>(handshake.msgType));
    buf.AddThreeBytes(handshake.handshakePayloadlength);
    return std::move(buf);
}

template <>
TlsBuffer WireSerializer::Encode<ClientHello>(
    const ClientHello& ch
)
{
    TlsBuffer buf;

    // serialize record message
    buf += std::move(WireSerializer::Encode<Record>(ch));

    // serialize handshake message
    buf += std::move(WireSerializer::Encode<Handshake>(ch));

    // serialize client hello message
    buf.AddTwoBytes(static_cast<uint16_t>(ch.legacyVersion));
    
    return std::move(buf);
}




// namespace Marshal
// {
//     template <typename T>
//     std::vector<uint8_t> Encode(
//         const T& t
//     );

//     template <typename T>
//     T Decode(
//         const std::vector<uint8_t>& v
//     );

//     // ClientHello

//     template<>
//     std::vector<uint8_t> Encode<ClientHello>(
//         const ClientHello& t
//     )
//     {
//         uint32_t total_size = 0;
//         std::cout << "Encode ClientHello" << std::endl;
//         // std::cout << sizeof(ProtocolVersion) << std::endl;
//         // std::cout << sizeof(Random) << std::endl;
//         // std::cout << sizeof(CipherSuite) << std::endl;
//         std::cout << sizeof(Extension) << std::endl;
        
//         return std::vector<uint8_t> {0};
//     }

//     template<>
//     ClientHello Decode(
//         const std::vector<uint8_t>& v
//     );

//     //  SessionId
//     template<>
//     std::vector<uint8_t> Encode<SessionId>(
//         const SessionId& s
//     )
//     {
//         auto length = sizeof(s.length) + sizeof(s.session_id);
//         std::vector<uint8_t> data(length, 0x00);
//         data[0] = s.length;
//         std::copy(s.session_id.begin(), s.session_id.end(), data.begin() + 1);
//         return data;
//     }

//     // template<>
//     // std::vector<uint8_t> Encode<CipherSuites>(
//     //     const CipherSuites& c
//     // )
//     // {
//     //     auto length = sizeof(c.length) + c.ciphers.size() * sizeof(CipherSuite);
//     //     std::vector<uint8_t> data(length, 0x00);

//     //     auto length_bytes = Utils::GetBigEndianBytes(c.length);
//     //     std::copy(length_bytes.begin(), length_bytes.end(), data.begin());
//     //     auto i = length_bytes.size();
//     //     for (auto it = c.ciphers.begin(); it != c.ciphers.end(); ++it)
//     //     {
//     //         auto cipher_bytes = Utils::GetBigEndianBytes(*it);
//     //         std::copy(cipher_bytes.begin(), cipher_bytes.end(), data.begin() + i);
//     //         i += 2;
//     //     }
        
//     //     return data;
//     // }

//     // ServerHello

// };

#endif  //  _MARSHAL_H_