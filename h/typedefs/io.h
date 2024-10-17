#pragma once
#include "typedefs_mesh.h"
#include "../offset/mesh_offset.h"
#include <CGAL/Polygon_mesh_processing/autorefinement.h>

inline Mesh load_from(const std::string& path) {
    Surface surface;
    std::ifstream input;
    input.open(path);
    if (!input) {
        throw std::exception("fail:<load_from>");
    }
    else {
        input >> surface;
    }
    input.close();

    if (!CGAL::is_triangle_mesh(surface)) {
        if (!PMP::triangulate_faces(surface)) {
            throw std::exception("fail:<load_from:no_triangulate>");
        }
    }

    remesh_almost_planar(surface);

    Mesh mesh = convert_to(surface);

    if (!mesh.is_closed()) {
        PMP::stitch_borders(mesh);

        // Перебираем все дырки (незамкнутые края) и заполняем их
        for (auto h : halfedges(mesh)) {
            if (CGAL::is_border(h, mesh)) {
                // Если это край границы, заполняем отверстие
                PMP::triangulate_refine_and_fair_hole(mesh, h);
            }
        }

        if (!mesh.is_closed()) {
            throw std::exception("fail:<load_from:no_closed>");
        }

        surface = convert_to(mesh);
        remesh_almost_planar(surface);
        mesh = convert_to(surface);
    }

    if (!PMP::does_bound_a_volume(mesh)) {
        throw std::exception("fail:<load_from:no_bound>");
    }

    if (PMP::does_self_intersect(mesh)) {
        if (PMP::does_self_intersect(mesh)) {
            throw std::exception("fail:<load_from:self_inter>");
        }        
    }

    if (!CGAL::is_valid_polygon_mesh(mesh)) {
        throw std::exception("fail:<load_from:valid_polygon>");
    }

    remesh_planar(mesh);

    return mesh;
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