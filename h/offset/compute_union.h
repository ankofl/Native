#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/Polygon_mesh_processing/polygon_mesh_to_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include <CGAL/Polygon_mesh_processing/repair.h>
#include <CGAL/Polygon_mesh_processing/self_intersections.h>

inline void compute_union(const Mesh& m1, const Mesh& m2, Mesh& result, size_t i) {
    // Полигональные супы для первой и второй сеток
    std::vector<P> points;
    std::vector<Face> faces;

    // Преобразование первой сетки в полигональный суп
    PMP::polygon_mesh_to_polygon_soup(m1, points, faces);

    // Преобразование второй сетки в полигональный суп
    std::vector<P> points2;
    std::vector<Face> faces2;
    PMP::polygon_mesh_to_polygon_soup(m2, points2, faces2);

    // Добавляем точки и грани второй сетки к первой
    std::size_t index_offset = points.size();
    points.insert(points.end(), points2.begin(), points2.end());

    for (auto& face : faces2) {
        for (auto& index : face) {
            index += index_offset; // Смещаем индексы для второй сетки
        }
        faces.push_back(face);
    }

    // Преобразуем объединённый полигональный суп обратно в сетку
    PMP::polygon_soup_to_polygon_mesh(points, faces, result);

    save_to(m1, std::format("C:/dev/ankofl.Native/data/{}-m1.off", i));
    save_to(m2, std::format("C:/dev/ankofl.Native/data/{}-m2.off", i));
    save_to(result, std::format("C:/dev/ankofl.Native/data/{}-result.off", i));
}
