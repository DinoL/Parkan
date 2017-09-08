from texture import Texture
from binary_file import Binary_file
import numpy as np
import cv2

class TextureDib(Texture):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 32

    def save(self, id, out_file, palette):
        _, texture = self.get_header_and_texture()

        pixels = [palette.get_color_by_id(col_id) for col_id in texture]

        wd, ht = self.get_width_and_height()

        arr = np.array(pixels[0: 0 + ht * wd]).reshape(ht, wd, palette.get_used_channels_cnt())
        cv2.imwrite(out_file, arr)

    def get_header_and_texture(self):
        return self.seq[-self.header_size:], self.seq[: -self.header_size]

    def get_width_and_height(self):
        header, _ = self.get_header_and_texture()
        return map(Binary_file.bytes_seq_to_int, (header[8:12], header[12:16]))