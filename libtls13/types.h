#ifndef _TYPES_H_
#define _TYPES_H_


#include <stdint.h>

enum class ProtocolVersion : uint16_t
{
    TLS_1_0 = 0x0301,
    TLS_1_1 = 0x0302,
    TLS_1_2 = 0x0303,
    TLS_1_3 = 0x0304
};

enum class CipherSuite : uint16_t {
  TLS_AES_128_GCM_SHA256 = 0x1301,
  TLS_AES_256_GCM_SHA384 = 0x1302,
  TLS_CHACHA20_POLY1305_SHA256 = 0x1303,

  // experimental cipher suites
  TLS_AES_128_OCB_SHA256_EXPERIMENTAL = 0xFF01
};


using Random = std::array<uint8_t, 32>;

enum class ExtensionType : uint16_t
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

struct Extension
{
    ExtensionType extension_type;
    uint16_t length;
    std::vector<uint8_t> data;      //  <0..2^16-1>
};

struct SessionId
{
    const uint8_t length = 32;
    std::array<uint8_t, 32> session_id;
};

struct CipherSuites
{
    uint16_t length;
    std::vector<CipherSuite> ciphers;
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

#endif  //  _TYPES_H_
