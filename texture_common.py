from texture import Texture
import numpy as np
import cv2

class TextureCommon(Texture):
    def __init__(self, path):
        super().__init__(path)

    def save(self, id, out_file, palette):
        _, texture = self.get_header_and_texture()

        pixels = [palette.get_color_by_id(col_id) for col_id in texture]

        wd, ht = self.get_width_and_height()

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