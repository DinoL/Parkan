#include "image.h"

Image::Image(const QImage& i_img, const QFileInfo& i_path) :
    m_img(i_img),
    m_path(i_path)
{}

bool Image::is_valid() const
{
    return !m_img.isNull();
}

qint32 Image::width() const
{
    return m_img.width();
}

qint32 Image::height() const
{
    return m_img.height();
}

const QImage& Image::image() const
{
    return m_img;
}

QDir Image::dir() const
{
    return m_path.absoluteDir();
}

QFileInfo Image::path() const
{
    return m_path;
}

void Image::set_palette(const Palette& i_palette)
{
    m_img.setColorTable(i_palette.get_color_table());
}

void Image::save(const QString& i_path) const
{
    image().save(i_path);
}

