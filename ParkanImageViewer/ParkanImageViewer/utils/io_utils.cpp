#include "io_utils.h"

std::ostream&operator<<(std::ostream& s, const QString& i_str)
{
    return s << i_str.toStdString();
}

std::istream&operator>>(std::istream& s, QString& o_str)
{
    std::string temp;
    s >> temp;
    o_str = QString(temp.c_str());
    return s;
}
