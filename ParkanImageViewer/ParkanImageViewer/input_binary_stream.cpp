#include "input_binary_stream.h"


InputBinaryStream::InputBinaryStream(std::istream& i_s) : m_s(i_s)
{}

template<>
InputBinaryStream& operator>>(InputBinaryStream& s, QByteArray& v)
{
    for(auto& el : v)
    {
        s >> el;
    }
    return s;
}
