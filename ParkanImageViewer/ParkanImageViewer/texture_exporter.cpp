#include "texture_exporter.h"

std::string to_std_string(const std::string& i_str)
{
    return i_str;
}

std::string to_std_string(const QString& i_str)
{
    return i_str.toStdString();
}

std::string to_std_string(const char *i_str)
{
    return std::string(i_str);
}
