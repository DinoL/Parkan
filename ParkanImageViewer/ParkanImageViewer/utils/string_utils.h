#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <QString>

#include <string>

std::string to_std_string(const std::string& i_str);
std::string to_std_string(const QString& i_str);
std::string to_std_string(const char* i_str);

#endif // STRING_UTILS_H
