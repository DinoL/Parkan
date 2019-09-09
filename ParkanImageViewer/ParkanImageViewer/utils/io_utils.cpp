#include "io_utils.h"

std::wostream&operator<<(std::wostream& s, const QString& i_str)
{
    return s << i_str.toStdWString();
}

std::wistream&operator>>(std::wistream& s, QString& o_str)
{
    std::wstring temp;
    s >> temp;
    o_str = QString::fromWCharArray(temp.c_str());
    return s;
}
