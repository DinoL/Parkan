#ifndef IMAGE_DESCRIPTION_GUARD_H
#define IMAGE_DESCRIPTION_GUARD_H

#include <istream>

class ImageDescriptionGuard
{
public:
    ImageDescriptionGuard(int i_size, std::wistream& io_stream);

protected:
    int size() const;
    void set_position(int i_pos);

private:
    int m_size;
    std::wistream& m_stream;
};

class HeaderGuard : public ImageDescriptionGuard
{
public:
    HeaderGuard(int i_size, std::wistream& io_stream);

    ~HeaderGuard();
};

class FooterGuard : public ImageDescriptionGuard
{
public:
    FooterGuard(int i_size, std::wistream& io_stream);

    ~FooterGuard();
};

#endif // IMAGE_DESCRIPTION_GUARD_H
