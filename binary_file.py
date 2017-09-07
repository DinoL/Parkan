import numpy as np

class Binary_file:
    def __init__(self, path):
        f = open(path, "r")
        self.seq = np.fromfile(f, dtype=np.uint8)