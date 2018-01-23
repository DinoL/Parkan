#ifndef TEXTURE_H
#define TEXTURE_H

#include "palette.h"

#include <QFileInfo>
#include <QByteArray>
#include <QImage>
#include <QString>

class Texture
{
public:
    Texture(const QFileInfo& i_path);

    quint32 width() const { return m_width; }
    quint32 height() const { return m_height; }

    const QImage& image() const { return m_img; }

    void set_palette(const Palette& i_palette) { m_img.setColorTable(i_palette.get_color_table()); }

    void save(const QString& i_path) const;

private:
    quint32 m_width = 0;
    quint32 m_height = 0;

    QByteArray m_data;
    QImage m_img;
};

#endif // TEXTURE_H
