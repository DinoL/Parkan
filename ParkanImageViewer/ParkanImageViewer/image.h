#ifndef IMAGE_H
#define IMAGE_H

#include "palette.h"

#include <QFileInfo>
#include <QString>
#include <QImage>

class Image
{
public:
    Image(const QFileInfo&)
    {}

    quint32 width() const;
    quint32 height() const;

    const QImage& image() const;

    void set_palette(const Palette& i_palette);

    void save(const QString& i_path) const;

protected:
    bool prepare_image();

protected:
    quint32 m_width = 0;
    quint32 m_height = 0;

    QByteArray m_data;
    QImage m_img;
};

#endif // IMAGE_H
