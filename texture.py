from binary_file import Binary_file
import numpy as np
import cv2


class Texture(Binary_file):
    def __init__(self, path):
        super().__init__(path)

    def save(self, order, out_file, palette):
        """To be implemented in derived classes"""
        print("Abstract save method call!")

    def get_header_and_texture(self):
        """To be implemented in derived classes"""
        print("Abstract get_header_and_texture method call!")

    def get_width_and_height(self):
        """To be implemented in derived classes"""
        print("Abstract get_width_and_height method call!")

    @staticmethod
    def get_textures_folder():
        return 'textures'
