#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/Polygon_mesh_processing/remesh_planar_patches.h>
#include <CGAL/Polygon_mesh_processing/region_growing.h>
#include <boost/property_map/vector_property_map.hpp>
#include "../convert_to.h"

inline void remesh_almost_planar(Surface& sm, const double cos = 0.98, const double length = 1) {
    std::vector<std::size_t> region_ids(num_faces(sm));
    std::vector<std::size_t> corner_id_map(num_vertices(sm), 0); // corner status of vertices
    std::vector<bool> ecm(num_edges(sm), false); // mark edges at the boundary of regions
    boost::vector_property_map<V> normal_map; // normal of the supporting planes of the regions detected

    // detect planar regions in the mesh
    std::size_t nb_regions =
        PMP::region_growing_of_planes_on_faces(sm,
            CGAL::make_random_access_property_map(region_ids),
            CGAL::parameters::cosine_of_maximum_angle(cos).
            region_primitive_map(normal_map).
            maximum_distance(length));

    // detect corner vertices on the boundary of planar regions
    std::size_t nb_corners =
        PMP::detect_corners_of_regions(sm,
            CGAL::make_random_access_property_map(region_ids),
            nb_regions,
            CGAL::make_random_access_property_map(corner_id_map),
            CGAL::parameters::cosine_of_maximum_angle(cos).
            maximum_distance(length).
            edge_is_constrained_map(CGAL::make_random_access_property_map(ecm)));

    // run the remeshing algorithm using filled properties
    Surface out;
    PMP::remesh_almost_planar_patches(sm,
        out,
        nb_regions, nb_corners,
        CGAL::make_random_access_property_map(region_ids),
        CGAL::make_random_access_property_map(corner_id_map),
        CGAL::make_random_access_property_map(ecm),
        CGAL::parameters::patch_normal_map(normal_map));

    if (out.is_empty()) {
        // Copy remeshed output back to original mesh
        throw std::exception("fail:<remesh_almost_planar>");
    }    
    sm = out;
}
