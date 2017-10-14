#ifndef TEXTURE_H
#define TEXTURE_H

#include "binary_file.h"

class Texture : public BinaryFile
{
public:
    Texture(const QFileInfo& i_path);
};

#endif // TEXTURE_H
