#include "image.h"

quint32 Image::width() const
{
    return m_width;
}

quint32 Image::height() const
{
    return m_height;
}

const QImage&Image::image() const
{
    return m_img;
}

void Image::set_palette(const Palette& i_palette)
{
    m_img.setColorTable(i_palette.get_color_table());
}

void Image::save(const QString& i_path) const
{
    image().save(i_path);
}
