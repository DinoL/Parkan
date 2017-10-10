#ifndef BINARYFILE_H
#define BINARYFILE_H

#include <string>
#include <vector>

class BinaryFile
{
public:
    using Sequence = std::vector<int>;

    BinaryFile(const std::string& i_path);

    int get_int(int start, int end);

    int get_word(int start);

    static int bytes_seq_to_int(const Sequence& i_seq);

private:
    int m_word_size = 2;
    Sequence m_seq;
};

#endif // BINARYFILE_H
