#include "string_utils.h"

std::wstring to_std_string(const std::wstring& i_str)
{
    return i_str;
}

std::wstring to_std_string(const QString& i_str)
{
    return i_str.toStdWString();
}

std::wstring to_std_string(const wchar_t *i_str)
{
    return std::wstring(i_str);
}
