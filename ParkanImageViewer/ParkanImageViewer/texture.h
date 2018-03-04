#ifndef TEXTURE_H
#define TEXTURE_H

#include "image_data.h"

class Texture : public ImageData
{
public:
    Texture(const QFileInfo& i_path);
};

#endif // TEXTURE_H
