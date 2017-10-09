from texture_common import TextureCommon
from texture_dib import TextureDib
from texture_ngb import TextureNgbComplex, TextureNgbPlain
from texture_alf import TextureAlf
from binary_file import BinaryFile


class TextureBuilder:
    @staticmethod
    def get_texture(path):
        binary = BinaryFile(path)
        compliant_textures = (texture_class for texture_class in TextureBuilder.get_texture_types()
                              if texture_class.has_signature(binary))
        for texture_class in compliant_textures:
            return texture_class(path)
            break
        else:
            return None

    @staticmethod
    def get_texture_extensions():
        bases = ['.A', '.V']
        singles = ['.DIB', '.NGB', '.F', '.W']
        animated_files = [base + str(x) for base in bases for x in range(1, 10)]
        return bases + animated_files + singles

    @staticmethod
    def get_texture_types():
        return TextureCommon, TextureDib, TextureNgbPlain, TextureNgbComplex, TextureAlf
