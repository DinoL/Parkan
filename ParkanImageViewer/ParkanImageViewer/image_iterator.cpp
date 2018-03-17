#include "image_iterator.h"
#include "texture_factory.h"

ImageIterator::ImageIterator(const QString& i_dir)
{
    if(i_dir.isEmpty())
        return;

    m_images = get_images(i_dir);
}

QFileInfo ImageIterator::operator*() const
{
    if(m_images.isEmpty())
        return {};

    return m_images[m_pos];
}

QFileInfo* ImageIterator::operator->()
{
    if(m_images.isEmpty())
        return nullptr;

    return &m_images[m_pos];
}

ImageIterator::operator bool() const { return size() > 0; }

ImageIterator&ImageIterator::inc()
{
    ++m_pos;
    if(m_pos >= size())
        m_pos -= size();
    return *this;
}

ImageIterator&ImageIterator::dec()
{
    --m_pos;
    if(m_pos < 0)
        m_pos += size();
    return *this;
}
