#include "image_description_guard.h"

ImageDescriptionGuard::ImageDescriptionGuard(int i_size, std::istream& io_stream) :
    m_size(i_size),
    m_stream(io_stream)
{}

HeaderGuard::HeaderGuard(int i_size, std::istream& io_stream) :
    ImageDescriptionGuard(i_size, io_stream)
{
    m_stream.seekg(0);
}

HeaderGuard::~HeaderGuard()
{
    m_stream.seekg(m_size);
}

FooterGuard::FooterGuard(int i_size, std::istream& io_stream) :
    ImageDescriptionGuard(i_size, io_stream)
{
    m_stream.seekg(-m_size, std::ios_base::end);
}

FooterGuard::~FooterGuard()
{
    m_stream.seekg(0);
}
