#include "output_binary_stream.h"


OutputBinaryStream::OutputBinaryStream(std::wostream& i_s) : m_s(i_s)
{}

template<>
OutputBinaryStream& operator<<(OutputBinaryStream& s, const QByteArray& v)
{
    for(const auto& el : v)
    {
        s << el;
    }
    return s;
}
