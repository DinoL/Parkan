#ifndef INPUTBINARYSTREAM_H
#define INPUTBINARYSTREAM_H

#include <iostream>
#include <type_traits>
#include <QByteArray>

class InputBinaryStream
{
public:
    InputBinaryStream(std::wistream& i_s);

    template<typename T>
    friend InputBinaryStream& read_raw_bytes(InputBinaryStream& s, T& v,
                                             typename std::enable_if<
                                             std::is_integral<T>::value ||
                                             std::is_floating_point<T>::value
                                             >::type* = nullptr);

private:
    std::wistream& m_s;

};

template<typename T>
InputBinaryStream& read_raw_bytes(InputBinaryStream& s, T& v,
                                  typename std::enable_if<
                                  std::is_integral<T>::value ||
                                  std::is_floating_point<T>::value
                                  >::type*)
{
    s.m_s.read((wchar_t*)&v, sizeof(v));
    return s;
}

template<typename T>
InputBinaryStream& operator>>(InputBinaryStream& s, T& v)
{
    return read_raw_bytes(s, v);
}

template<>
InputBinaryStream& operator>>(InputBinaryStream& s, QByteArray& v);

#endif // INPUTBINARYSTREAM_H
