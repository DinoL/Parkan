import numpy as np
import struct

formats = {
    'c': ['char', 1],
    'b': ['signed_char', 1],
    'B': ['unsigned_char', 1],
    '?': ['bool', 1],
    'h': ['short', 2],
    'H': ['unsigned_short', 2],
    'i': ['int', 4],
    'I': ['unsigned_int', 4],
    'l': ['long', 4],
    'L': ['unsigned_long', 4],
    'q': ['long_long', 8],
    'Q': ['unsigned_long_long', 8],
    'f': ['float', 4],
    'd': ['double', 8]
}

class BinaryFile:
    def __init__(self, path):
        f = open(path, "r")
        self.seq = np.fromfile(f, dtype=np.uint8)
        self.word_size = 2

    def get_value(self, type, pos):
        if not type in formats:
            raise ValueError('Unsupported value type in get_value: {}'.format(type))
        return struct.unpack(type, self.get_bytes(pos, pos + formats[type][1]))[0]

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

    def get_float(self, pos):
        return struct.unpack('f', self.get_bytes(pos, pos + 4))[0]

    def get_word(self, start):
        return self.get_int(start, start + self.word_size)

