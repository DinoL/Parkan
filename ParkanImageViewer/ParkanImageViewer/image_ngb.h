#ifndef IMAGE_NGB_H
#define IMAGE_NGB_H

#include "image.h"

class ImageNgb : public Image
{
public:
    ImageNgb(const QFileInfo& i_path);

private:
    uchar m_default_color;
};


#endif // IMAGE_NGB_H
