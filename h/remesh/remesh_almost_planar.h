#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/Polygon_mesh_processing/remesh_planar_patches.h>
#include <CGAL/Polygon_mesh_processing/region_growing.h>
#include <boost/property_map/vector_property_map.hpp>
#include "../copy.h"

inline void remesh_almost_planar(Mesh& mesh, const double cos = 0.6, const double length = 1) {
    Surface sm;
    copy(mesh, sm);
    // declare vectors to store mesh properties
    std::vector<std::size_t> region_ids(num_faces(sm));
    std::vector<std::size_t> corner_id_map(num_vertices(sm), -1); // corner status of vertices
    std::vector<bool> ecm(num_edges(sm), false); // mark edges at the boundary of regions
    boost::vector_property_map<V> normal_map; // normal of the supporting planes of the regions detected

    // detect planar regions in the mesh
    std::size_t nb_regions =
        PMP::region_growing_of_planes_on_faces(sm,
            CGAL::make_random_access_property_map(region_ids),
            CGAL::parameters::cosine_of_maximum_angle(cos).
            //CGAL::parameters::cosine_of_maximum_angle(0.98).
            region_primitive_map(normal_map).
            maximum_distance(length));
    //maximum_distance(0.011));

// detect corner vertices on the boundary of planar regions
    std::size_t nb_corners =
        PMP::detect_corners_of_regions(sm,
            CGAL::make_random_access_property_map(region_ids),
            nb_regions,
            CGAL::make_random_access_property_map(corner_id_map),
            CGAL::parameters::cosine_of_maximum_angle(cos).
            //CGAL::parameters::cosine_of_maximum_angle(0.98).
            //maximum_distance(0.011).
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
    copy(out, mesh);
}