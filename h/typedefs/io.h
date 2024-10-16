#pragma once
#include "typedefs_mesh.h"
#include "../offset/mesh_offset.h"

inline Mesh load_from(const std::string& path) {
    Mesh output;
    std::ifstream input;
    input.open(path);
    if (!input) {
        throw std::exception("fail:<load_from>");
    }
    else {
        input >> output;
    }
    input.close();

    if (!CGAL::is_triangle_mesh(output)) {
        if (!PMP::triangulate_faces(output)) {
            throw std::exception("fail:<load_from:no_triangulate>");
        }
    }

    if (!output.is_closed()) {
        throw std::exception("fail:<load_from:no_closed>");
    }

    if (!PMP::does_bound_a_volume(output)) {
        throw std::exception("fail:<load_from:no_bound>");
    }

    if (PMP::does_self_intersect(output)) {
        throw std::exception("fail:<load_from:self_inter>");
    }

    if (!CGAL::is_valid_polygon_mesh(output)) {
        throw std::exception("fail:<load_from:valid_polygon>");
    }

    remesh_planar(output);

    return output;
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
            std::cout << std::format("loading:({})", entry.path().string());

            meshes.push_back(load_from(entry.path().string()));

            std::cout << std::format("loaded:({})\n", meshes.back().size_of_facets());
        }        
    }
    return meshes.size() > 0;
}