#include "binary_file.h"

#include <fstream>
#include <iterator>

BinaryFile::BinaryFile(const std::string& i_path)
{
    std::ifstream stream(i_path, std::ios::in | std::ios::binary);
    m_seq = Sequence(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
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
