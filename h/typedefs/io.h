#pragma once
#include "typedefs_mesh.h"
#include "../offset/mesh_offset.h"

inline bool load_from(Mesh& output, const std::string& path) {
    output.clear();
    std::ifstream input;
    input.open(path);
    if (!input) {
        return false;
    }
    else {
        input >> output;
    }
    input.close();

    if (!CGAL::is_triangle_mesh(output)) {
        if (!PMP::triangulate_faces(output)) {
            std::cout << "no_triangulate\n";
        }
    }

    if (!output.is_closed()) {
        std::cout << "no_closed\n";
    }

    if (!PMP::does_bound_a_volume(output)) {
        std::cout << "no_bound\n";
    }

    if (PMP::does_self_intersect(output)) {
        std::cout << "self_inter\n";
    }

    return CGAL::is_valid_polygon_mesh(output);
}

inline bool save_to(const Mesh& input, const std::string path) {
    if (!CGAL::is_valid_polygon_mesh(input)) {
        return false;
    }
    if (CGAL::IO::write_polygon_mesh(path, input, CGAL::parameters::stream_precision(17))) {
        return true;
    }
    return false;
}

inline bool load_dir(const std::string& directory, std::vector<Mesh>& meshes) {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".off") {
            Mesh loaded;
            if (load_from(loaded, entry.path().string())) {
                //meshes.push_back(loaded);
                meshes.push_back(mesh_offset(loaded, offset_const));
            }
        }
    }
    return meshes.size() > 0;
}