#ifndef _UTILS_H_
#define _UTILS_H_

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
    auto size = sizeof(val);
    T temp = 0;
    while (size--)
    {
        temp |= (val & 0xFF);
        val >>= 1;
        temp <<= 1;
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
    for (auto it = data.rbegin(); it!= data.rend(); ++it)
    {
        *it = (val & 0xFF);
        val >>= 1;
    }
    return data;
}


template <typename T>
std::vector<uint8_t> Utils::GetBigEndianBytes(
    T val
)
{
    auto big_endian = Utils::SwapEndian(val);
    return Utils::ToBytes(big_endian);
}

#endif  //  _UTILS_H_