#pragma once
#include "../typedefs/typedefs_mesh.h"

#include <CGAL/convex_decomposition_3.h>
#include "mesh_convex.h"

inline std::vector<Mesh> mesh_decompose(Mesh& mesh) {
    std::vector<Mesh> meshes;

    Nef N(mesh);

    CGAL::convex_decomposition_3(N);
    Nef::Volume_const_iterator ci = ++N.volumes_begin();
    for (; ci != N.volumes_end(); ++ci) {
        if (ci->mark()) {
            Mesh part;
            N.convert_inner_shell_to_polyhedron(ci->shells_begin(), part);
            Mesh convex = mesh_convex(part);
            if (PMP::volume(convex) > 0.00001) {
                meshes.push_back(convex);
            }
        }
    }

    if (meshes.empty()) {
        throw std::exception("fail:<mesh_decompose>");
    }

    return meshes;
}