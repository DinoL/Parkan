#ifndef IMAGE_ITERATOR_H
#define IMAGE_ITERATOR_H

#include <QString>
#include <QFileInfoList>

class ImageIterator
{
public:
    ImageIterator(const QString& i_dir = "");

    ImageIterator& operator++(int) { return inc(); }
    ImageIterator& operator++()    { return inc(); }
    ImageIterator& operator--(int) { return dec(); }
    ImageIterator& operator--()    { return dec(); }

    QFileInfo operator*() const;
private:
    ImageIterator& inc();
    ImageIterator& dec();

    int size() const { return m_images.size(); }

private:
    int m_pos = 0;
    QFileInfoList m_images = {};
};

#endif // IMAGE_ITERATOR_H
