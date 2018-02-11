#ifndef IMAGE_NGB_H
#define IMAGE_NGB_H

#include "image.h"

#include <QByteArray>

class ImageNgb : public Image
{
public:
    ImageNgb(const QFileInfo& i_path);

private:
    QByteArray m_data;
};


#endif // IMAGE_NGB_H
