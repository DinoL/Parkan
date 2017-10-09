from texture import Texture
from binary_file import BinaryFile
import numpy as np


class TextureAlf(Texture):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 32

    def get_texture(self):
        _, body = self.get_header_and_body()
        wd, ht = self.get_width_and_height()
        return np.array(body[: wd * ht])

    def get_header_and_body(self):
        return self.seq[-self.header_size:], self.seq[: -self.header_size]

    def get_width_and_height(self):
        return 256, 33

    @staticmethod
    def has_signature(binary):
        print(binary.seq[-17], binary.seq[-16])
        return binary.seq[-18] == 0x80 and binary.seq[-17] == 0x3F
