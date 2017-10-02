from texture import Texture
from binary_file import BinaryFile
import numpy as np


class TextureCommon(Texture):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 32

    def get_texture(self, order):
        _, body = self.get_header_and_body()
        wd, ht = self.get_width_and_height()
        cur_pos = 0
        cur_id = 0
        while cur_pos < len(body):
            if cur_id == order:
                return np.array(body[cur_pos: cur_pos + wd * ht])
            cur_id += 1
            cur_pos += wd * ht
            wd, ht = wd // 2, ht // 2

    def get_header_and_body(self):
        return self.seq[:self.header_size], self.seq[self.header_size:]

    def get_width_and_height(self):
        header, _ = self.get_header_and_body()
        return map(BinaryFile.bytes_seq_to_int, (header[4:8], header[8:12]))

    @staticmethod
    def has_signature(binary):
        return ''.join(map(chr, binary.seq[:4])) == 'Texm'
