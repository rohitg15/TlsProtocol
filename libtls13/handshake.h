#ifndef _HANDSHAKE_H_
#define _HANDSHAKE_H_


#include <stdint.h>
#include <vector>

enum class HandshakeTypeEnum : uint8_t
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

template <typename T>
struct Handshake : public Record
{
    HandshakeTypeEnum handshakeType;
    uint24_t handshakePayloadLength;

    Handshake(
        const T&& obj
    );

    uint32_t GetSize() override;

    std::vector<uint8_t> Encode();

    private:
        T obj_;
        TlsBuffer buf_;
};

/*
 * Usage: ClientHello ch;
 *        Handshake<ClientHello> msg(ch);
 *        RecordWriter< Handshake<ClientHello> > chRecord;
 */


template <typename T>
Handshake<T>::Handshake(
    const T& obj
) : obj_(std::move(obj)),
    recordType(RecordTypeEnum::Handshake),
    compatVersion(ProtocolVersionEnum::TLS_1_2)
{
    handshakeType = obj_.handshakeType;
    handshakePayloadLength = obj_.GetSize();
    recordPayloadLength = handshakePayloadLength + GetSize();
}

template <typename T>
uint32_t Handshake<T>::GetSize()
{
    // 3 bytes is for handshakePayloadLength
    return sizeof(handshakeType) + 3;
}

template <typename T>
std::vector<uint8_t> Handshake<T>::Encode()
{
    // write handshake type
    buf_.AddByte(static_cast<uint8_t>(handshakeType));
    // write handshake payload length
    buf_.AddThreeBytes(handshakePayloadLength);
    // write payload data
    buf_.AddVector(std::move(obj_.Encode()));
    return buf_.GetBytes();
}



#endif  //  _HANDSHAKE_H_