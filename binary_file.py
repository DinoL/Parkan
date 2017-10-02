import numpy as np


class BinaryFile:
    def __init__(self, path):
        f = open(path, "r")
        self.seq = np.fromfile(f, dtype=np.uint8)
        self.word_size = 2

    @staticmethod
    def bytes_seq_to_int(bytes_seq):
        sum = 0
        for i in range(len(bytes_seq)):
            sum += bytes_seq[i] * (256 ** i)
        return sum

    def get_int(self, start, end):
        return BinaryFile.bytes_seq_to_int(self.seq[start:end])

    def get_word(self, start):
        return self.get_int(start, start + self.word_size)

