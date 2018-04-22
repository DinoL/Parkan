#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <iostream>

class ISerializable
{
public:
    virtual void read(std::istream& io_s) = 0;
    virtual void write(std::ostream& io_s) const = 0;

    friend std::ostream& operator<<(std::ostream& io_s, const ISerializable& i_obj);
    friend std::istream& operator>>(std::istream& io_s, ISerializable& o_obj);
};

#endif // SERIALIZABLE_H
