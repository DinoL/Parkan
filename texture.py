from binary_file import Binary_file
import numpy as np
import cv2

class Texture(Binary_file):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 32

    def decode(self, palette):
        """To be implemented in derived classes"""
        print("Abstract decode method call!")

    def save(self, id, out_file, palette):
        """To be implemented in derived classes"""
        print("Abstract save method call!")

    def get_header_and_texture(self):
        return self.seq[:self.header_size], self.seq[self.header_size:]

    def get_width_and_height(self):
        header, _ = self.get_header_and_texture()
        return map(Binary_file.bytes_seq_to_int, (header[4:8], header[8:12]))

    @staticmethod
    def get_textures_folder():
        return 'textures'
