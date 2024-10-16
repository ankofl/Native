#pragma once
#include "typedefs_std.h"
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <CGAL/IO/read_off_points.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/Polygon_mesh_processing/self_intersections.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/Nef_3/SNC_indexed_items.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_3                                P;
typedef K::Vector_3                               V;
typedef std::vector<std::size_t> Face;

typedef CGAL::Polyhedron_3<K> Mesh;

typedef CGAL::Surface_mesh<P> Surface;
typedef Surface::Halfedge_index Halfedge_index;
typedef Surface::Vertex_index Vertex_index;

typedef CGAL::Nef_polyhedron_3<K, CGAL::SNC_indexed_items> Nef;

namespace PMP = CGAL::Polygon_mesh_processing;

struct VectorHash {
    template <class T>
    std::size_t operator()(const T& v) const {
        // Используем хэш-функцию для x, y и z
        std::size_t seed = 0;
        seed ^= std::hash<double>()(CGAL::to_double(v.x())) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<double>()(CGAL::to_double(v.y())) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<double>()(CGAL::to_double(v.z())) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

struct VectorEqual {
    bool operator()(const V& lhs, const V& rhs) const {
        // Определите сравнение для нормалей
        return lhs == rhs; // или используйте сравнение с определенной точностью
    }
};

struct PointEqual {
    bool operator()(const P& lhs, const P& rhs) const {
        // Определите сравнение для нормалей
        return lhs == rhs; // или используйте сравнение с определенной точностью
    }
};