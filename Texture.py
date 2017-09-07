import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
import cv2
import glob, os

def str_hex_to_int(h):
    return int(h, base=16)

def str_hex_to_float(h):
    return str_hex_to_int(h)/255

def save_data_as_file(data, file):
    cv2.imwrite(file, data)

def swap_channels(rgb, channels='rgb'):
    if channels == 'rgb':
        return rgb
    out = rgb
    if channels == 'rbg':
        out[2], out[1] = rgb[1], rgb[2]
    elif channels == 'brg':
        out[0], out[1], out[2] = rgb[2], rgb[0], rgb[1]
    elif channels == 'bgr':
        out[0], out[1], out[2] = rgb[2], rgb[1], rgb[0]
    elif channels == 'grb':
        out[0], out[1], out[2] = rgb[1], rgb[0], rgb[2]
    elif channels == 'gbr':
        out[0], out[1], out[2] = rgb[1], rgb[2], rgb[0]
    return out

def bytes_seq_to_int(bytes):
    sum = 0
    for i in range(len(bytes)):
        sum += bytes[i] * (256 ** i)
    return sum


def get_color_palette(palette_path):
    f = open(palette_path, "r")
    bytes_seq = np.fromfile(f, dtype=np.uint8)

    bytes_per_color = 4
    bytes_per_channels = 3
    palette_colors_cnt = 256
    colors_seq = [bytes_seq[i : i + bytes_per_channels] for i in range(0, bytes_per_color * palette_colors_cnt, bytes_per_color)]
    data = np.array(colors_seq).reshape(1, palette_colors_cnt, 3)

    #print(len(data[0]), data[0][100])
    #save_data_as_file(data, "palette_" + type + ".png")

    # rest = tex_lines[257:]
    # rest_lines = [tuple(map(str_hex_to_float, el[:3])) for el in rest]
    # rest_data = np.array(rest_lines).reshape(128, 128, 3)
    # save_data_as_file(rest_data, "rest128_wo_alpha.png")
    return data[0]

def get_color_by_id(id, palette = None, shift = 0):
    if palette is not None:
        return list(palette[(id + 256 - shift) % 256])
    return list(get_color_palette("PAL.PAL")[(id + shift) % 256])

def get_texture_files(dir, ext_list):
    return [file for files_with_ext in map(lambda ext: glob.glob(os.path.join(dir, "*." + ext)), ext_list) for file in files_with_ext]

def get_width_height(header):
    return map(bytes_seq_to_int, (header[4:8], header[8:12]))

def get_header_and_texture(bytes_seq):
    return bytes_seq[:32], bytes_seq[32:]

def process_texture_file(texture_path, palette_path):
    f = open(texture_path, "r")
    bytes_seq = np.fromfile(f, dtype=np.uint8)

    palette = get_color_palette(palette_path)

    header, texture = get_header_and_texture(bytes_seq)

    shift = 0
    pixs = [get_color_by_id(col_id, palette=palette, shift=shift) for col_id in texture]

    wd, ht = get_width_height(header)

    dir, tex_name = os.path.split(texture_path)
    file_name = os.path.splitext(tex_name)[0]
    out_folder = os.path.join(dir, file_name)

    if not os.path.exists(out_folder):
        os.makedirs(out_folder)

    cur = 0
    while cur < len(pixs):
        arr = np.array(pixs[cur : cur + ht*wd]).reshape(ht, wd, 3)
        out_file = os.path.join(out_folder, file_name + "_" + str(ht) + "_" + str(wd) + ".png")
        save_data_as_file(arr, file=out_file)
        cur += wd*ht
        wd, ht = wd//2, ht//2

def get_file_stats(file):
    f = open(file, "r")
    bytes_seq = np.fromfile(f, dtype=np.uint8)
    header, _ = get_header_and_texture(bytes_seq)
    wd, ht = get_width_height(header)
    print(file, wd, ht, header[12], header[24], header[28], sep='\t')

def process_folder(folder_name):
    for file in get_texture_files(folder_name, ['A', 'A4']):
        process_texture_file(file, "PAL.PAL")

process_folder("Korob")

