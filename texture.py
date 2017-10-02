from binary_file import BinaryFile


class Texture(BinaryFile):
    def __init__(self, path):
        super().__init__(path)

    def save(self, order, out_file, palette):
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
