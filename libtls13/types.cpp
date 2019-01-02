#include "types.h"
#include "utils.h"

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
    buf.pop_back();
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
    return buf_;
}

uint32_t Record::GetSize()
{
    return sizeof(recordType) + sizeof(compatVersion) + sizeof(recordPayloadLength);
}