#ifndef _TYPES_H_
#define _TYPES_H_


#include <stdint.h>
#include <vector>
#include <array>

struct bits_24
{
    uint32_t val:24;
};
using uint24_t = bits_24;


enum class RecordTypeEnum : uint8_t
{
    HANDSHAKE = 0x16,
    ALERT = 0x20
};


enum class HandshakeTypeEnum : uint8_t
{
    CLIENT_HELLO = 1,
    SERVER_HELLO = 2,
    NEW_SESSION_TICKET = 4,
    END_OF_EARLY_DATA = 5,
    ENCRYPTED_EXTENSIONS = 8,
    CERTIFICATE = 11,
    CERTIFICATE_REQUEST = 13,
    CERTIFICATE_VERIFY = 15,
    FINISHED = 20,
    KEY_UPDATE = 24,
    MESSAGE_HASH = 254,
};

enum class ProtocolVersionEnum : uint16_t
{
    TLS_1_0 = 0x0301,
    TLS_1_1 = 0x0302,
    TLS_1_2 = 0x0303,
    TLS_1_3 = 0x0304
};

enum class CipherSuiteEnum : uint16_t {
  TLS_AES_128_GCM_SHA256 = 0x1301,
  TLS_AES_256_GCM_SHA384 = 0x1302,
  TLS_CHACHA20_POLY1305_SHA256 = 0x1303,

  // experimental cipher suites
  TLS_AES_128_OCB_SHA256_EXPERIMENTAL = 0xFF01
};



enum class ExtensionTypeEnum : uint16_t
{
    server_name = 0,
    supported_groups = 10,
    signature_algorithms = 13,
    application_layer_protocol_negotiation = 16,
    token_binding = 24,
    key_share_old = 40,
    pre_shared_key = 41,
    early_data = 42,
    supported_versions = 43,
    cookie = 44,
    psk_key_exchange_modes = 45,
    certificate_authorities = 47,
    post_handshake_auth = 49,
    signature_algorithms_cert = 50,
    key_share = 51,

    compress_certificate = 0xff02
};

// using Random = std::array<uint8_t, 32>;






// length-encoded vector type
template <typename T, typename U>
struct LVector
{
    U len_;
    std::vector<T> buf_;
};

struct Record
{
    RecordTypeEnum recordType;
    ProtocolVersionEnum compatVersion;
    uint16_t recordPayloadLength;

    // record payload
    
    virtual uint32_t GetSize();
};


struct Handshake : public Record
{
    HandshakeTypeEnum msgType;
    uint24_t handshakePayloadlength;
    
    // handshake message 
};


struct Extension
{
    ExtensionTypeEnum extensionType;
    uint16_t length;
    std::vector<uint8_t> data;      //  <0..2^16-1>
};

struct TlsRandom
{
    std::array<uint8_t, 32> random;
};

struct SessionId
{
    const uint8_t length = 32;
    std::array<uint8_t, 32> session_id;
};

struct CipherSuites
{
    uint16_t length;
    std::vector<CipherSuiteEnum> ciphers;
};

struct Compression
{
    const uint8_t length = 1;
    const uint8_t method = 0x00;
};

struct Extensions
{
    uint16_t length;
    std::vector<Extension> extensions;
};

class TlsBuffer
{
    public:
        TlsBuffer() = default;
        
        TlsBuffer(
            const TlsBuffer&
        );

        TlsBuffer& operator=(
            const TlsBuffer&
        );

        TlsBuffer(
            const TlsBuffer&&
        );

        TlsBuffer& operator=(
            const TlsBuffer&&
        );

        void AddByte(
            uint8_t byte
        );

        void AddTwoBytes(
            uint16_t data
        );

        void AddThreeBytes(
            uint24_t data
        );

        void AddFourBytes(
            uint32_t data
        );

        void AddVector(
            const std::vector<uint8_t>&& data
        );

        TlsBuffer& operator+=(
            const TlsBuffer& rhs
        );

        friend TlsBuffer&& operator+(
            const TlsBuffer& lhs,
            const TlsBuffer rhs
        )
        {
            TlsBuffer buf {lhs};
            buf += rhs;
            return std::move(buf);
        }

        std::vector<uint8_t> GetBytes();
    private:
        std::vector<uint8_t> buf_;
};

#endif  //  _TYPES_H_
