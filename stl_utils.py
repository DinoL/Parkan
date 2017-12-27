from binary_file import BinaryFile


class Indented:
    """Represents indented object"""
    def get_indent(self, level):
        return '  ' * level


class Vector(Indented):
    """Represents vector of values"""
    def __init__(self, name, coordinates):
        self.name = name
        self.coordinates = coordinates

    def __getitem__(self, index):
        return self.coordinates[index]

    def to_str(self, level):
        return self.get_indent(level) + self.name + ' ' + ' '.join(map(str, self.coordinates))


class Vertex(Indented):
    """Represents vertex for STL file"""
    def __init__(self, coordinates):
        self.vec = Vector('vertex', coordinates)

    def __getitem__(self, index):
        return self.vec[index]

    def to_str(self, level):
        return self.vec.to_str(level)


class Normal(Indented):
    """Represents normal vector for STL file"""
    def __init__(self, coordinates):
        self.vec = Vector('normal', coordinates)

    def __getitem__(self, index):
        return self.vec[index]

    def to_str(self, level):
        return self.vec.to_str(level)


class Loop(Indented):
    """Represents vertices loop for STL file"""
    def __init__(self):
        self.vertices = []

    def add_vertex(self, vx):
        self.vertices.append(vx)

    def calculate_normal(self):
        default = (0, 0, 0)
        if len(self.vertices) < 3:
            return default

        edge_01 = [self.vertices[1][i] - self.vertices[0][i] for i in range(3)]
        edge_12 = [self.vertices[2][i] - self.vertices[1][i] for i in range(3)]
        # normal is a vector product of face edges

        for el in edge_01 + edge_12:
            if abs(el) > 1e4:
                return default

        #print(edge_01, edge_12)

        x = edge_01[1] * edge_12[2] - edge_01[2] * edge_12[1]
        y = edge_01[2] * edge_12[0] - edge_01[0] * edge_12[2]
        z = edge_01[0] * edge_12[1] - edge_01[1] * edge_12[0]
        norm_sqr = (x ** 2 + y ** 2 + z ** 2)
        if norm_sqr <= 1e-6:
            return default

        return [coordinate / norm_sqr**0.5 for coordinate in (x, y, z)]

    def to_str(self, level):
        res = self.get_indent(level) + 'outer loop\n'
        for vx in self.vertices:
            res += vx.to_str(level + 1) + '\n'
        res += self.get_indent(level) + 'endloop\n'
        return res

class Facet(Indented):
    """Represents facet with (typically) one loop for STL file"""
    def __init__(self):
        self.loops = []

    def add_loop(self, loop):
        self.loops.append(loop)

    def calculate_normal(self):
        default = (0, 0, 0)
        if not self.loops:
            return default

        return self.loops[0].calculate_normal()


    def get_normal(self):
        normal = self.calculate_normal()
        return Normal(normal) # not computed, some default value

    def to_str(self, level):
        res = self.get_indent(level) + 'facet ' + self.get_normal().to_str(0) + '\n'
        for loop in self.loops:
            res += loop.to_str(level + 1)

        res += self.get_indent(level) + 'endfacet\n'
        return res

class Solid(Indented):
    """Represents solid body for STL file"""
    def __init__(self, name):
        self.facets = []
        self.name = name

    def add_facet(self, fac):
        self.facets.append(fac)

    def to_str(self, level):
        res = self.get_indent(level) + 'solid ' + self.name + '\n'
        for fac in self.facets:
            res += fac.to_str(level + 1)

        res += self.get_indent(level) + 'endsolid ' + self.name
        return res


def generate_cube(size):
    """Produce all cube vertices in an appropriate order"""
    def generate_square_in_plane(x, plane_id):
        vxs = [[x, -size, -size],
               [x, -size,  size],
               [x,  size,  size],
               [x,  size, -size],
               [x, -size, -size],
               [x,  size,  size]]
        return permute(vxs, 0, plane_id)

    def permute(vx_list, id1, id2):
        for vx in vx_list:
            vx[id1], vx[id2] = vx[id2], vx[id1]
        return vx_list

    all_vertices = []
    for x in [-size, size]:
        for c_id in range(3):
            square = generate_square_in_plane(x, c_id)
            flip = (x == -size and c_id > 0 or x == size and c_id == 0)
            if flip:
                square = square[::-1]
            all_vertices += square

    return all_vertices


def generate_dodecahedron(radius):
    pass


def generate_octahedron(radius):
    """Produce all octahedron vertices in an appropriate order"""
    vertices = []

    def get_vertex(i, sign):
        vx = [0, 0, 0]
        vx[i] = sign * radius
        return vx

    def get_starting_face(is_upper_half):
        sign = 1 if is_upper_half else -1
        seq = range(3)
        if not is_upper_half:
            seq = seq[::-1]
        return [get_vertex(i, sign) for i in seq]

    def next_face(face):
        opp_vx = [-coordinate for coordinate in face[0]]
        return [face[2], face[1], opp_vx]

    for is_upper_half in (True, False):
        face = get_starting_face(is_upper_half)
        vertices += [*face]
        for i in range(3):
            face = next_face(face)
            vertices += [*face]

    return vertices


def write_vertices_to_stl(output_file, size, generator):
    """Save solid body vertices to STL file"""
    def vertex_list_to_stl_str(all_vertexes):
        s = Solid('body')
        facets_cnt = len(all_vertexes) // 3
        for i in range(facets_cnt):
            l = Loop()
            for vx in all_vertexes[3 * i: 3 * (i + 1)]:
                l.add_vertex(Vertex(vx))
            f = Facet()
            f.add_loop(l)
            s.add_facet(f)

        return s.to_str(0)

    file = open(output_file, 'w+')
    file.write(vertex_list_to_stl_str(generator(size)))
