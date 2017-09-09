from texture import Texture
from binary_file import Binary_file
import numpy as np
import cv2


class TextureNgb(Texture):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 16

    def save(self, order, out_file, palette):
        if "".join(map(chr, self.seq[0:4])) == 'Texm':
            self.save_as_common(order, out_file, palette)
        else:
            print("Saving NGB file to", out_file)

    def save_as_common(self,  id, out_file, palette):
        texture = self.seq[32:]

        pixels = [palette.get_color_by_id(col_id) for col_id in texture]

        wd, ht = map(Binary_file.bytes_seq_to_int, (self.seq[4:8], self.seq[8:12]))

        cur = 0
        cur_id = 0
        while cur < len(pixels):
            if cur_id == id:
                arr = np.array(pixels[cur: cur + ht * wd]).reshape(ht, wd, palette.get_used_channels_cnt())
                cv2.imwrite(out_file, arr)
                break
            cur_id += 1
            cur += wd * ht
            wd, ht = wd // 2, ht // 2

    def get_header_and_texture(self):
        return self.seq[:self.header_size], self.seq[self.header_size:]

    def get_width_and_height(self):
        wd = self.seq[4] - self.seq[0] + 1
        ht = self.seq[6] - self.seq[2] + 1
        return wd, ht
