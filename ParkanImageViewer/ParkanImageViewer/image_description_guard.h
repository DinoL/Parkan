#ifndef IMAGE_DESCRIPTION_GUARD_H
#define IMAGE_DESCRIPTION_GUARD_H

#include <istream>

class ImageDescriptionGuard
{
public:
    ImageDescriptionGuard(int i_size, std::istream& io_stream) :
        m_size(i_size),
        m_stream(io_stream)
    {}

protected:
    int m_size;
    std::istream& m_stream;
};

class HeaderGuard : public ImageDescriptionGuard
{
public:
    HeaderGuard(int i_size, std::istream& io_stream) :
        ImageDescriptionGuard(i_size, io_stream)
    {
        m_stream.seekg(0);
    }

    ~HeaderGuard()
    {
        m_stream.seekg(m_size);
    }
};

class FooterGuard : public ImageDescriptionGuard
{
public:
    FooterGuard(int i_size, std::istream& io_stream) :
        ImageDescriptionGuard(i_size, io_stream)
    {
        m_stream.seekg(-m_size, std::ios_base::end);
    }

    ~FooterGuard()
    {
        m_stream.seekg(0);
    }
};

#endif // IMAGE_DESCRIPTION_GUARD_H
