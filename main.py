from folder import Folder
from palette import Palette

if __name__ == "__main__":
    Palette.process_all_palettes()
    #for pal_file in Palette.get_palette_files():
    Folder('misc').process(Palette.get_abs_path('B0001.COL'))