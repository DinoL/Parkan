#include "input_binary_stream.h"


InputBinaryStream::InputBinaryStream(std::wistream& i_s) : m_s(i_s)
{}

template<>
InputBinaryStream& operator>>(InputBinaryStream& s, QByteArray& v)
{
    for(wchar_t el : v)
    {
        s >> el;
    }
    return s;
}
