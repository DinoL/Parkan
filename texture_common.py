from texture import Texture
from binary_file import BinaryFile
import numpy as np


class TextureCommon(Texture):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 32

    def get_texture(self):
        _, body = self.get_header_and_body()
        wd, ht = self.get_width_and_height()
        return np.array(body[: wd * ht])

    def get_header_and_body(self):
        return self.seq[:self.header_size], self.seq[self.header_size:]

    def get_width_and_height(self):
        header, _ = self.get_header_and_body()
        return map(BinaryFile.bytes_seq_to_int, (header[4:8], header[8:12]))

    @staticmethod
    def has_signature(binary):
        return ''.join(map(chr, binary.seq[:4])) == 'Texm'
