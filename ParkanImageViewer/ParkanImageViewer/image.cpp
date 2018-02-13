#include "image.h"

qint32 Image::width() const
{
    return m_width;
}

qint32 Image::height() const
{
    return m_height;
}

const QImage& Image::image() const
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

bool Image::prepare_image()
{
    if(m_width > 0 && m_height > 0 && m_data.size() >= m_width * m_height)
        m_img = QImage((uchar*)m_data.data(), m_width, m_height, QImage::QImage::Format_Indexed8);

    return !m_img.isNull();
}
