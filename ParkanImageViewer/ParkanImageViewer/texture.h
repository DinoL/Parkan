#ifndef TEXTURE_H
#define TEXTURE_H

#include <QFileInfo>

class Texture
{
public:
    Texture(const QFileInfo& i_path);

    quint32 width() const { return m_width; }
    quint32 height() const { return m_height; }

private:
    quint32 m_width = 0;
    quint32 m_height = 0;
};

#endif // TEXTURE_H
