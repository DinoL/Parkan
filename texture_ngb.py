from texture import Texture
from binary_file import Binary_file
import numpy as np
import cv2


class TextureNgb(Texture):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 16

    def get_default_color(self):
        return self.seq[8]

    def get_header_and_texture(self):
        return self.seq[:self.header_size], self.seq[self.header_size:]

    def get_width_and_height(self):
        header, _ = self.get_header_and_texture()
        header_words = {i : Binary_file.bytes_seq_to_int(header[i:i+2]) for i in range(0, 8, 2)}
        wd = header_words[4] - header_words[0] + 1
        ht = header_words[6] - header_words[2] + 1
        return wd, ht


class TextureNgbPlain(TextureNgb):
    @staticmethod
    def has_signature(binary):
        return np.array_equal(binary.seq[12:16], [0xAB, 0xCD, 0xF0, 0x01])

    def save(self, order, out_file, palette):
        wd, ht = self.get_width_and_height()
        _, texture = self.get_header_and_texture()
        pixels = [palette.get_color_by_id(col_id) for col_id in texture]
        arr = np.array(pixels[: ht * wd]).reshape(ht, wd, palette.get_used_channels_cnt())
        cv2.imwrite(out_file, arr)


class TextureNgbComplex(TextureNgb):
    @staticmethod
    def has_signature(binary):
        return np.array_equal(binary.seq[12:16], [0xAB, 0xCD, 0xEF, 0x01])

    def save(self, order, out_file, palette):
        wd, ht = self.get_width_and_height()
        print(wd, ht)
        texture = [self.get_default_color()] * (wd * ht)
        for y in range(ht):
            for x in range(wd):
                texture[wd * y + x] = self.get_pixel_color(x, y)

        pixels = [palette.get_color_by_id(col_id) for col_id in texture]
        arr = np.array(pixels).reshape(ht, wd, palette.get_used_channels_cnt())
        cv2.imwrite(out_file, arr)

    def get_pixel_color(self, x, y):
        row_info_pos_pos = 4*y + self.header_size
        row_info_pos = Binary_file.bytes_seq_to_int(self.seq[row_info_pos_pos : row_info_pos_pos + 4])
        row_info = Binary_file.bytes_seq_to_int(self.seq[row_info_pos: row_info_pos + 4])
        mod = 2**16
        cur_wd, x_shift = divmod(row_info, mod)
        while True:
            cur_x = x - x_shift
            if cur_x < 0:
                break

            if cur_x < cur_wd:
                return self.seq[row_info_pos + cur_x + 4]
            else:
                row_info_pos += (cur_wd + 4)
                row_info = Binary_file.bytes_seq_to_int(self.seq[row_info_pos : row_info_pos + 4])
                x = cur_x - cur_wd
                cur_wd, x_shift = divmod(row_info, mod)

        return self.get_default_color()