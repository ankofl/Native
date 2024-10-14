#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/convex_hull_3.h>

inline Mesh mesh_convex(Mesh& mesh) {
    std::vector<P> points;
    for (auto vi = mesh.vertices_begin(); vi != mesh.vertices_end(); ++vi) {
        points.push_back(vi->point());
    }
    Mesh convex;
    CGAL::convex_hull_3(points.begin(), points.end(), convex);
    return convex;
}