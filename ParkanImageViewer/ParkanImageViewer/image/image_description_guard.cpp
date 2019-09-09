#include "image_description_guard.h"

ImageDescriptionGuard::ImageDescriptionGuard(int i_size, std::wistream& io_stream) :
    m_size(i_size),
    m_stream(io_stream)
{}

int ImageDescriptionGuard::size() const
{
    return m_size;
}

void ImageDescriptionGuard::set_position(int i_pos)
{
    if(i_pos >= 0)
        m_stream.seekg(i_pos);
    else
        m_stream.seekg(i_pos, std::ios_base::end);
}

HeaderGuard::HeaderGuard(int i_size, std::wistream& io_stream) :
    ImageDescriptionGuard(i_size, io_stream)
{
    set_position(0);
}

HeaderGuard::~HeaderGuard()
{
    set_position(size());
}

FooterGuard::FooterGuard(int i_size, std::wistream& io_stream) :
    ImageDescriptionGuard(i_size, io_stream)
{
    set_position(-size());
}

FooterGuard::~FooterGuard()
{
    set_position(0);
}
