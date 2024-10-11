#pragma once
#include "typedefs_std.h"
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Polyhedron_3.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

typedef K::Point_3                                P;
typedef K::Vector_3                               V;

typedef CGAL::Polyhedron_3<K> Mesh;
namespace PMP = CGAL::Polygon_mesh_processing;

inline bool load_from(Mesh& output, const std::string path) {
    output.clear();
    std::ifstream input;
    input.open(path);
    if (!input) {
        return false;
    }
    else if (!(input >> output)) {
        return false;
    }

    input.close();
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