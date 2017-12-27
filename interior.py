from stl_utils import *

class BinaryDescription:
    """Some binary file format-related constants"""
    def __init__(self):
        self.vertex_coord_size = 4     # 32 bit int
        self.vertex_coord_cnt = 3      # 3d
        self.vertex_size = self.vertex_coord_size * self.vertex_coord_cnt
        self.block_size_len = 2        # bytes
        self.vert_face_len = 114       # from hex-editor experiments
        self.hor_face_len = 128        # from hex-editor experiments
        self.face_vertices_cnt = 4     # rectangles
        self.vertex_len_in_face = 10   # contains some additional info, use first 2 bytes as vertex id


def convert_bin_to_stl(input_path, output_path, name):
    """Convert given binary file to STL model"""
    desc = BinaryDescription()
    binary = BinaryFile(input_path)

    vertices_cnt = binary.get_int(0, desc.block_size_len)
    print("Found ", vertices_cnt, " vertices")

    def get_start_from_vertex_id(v_id):
        offset = desc.block_size_len  # from start of the file
        size = desc.vertex_size
        return v_id * size + offset

    def vertex_from_seq(v_id, seq):
        v_start = get_start_from_vertex_id(v_id)
        coord_starts = range(v_start, v_start + desc.vertex_size, desc.vertex_coord_size)
        coord_ends = [c_start + desc.vertex_coord_size for c_start in coord_starts]
        return [seq.get_float(coord_starts[coord_id], coord_ends[coord_id]) for coord_id in range(desc.vertex_coord_cnt)]

    vertices = [vertex_from_seq(v_id, binary) for v_id in range(vertices_cnt)]

    vert_block_start = get_start_from_vertex_id(vertices_cnt)
    vert_faces_cnt = binary.get_word(vert_block_start)
    print("Found ", vert_faces_cnt, " faces")

    def get_start_from_face_id(id):
        offset = vert_block_start + 2 # from start of the file
        size = desc.vert_face_len
        return id * size + offset

    def face_from_seq(f_id, seq):
        f_start = get_start_from_face_id(f_id)
        vert_desc_len = desc.vertex_len_in_face * desc.face_vertices_cnt
        vertices_positions = range(f_start, f_start + vert_desc_len, desc.vertex_len_in_face)
        return [seq.get_word(pos) for pos in vertices_positions]

    vert_faces = [face_from_seq(id, binary) for id in range(vert_faces_cnt)]

    hor_block_start = get_start_from_face_id(vert_faces_cnt)
    hor_faces_cnt = binary.get_word(hor_block_start)
    print("Found ", hor_faces_cnt, " horizontal faces")

    print(vert_block_start, hor_block_start)

    def get_start_from_hor_face_id(f_id):
        offset = hor_block_start + 2 # from start of the file
        size = desc.hor_face_len
        return f_id * size + offset

    def hor_face_from_seq(f_id, seq):
        f_start = get_start_from_hor_face_id(f_id)
        vert_desc_len = desc.vertex_len_in_face * desc.face_vertices_cnt
        vertices_positions = range(f_start, f_start + vert_desc_len, desc.vertex_len_in_face)
        return [seq.get_word(pos) for pos in vertices_positions]

    hor_faces = [hor_face_from_seq(id, binary) for id in range(hor_faces_cnt)]

    all_faces = vert_faces + hor_faces

    def split_to_triangles(rect):
        """Split given rectangle into 2 triangle faces
        for rectangle
        0 - 1
        | \ |
        3 - 2
        faces should be 0-1-2 and 0-2-3"""

        face1 = (rect[0], rect[1], rect[2])
        face2 = (rect[0], rect[2], rect[3])
        return face1, face2

    all_triangle_faces = [tr for rect in all_faces for tr in split_to_triangles(rect)]

    def vertex_id_to_coordinates(v_id):
        return vertices[v_id]

    all_triangle_coordinates = [list(map(vertex_id_to_coordinates, face)) for face in all_triangle_faces]

    def faces_list_to_stl_str(faces, solid_name):
        solid = Solid(solid_name)
        for face in faces:
            loop = Loop()
            for vx in face:
                loop.add_vertex(Vertex(vx))
            facet = Facet()
            facet.add_loop(loop)
            solid.add_facet(facet)

        return solid.to_str(0)

    def write_stl_to_file():
        stl_str = faces_list_to_stl_str(all_triangle_coordinates, name)
        file = open(output_path, 'w+')
        file.write(stl_str)

    write_stl_to_file()
