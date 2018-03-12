#ifndef IMAGE_DESCRIPTION_GUARD_H
#define IMAGE_DESCRIPTION_GUARD_H

#include <istream>

class ImageDescriptionGuard
{
public:
    ImageDescriptionGuard(int i_size, std::istream& io_stream);

protected:
    int m_size;
    std::istream& m_stream;
};

class HeaderGuard : public ImageDescriptionGuard
{
public:
    HeaderGuard(int i_size, std::istream& io_stream);

    ~HeaderGuard();
};

class FooterGuard : public ImageDescriptionGuard
{
public:
    FooterGuard(int i_size, std::istream& io_stream);

    ~FooterGuard();
};

#endif // IMAGE_DESCRIPTION_GUARD_H
