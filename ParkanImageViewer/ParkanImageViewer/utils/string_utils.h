#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <QString>

#include <string>

std::wstring to_std_string(const std::wstring& i_str);
std::wstring to_std_string(const QString& i_str);
std::wstring to_std_string(const wchar_t* i_str);

#endif // STRING_UTILS_H
