import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
import cv2
import glob, os

def str_hex_to_int(h):
    return int(h, base=16)

def str_hex_to_float(h):
    return str_hex_to_int(h)/255

def show_data_as_plot(data, file = None, method = 'cv2'):
    if method == 'cv2':
        if file is not None:
            cv2.imwrite(file, data)
        else:
            cv2.imshow('image', data)
            cv2.waitKey();
    elif method == 'plot':
        plt.imshow(data)
        if file is not None:
            plt.savefig(file)
        else:
            plt.show()

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


def get_color_palette(palette_file, channels='rgb'):
    tex = open(palette_file, "r")
    vx = []
    for line in tex:
        vx += line.split(" ")

    width = 4
    indent = 0
    tex_lines = [vx[i : i + width] for i in range(indent, len(vx), width)]

    pal_cols = tex_lines[:256]

    # rgb_lines = [tuple(map(str_hex_to_float, swap_channels(el[:3], channels))) for el in pal_cols]
    rgb_lines = [tuple(map(str_hex_to_int, el[:3])) for el in pal_cols]
    data = np.array(rgb_lines).reshape(1, 256, 3)

    #print(len(data[0]), data[0][100])
    #show_data_as_plot(data, "palette_" + type + ".png")

    # rest = tex_lines[257:]
    # rest_lines = [tuple(map(str_hex_to_float, el[:3])) for el in rest]
    # rest_data = np.array(rest_lines).reshape(128, 128, 3)
    # show_data_as_plot(rest_data, "rest128_wo_alpha.png")
    return data[0]

def get_color_by_id(id, palette = None, channels='rgb', shift = 0):
    if palette is not None:
        return list(palette[(id + 256 - shift) % 256])
    return list(get_color_palette("pal1.txt", channels)[(id + shift) % 256])

def get_tex_files(dir, ext_list):
    # if dir:
    #     os.chdir(dir)
    return [file for files_with_ext in map(lambda ext: glob.glob(dir + "\*." + ext), ext_list) for file in files_with_ext]

def get_width_height(header):
    return map(bytes_seq_to_int, (header[4:8], header[8:12]))

def visualize_tex(tex_file):
    f = open(tex_file, "r")
    vx = np.fromfile(f, dtype=np.uint8)

    #shift = int(vx[24])
    shift = 0
    channels = 'bgr'
    palette = get_color_palette("pal1.txt", channels)
    pixs = [get_color_by_id(col_id, palette=palette, channels=channels, shift=shift) for col_id in vx]

    wd, ht = get_width_height(vx[:32])
    #print("height: {} width: {}".format(ht, wd))

    file_name = tex_file[: tex_file.find('.')]
    out_folder = file_name

    if not os.path.exists(out_folder):
        os.makedirs(out_folder)

    main_tex = pixs[32:]
    #print(len(main_tex))
    cur = 0
    cnt = 0
    while cur < len(main_tex):
        arr = np.array(main_tex[cur : cur + ht*wd]).reshape(ht, wd, 3)
    
        out_file = out_folder + "/" + file_name + "_" + str(ht) + "_" + str(wd) + ".png"
        show_data_as_plot(arr, file=out_file, method='cv2')
        #print(out_file)
        cur += wd*ht
        #print(cur)
        wd, ht = wd//2, ht//2
        cnt += 1
    return cnt

#visualize_tex("AW03.A")

def get_file_stats(file):
    f = open(file, "r")
    vx = np.fromfile(f, dtype=np.uint8)
    header = vx[:32]
    wd, ht = get_width_height(header)
    print(file, wd, ht, header[12], header[24], header[28], sep='\t')


for file in get_tex_files("Korob", ['A', 'A4']):
    visualize_tex(file)

