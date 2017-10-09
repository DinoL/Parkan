from binary_file import BinaryFile
import cv2
import numpy as np


class Texture(BinaryFile):
    def __init__(self, path):
        super().__init__(path)

    def get_pixels(self, palette):
        wd, ht = self.get_width_and_height()
        pixels = [palette.get_color_by_id(col_id) for col_id in self.get_texture()]
        return np.array(pixels).reshape(ht, wd, palette.get_used_channels_cnt())

    def save(self, out_file, palette):
        cv2.imwrite(out_file, self.get_pixels(palette))

    def get_texture(self):
        """To be implemented in derived classes"""
        raise NotImplementedError('Abstract method call')

    def get_header_and_body(self):
        """To be implemented in derived classes"""
        raise NotImplementedError('Abstract method call')

    def get_width_and_height(self):
        """To be implemented in derived classes"""
        raise NotImplementedError('Abstract method call')

    @staticmethod
    def has_signature(binary):
        """To be implemented in derived classes"""
        raise NotImplementedError('Abstract method call')

    @staticmethod
    def get_textures_folder():
        return 'textures'
