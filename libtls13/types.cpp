#include "types.h"
#include "utils.h"

#include <iostream>


Record::Record(
    RecordTypeEnum rType,
    ProtocolVersionEnum protVersion
)
:   recordType(rType),
    compatVersion(protVersion),
    recordPayloadLength(0)
{}

Handshake::Handshake(
    HandshakeTypeEnum handshakeType
) :
    Record(RecordTypeEnum::HANDSHAKE, ProtocolVersionEnum::TLS_1_2),
    handshakeMsgType(handshakeType),
    handshakePayloadLength(0)
{}


TlsBuffer::TlsBuffer(
    const TlsBuffer& other
) : 
    buf_(other.buf_)
{}

TlsBuffer& TlsBuffer::operator=(
    const TlsBuffer& rhs
)
{
    if (this != &rhs)
    {
        buf_ = rhs.buf_;
    }
    return *this;
}

TlsBuffer::TlsBuffer(
    const TlsBuffer&& other
) : 
    buf_(std::move(other.buf_))
{}

TlsBuffer& TlsBuffer::operator=(
    const TlsBuffer&& rhs
)
{
    if (this != &rhs)
    {
        buf_ = std::move(rhs.buf_);
    }
    return *this;
}

TlsBuffer& TlsBuffer::operator+=(
    const TlsBuffer& rhs
)
{
    buf_.insert(buf_.end(), rhs.buf_.begin(), rhs.buf_.end());
    return *this;
}

void TlsBuffer::AddByte(
    uint8_t byte
)
{
    buf_.emplace_back(byte);
}

void TlsBuffer::AddTwoBytes(
    uint16_t data
)
{
    auto buf = Utils::GetBigEndianBytes<uint16_t>(data);
    AddVector(std::move(buf));
}

void TlsBuffer::AddThreeBytes(
    uint24_t data
)
{
    auto buf = Utils::GetBigEndianBytes<uint32_t>(data.val);
    // discard last byte in the vector since we are only looking at 24 bits
   
    std::reverse(buf.begin(), buf.end());
    buf.pop_back();
    std::reverse(buf.begin(), buf.end());
    AddVector(std::move(buf));
}

void TlsBuffer::AddFourBytes(
        uint32_t data
)
{
    auto buf = Utils::GetBigEndianBytes<uint32_t>(data);
    AddVector(std::move(buf));  
}

void TlsBuffer::AddVector(
    const std::vector<uint8_t>&& data
)
{
    buf_.insert(buf_.end(), data.begin(), data.end());
}


std::vector<uint8_t> TlsBuffer::GetBytes()
{
    std::vector<uint8_t> buf (buf_.size(), 0x00);
    std::copy(buf_.begin(), buf_.end(), buf.begin());
    return buf;
}

uint32_t Record::GetSize()
{
    return sizeof(recordType) + sizeof(compatVersion) + sizeof(recordPayloadLength);
}