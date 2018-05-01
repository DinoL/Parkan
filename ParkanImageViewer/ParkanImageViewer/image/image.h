#ifndef IMAGE_H
#define IMAGE_H

#include "palette.h"

#include <QString>
#include <QImage>
#include <QFileInfo>
#include <QDir>

class Image
{
public:
    Image(const QImage& i_img, const QFileInfo& i_path);

    bool is_valid() const;

    qint32 width() const;
    qint32 height() const;

    const QImage& image() const;

    QDir dir() const;
    QFileInfo path() const;

    void set_palette(const Palette& i_palette);

    bool save(const QString& i_path) const;

protected:
    QImage m_img;
    QFileInfo m_path;
};

#endif // IMAGE_H
