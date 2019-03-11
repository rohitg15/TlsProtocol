#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <algorithm>

class Utils
{

public:
    template <typename T>
    static T SwapEndian(
        T val
    );

    template <typename T>
    static std::vector<uint8_t> ToBytes(
        T val
    );


    template <typename T>
    static std::vector<uint8_t> GetBigEndianBytes(
        T val
    );

};

template<typename T>
T Utils::SwapEndian(
    T val
)
{
    // auto size = sizeof(val);
    //std::cout << " size : " << size << std::endl;
    T temp = 0;
    while (val > 0)
    {
        temp |= (val & 0xFF);
        temp <<= 8;
        val >>= 8;
    }
    return temp;
}


template <typename T>
std::vector<uint8_t> Utils::ToBytes(
    T val
)
{
    auto length = sizeof(val);
    std::vector<uint8_t> data(length, 0x00);
    for (auto it = data.begin(); it!= data.end(); ++it)
    {
        *it = (val & 0xFF);
        val >>= 8;
    }
    
    return data;
}


template <typename T>
std::vector<uint8_t> Utils::GetBigEndianBytes(
    T val
)
{
    //auto bigEndian = Utils::SwapEndian<T>(val);
    std::vector<uint8_t> bytes = Utils::ToBytes(val);
    std::reverse(bytes.begin(), bytes.end());
    return bytes;
}

#endif  //  _UTILS_H_