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
    QFileInfo* operator->();
    operator bool() const;

    bool is_valid() const;

private:
    ImageIterator& inc();
    ImageIterator& dec();

    int size() const { return m_images.size(); }
    void init_images(const QString& i_dir);

private:
    int m_pos = 0;
    QFileInfoList m_images = {};
};

#endif // IMAGE_ITERATOR_H
