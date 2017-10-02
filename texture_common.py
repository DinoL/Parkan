from texture import Texture
from binary_file import BinaryFile
import numpy as np
import cv2


class TextureCommon(Texture):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 32

    def save(self, order, out_file, palette):
        _, texture = self.get_header_and_body()

        pixels = [palette.get_color_by_id(col_id) for col_id in texture]

        wd, ht = self.get_width_and_height()

        cur = 0
        cur_id = 0
        while cur < len(pixels):
            if cur_id == order:
                arr = np.array(pixels[cur: cur + ht * wd]).reshape(ht, wd, palette.get_used_channels_cnt())
                cv2.imwrite(out_file, arr)
                break
            cur_id += 1
            cur += wd * ht
            wd, ht = wd // 2, ht // 2

    def get_header_and_body(self):
        return self.seq[:self.header_size], self.seq[self.header_size:]

    def get_width_and_height(self):
        header, _ = self.get_header_and_body()
        return map(BinaryFile.bytes_seq_to_int, (header[4:8], header[8:12]))

    @staticmethod
    def has_signature(binary):
        return ''.join(map(chr, binary.seq[:4])) == 'Texm'
