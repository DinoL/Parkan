#include "image_iterator.h"
#include "texture_factory.h"

#include <QFileInfo>

#include <fstream>

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
        m_pos = find_index_of(i_path);
    }
}

int ImageIterator::find_index_of(const QFileInfo& i_path) const
{
    for(int i = 0; i < m_images.size(); ++i)
    {
        if(m_images[i].indexOf(i_path) >=0)
            return i;
    }
    return -1;
}

QFileInfoList ImageIterator::operator*() const
{
    if(!is_valid())
        return {};

    return m_images[m_pos];
}

QFileInfoList* ImageIterator::operator->()
{
    if(!is_valid())
        return nullptr;

    return &m_images[m_pos];
}

bool ImageIterator::is_valid() const
{
    return size() > 0 && m_pos >= 0 && m_pos < size();
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
    m_images.clear();

    const QFileInfoList all_paths = get_images(i_dir, false);

    FrameGroupper groupper;
    for(const auto& group : groupper.split_by_groups(all_paths))
    {
        m_images.push_back(groupper.to_info_list(group));
    }
}
