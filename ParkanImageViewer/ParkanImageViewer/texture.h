#ifndef TEXTURE_H
#define TEXTURE_H

#include "image.h"

#include <QByteArray>

class Texture : public Image
{
public:
    Texture(const QFileInfo& i_path);

private:
    QByteArray m_data;
};

#endif // TEXTURE_H
