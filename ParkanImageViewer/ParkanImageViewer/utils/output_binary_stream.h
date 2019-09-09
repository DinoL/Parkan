#ifndef OUTPUTBINARYSTREAM_H
#define OUTPUTBINARYSTREAM_H

#include <iostream>
#include <type_traits>
#include <QByteArray>

class OutputBinaryStream
{
public:
    OutputBinaryStream(std::wostream& i_s);

    template<typename T>
    friend OutputBinaryStream& write_raw_bytes(OutputBinaryStream& s, const T& v,
                                               typename std::enable_if<
                                               std::is_integral<T>::value ||
                                               std::is_floating_point<T>::value
                                               >::type* = nullptr);
private:
    std::wostream& m_s;
};

template<typename T>
OutputBinaryStream& write_raw_bytes(OutputBinaryStream& s, const T& v,
                                    typename std::enable_if<
                                    std::is_integral<T>::value ||
                                    std::is_floating_point<T>::value
                                    >::type*)
{
    s.m_s.write((wchar_t*)&v, sizeof(v));
    return s;
}

template<typename T>
OutputBinaryStream& operator<<(OutputBinaryStream& s, const T& v)
{
    return write_raw_bytes(s, v);
}

template<>
OutputBinaryStream& operator<<(OutputBinaryStream& s, const QByteArray& v);

#endif // OUTPUTBINARYSTREAM_H
