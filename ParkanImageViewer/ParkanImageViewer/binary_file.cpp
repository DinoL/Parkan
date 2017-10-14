#include "binary_file.h"

#include <fstream>
#include <iterator>
#include <QFile>
#include <iostream>

BinaryFile::BinaryFile(const QFileInfo& i_path)
{
    QFile file(i_path.filePath());
    file.open(QIODevice::ReadOnly);
    const auto buf = file.readAll();
    m_seq = Sequence(buf.begin(), buf.end());
}

int BinaryFile::get_int(int start, int end)
{
    return(bytes_seq_to_int(Sequence(m_seq.begin() + start,
                                     m_seq.begin() + end)));
}

int BinaryFile::get_word(int start)
{
    return(get_int(start, start + m_word_size));
}

int BinaryFile::bytes_seq_to_int(const Sequence& i_seq)
{
    int sum = 0;
    int cur_power = 1;
    for(const auto& byte : i_seq)
    {
        sum += byte * cur_power;
        cur_power *= 256;
    }
    return(sum);
}
