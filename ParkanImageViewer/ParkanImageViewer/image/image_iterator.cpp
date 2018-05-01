#include "image_iterator.h"
#include "texture_factory.h"

#include <QFileInfo>

ImageIterator::ImageIterator(const QString& i_path)
{
    if(i_path.isEmpty())
        return;

    QFileInfo info(i_path);

    if(info.isDir())
    {
        init_images(i_path);
    }
    else if(info.isFile())
    {
        init_images(info.absolutePath());
        m_pos = m_images.indexOf(i_path);
    }
}

QFileInfo ImageIterator::operator*() const
{
    if(!is_valid())
        return {};

    return m_images[m_pos];
}

QFileInfo* ImageIterator::operator->()
{
    if(!is_valid())
        return nullptr;

    return &m_images[m_pos];
}

bool ImageIterator::is_valid() const
{
    return size() > 0 && m_pos >= 0;
}

ImageIterator::operator bool() const
{
    return is_valid();
}

ImageIterator& ImageIterator::inc()
{
    ++m_pos;
    if(m_pos >= size())
        m_pos -= size();
    return *this;
}

ImageIterator& ImageIterator::dec()
{
    --m_pos;
    if(m_pos < 0)
        m_pos += size();
    return *this;
}

void ImageIterator::init_images(const QString& i_dir)
{
    m_images = get_images(i_dir);
}
