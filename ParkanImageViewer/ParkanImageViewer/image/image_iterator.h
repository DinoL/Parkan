#ifndef IMAGE_ITERATOR_H
#define IMAGE_ITERATOR_H

#include <QString>
#include <QFileInfoList>

#include "frame_groupper.h"

class ImageIterator
{
public:
    ImageIterator(const QString& i_dir = "");

    ImageIterator& operator++(int) { return inc(); }
    ImageIterator& operator++()    { return inc(); }
    ImageIterator& operator--(int) { return dec(); }
    ImageIterator& operator--()    { return dec(); }

    QFileInfoList operator*() const;
    QFileInfoList* operator->();
    operator bool() const;

    bool is_valid() const;

private:
    ImageIterator& inc();
    ImageIterator& dec();

    int size() const { return static_cast<int>(m_images.size()); }
    void init_images(const QString& i_dir);

private:
    int m_pos = 0;
    std::vector<QFileInfoList> m_images = {};
    int find_index_of(const QFileInfo& i_path) const;
};

#endif // IMAGE_ITERATOR_H
