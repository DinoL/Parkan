from texture_common import TextureCommon
from texture_dib import TextureDib
from texture_ngb import TextureNgb
import os.path

class TextureBuilder:
    @staticmethod
    def get_texture(path):
        filename = os.path.basename(path)
        _, ext = os.path.splitext(filename)
        if ext not in TextureBuilder.get_texture_extensions():
            print("Extension", ext, "not found")
            return None
        if ext == '.DIB':
            return TextureDib(path)
        elif ext == '.NGB':
            return TextureNgb(path)
        return TextureCommon(path)

    @staticmethod
    def get_texture_extensions():
        bases = ['.A', '.V']
        singles = ['.DIB', '.NGB', '.F', '.W']
        animated_files = [base + str(x) for base in bases for x in range(1, 10)]
        return bases + animated_files + singles