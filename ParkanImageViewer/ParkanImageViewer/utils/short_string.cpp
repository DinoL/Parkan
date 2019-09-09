#include "short_string.h"

#include "io_utils.h"

#include <QByteArray>

QString ShortString::to_string() const
{
    int i = 0;
    while(i < 16 && !isprint(str[i]))
        ++i;

    int j = i;
    while(j < 16 && isprint(str[j]))
        ++j;

    return QString(QByteArray(str + i, j - i));
}


InputBinaryStream& operator>>(InputBinaryStream& s, ShortString& v)
{
    for(auto& el : v.str)
    {
        s >> el;
    }
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const ShortString& v)
{
    for(const char& el : v.str)
    {
        s << el;
    }
    return s;
}

std::wostream& operator<<(std::wostream& s, const ShortString& v)
{
    s << "\"";
    s << v.to_string();
    s << "\" ";
    return s;
}
