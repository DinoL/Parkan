#ifndef IO_UTILS_H
#define IO_UTILS_H

#include "binary_stream.h"

#include <QString>

#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& s, const QString& i_str);
std::istream& operator>>(std::istream& s, QString& o_str);

#endif // IO_UTILS_H
