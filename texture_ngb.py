from texture import Texture
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
        header_words = [self.get_word(self.word_size * i) for i in range(4)]
        wd = header_words[2] - header_words[0] + 1
        ht = header_words[3] - header_words[1] + 1
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
    def __init__(self, path):
        super().__init__(path)
        self.row_info_size = 4
        self.row_info_pos_size = 4
        self.terminal_value = 255
        self.wd, self.ht = super().get_width_and_height()

    @staticmethod
    def has_signature(binary):
        return np.array_equal(binary.seq[12:16], [0xAB, 0xCD, 0xEF, 0x01])

    def get_width_and_height(self):
        return self.wd, self.ht

    def get_row_range(self, row):
        row_info_position = self.get_row_info_position(row)
        if self.is_terminal(row_info_position):
            return row_info_position, row_info_position

        _, ht = self.get_width_and_height()
        if row == ht - 1:
            return row_info_position, len(self.seq) - 4

        next_row_info_position = self.get_row_info_position(row + 1)
        return row_info_position, next_row_info_position - 2

    def get_plain_index(self, x, y):
        wd, _ = self.get_width_and_height()
        return wd * y + x

    @staticmethod
    def insert(texture, pos, patch):
        width = len(patch)
        texture[pos : pos + width] = patch

    def process_row(self, row, texture):
        row_start, row_end = self.get_row_range(row)
        if row_start >= row_end:
            return texture

        cur_x = 0
        cur = row_start
        while cur < row_end:
            cur_wd, shift = self.get_row_info(cur)
            cur_x += shift
            cur += self.row_info_size
            TextureNgbComplex.insert(texture, self.get_plain_index(cur_x, row), self.seq[cur : cur + cur_wd])
            cur_x += cur_wd
            cur += cur_wd
        return texture

    def process_rows(self):
        wd, ht = self.get_width_and_height()
        texture = [self.get_default_color()] * (wd * ht)
        for row in range(ht):
            self.process_row(row, texture)
        return texture

    def save(self, order, out_file, palette):
        wd, ht = self.get_width_and_height()
        texture = self.process_rows()
        pixels = [palette.get_color_by_id(col_id) for col_id in texture]
        arr = np.array(pixels).reshape(ht, wd, palette.get_used_channels_cnt())
        cv2.imwrite(out_file, arr)

    def get_row_info_position(self, row):
        s = self.header_size + self.row_info_pos_size * row
        return self.get_int(s, s + self.row_info_pos_size)

    def get_row_info(self, pos):
        return divmod(self.get_int(pos, pos + self.row_info_size), 2 ** 16)

    def is_terminal(self, pos):
        return pos >= len(self.seq) or\
               (self.seq[pos] == self.terminal_value and self.seq[pos + 1] == self.terminal_value)
