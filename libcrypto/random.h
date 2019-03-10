#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <array>
#include <sodium/randombytes.h>

namespace Crypto
{

    template <size_t size>
    class Random
    {
        public:
        static std::array<uint8_t, size> GetRandomBytes();

    };

    template <size_t size>
    std::array<uint8_t, size> Random<size>::GetRandomBytes()
    {
        std::array<uint8_t, size> buf;
        randombytes_buf(buf.data(), size);
        return std::move(buf);
    }

} // Crypto



#endif  //  _RANDOM_H_