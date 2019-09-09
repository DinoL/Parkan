#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <iostream>

class ISerializable
{
public:
    virtual void read(std::wistream& io_s) = 0;
    virtual void write(std::wostream& io_s) const = 0;

    friend std::wostream& operator<<(std::wostream& io_s, const ISerializable& i_obj);
    friend std::wistream& operator>>(std::wistream& io_s, ISerializable& o_obj);
};

#endif // SERIALIZABLE_H
