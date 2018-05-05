#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

#include "image.h"

#include <QFileInfo>
#include <QString>
#include <QImage>

class ImageData
{
public:
    ImageData(const QFileInfo& i_path);

    virtual ~ImageData();

    bool is_valid() const;

    qint32 width() const;
    qint32 height() const;

    Image get_image() const;

protected:
    static QImage data_to_image(const QByteArray& i_data, QSize i_size);
    static int point_to_index(int x, int y, int width);

protected:
    qint32 m_width = 0;
    qint32 m_height = 0;

    QByteArray m_data;
    QFileInfo m_path;
};

#endif // IMAGE_DATA_H
