#ifndef IMAGE_NGB_COMPLEX_H
#define IMAGE_NGB_COMPLEX_H


#include "image.h"

class ImageNgbComplex : public Image
{
public:
    ImageNgbComplex(const QFileInfo& i_path);

private:
    uchar m_default_color;
};


#endif // IMAGE_NGB_COMPLEX_H
