#ifndef TEXTURE_H
#define TEXTURE_H

#include "image.h"

class Texture : public Image
{
public:
    Texture(const QFileInfo& i_path);
};

#endif // TEXTURE_H
