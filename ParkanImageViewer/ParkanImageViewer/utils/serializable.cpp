#include "serializable.h"

std::ostream& operator<<(std::ostream& io_s, const ISerializable& i_obj)
{
    i_obj.write(io_s);
    return io_s;
}

std::istream& operator>>(std::istream& io_s, ISerializable& o_obj)
{
    o_obj.read(io_s);
    return io_s;
}
