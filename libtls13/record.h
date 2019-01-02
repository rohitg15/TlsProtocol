#ifndef _RECORD_H_
#define _RECORD_H_

#include "types.h"
#include <vector>

template <typename T>
class RecordWriter
{
    public:
        RecordWriter(
            const T&& obj
        );

        std::vector<uint8_t> Encode();
    private:
        T obj_;
        TlsBuffer buf_;
};


template <typename T>
RecordWriter<T>::RecordWriter(
    const T&& obj
) : obj_(std::move(obj))
{}

template <typename T>
std::vector<uint8_t> RecordWriter<T>::Encode()
{
    // write record type
    buf_.AddByte(static_cast<uint8_t>(obj_.recordType));
    // write compat TLS version
    buf_.AddTwoBytes(static_cast<uint16_t>(obj_.compatVersion));
    // write payload length
    buf_.AddTwoBytes(obj_.recordPayloadLength);
    // write payload data
    buf_.AddVector(std::move(obj_.Encode()));
    return buf_.GetBytes();
}


#endif  //  _RECORD_H_