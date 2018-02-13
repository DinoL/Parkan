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

    qint32 width() const;
    qint32 height() const;

    const QImage& image() const;

    void set_palette(const Palette& i_palette);

    void save(const QString& i_path) const;

protected:
    bool prepare_image();

protected:
    qint32 m_width = 0;
    qint32 m_height = 0;

    QByteArray m_data;
    QImage m_img;
};

#endif // IMAGE_H
