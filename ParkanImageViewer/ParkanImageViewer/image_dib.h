#ifndef IMAGE_DIB_H
#define IMAGE_DIB_H

#include "image.h"

#include <QByteArray>

class ImageDib : public Image
{
public:
    ImageDib(const QFileInfo& i_path);

private:
    QByteArray m_data;
};

#endif // IMAGE_DIB_H
