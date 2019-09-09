#ifndef SHORT_STRING_H
#define SHORT_STRING_H

#include "binary_stream.h"

#include <QString>

#include <iostream>

struct ShortString
{
    char str[16];

    QString to_string() const;
};

InputBinaryStream& operator>>(InputBinaryStream& s, ShortString& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const ShortString& v);
std::wostream& operator<<(std::wostream& s, const ShortString& v);

#endif // SHORT_STRING_H
