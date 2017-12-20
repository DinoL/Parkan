def ones_complement(x, bits=16):
    """Calculates a one's complement integer from the given input value's bits"""
    return x ^ ((1 << bits) - 1)


def twos_complement(input_value, num_bits=16):
    """Calculates a two's complement integer from the given input value's bits"""
    mask = 2 ** (num_bits - 1)
    return -(input_value & mask) + (input_value & ~mask)
