#ifndef TEXTURE_H
#define TEXTURE_H

#include <QFileInfo>

class Texture
{
public:
    Texture(const QFileInfo& i_path);

private:
    quint32 m_width = 0;
    quint32 m_height = 0;
};

#endif // TEXTURE_H
