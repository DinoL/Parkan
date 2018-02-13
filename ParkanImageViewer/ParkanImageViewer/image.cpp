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
    {
        m_img = QImage(m_width, m_height, QImage::QImage::Format_Indexed8);
        for(qint32 y = 0; y < m_height; ++y)
        {
            auto row = m_img.scanLine(y);
            for(qint32 x = 0; x < m_width; ++x)
            {
                row[x] = m_data[x + m_width * y];
            }
        }
    }
    return !m_img.isNull();
}
