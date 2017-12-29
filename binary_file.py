import numpy as np
import struct


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

    def get_bytes(self, start, end):
        return bytes(list(self.seq[start:end]))

    def get_int(self, start, end):
        return BinaryFile.bytes_seq_to_int(self.seq[start:end])

    def get_float(self, start, end):
        return struct.unpack('f', self.get_bytes(start, end))[0]

    def get_word(self, start):
        return self.get_int(start, start + self.word_size)

