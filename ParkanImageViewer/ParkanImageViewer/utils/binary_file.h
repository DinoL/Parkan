#ifndef BINARYFILE_H
#define BINARYFILE_H

#include <vector>
#include <QFileInfo>

class BinaryFile
{
public:
    using Sequence = std::vector<quint8>;

    BinaryFile(const QFileInfo& i_path);

    int get_int(int start, int end);

    int get_word(int start);

    static int bytes_seq_to_int(const Sequence& i_seq);

protected:
    int m_word_size = 2;
    Sequence m_seq;
};

#endif // BINARYFILE_H
