#include "serializable.h"

std::wostream& operator<<(std::wostream& io_s, const ISerializable& i_obj)
{
    i_obj.write(io_s);
    return io_s;
}

std::wistream& operator>>(std::wistream& io_s, ISerializable& o_obj)
{
    o_obj.read(io_s);
    return io_s;
}

