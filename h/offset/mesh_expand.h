#pragma once
#include "../typedefs/typedefs_mesh.h"

#include <CGAL/Polygon_mesh_processing/compute_normal.h>
#include <CGAL/Polygon_mesh_processing/transform.h>
#include <CGAL/Aff_transformation_3.h>
#include <map>
#include <cmath> // Для std::abs
#include "mesh_vector_normal_map.h"
#include "correct_normal.h"
#include "../remesh/remesh_planar.h"
#include <CGAL/convex_hull_3.h>

inline bool mesh_expand(Mesh mesh, double margin, Mesh& output) {
    std::vector<std::map<P, std::vector<V>>> vector_normal_map;
    // Создаем vector_normal_map на основе mesh
    mesh_vector_normal_map(mesh, vector_normal_map);

    std::vector<P> pins;
    // Пример вывода содержимого vector_normal_map
    for (const auto& normal_map : vector_normal_map) {
        for (const auto& entry : normal_map) {
            const P& point = entry.first;
            const std::vector<V>& normals = entry.second;
            if (normals.size() == 1) {
                V corrected_normal = correct_normal(normals[0]);
                pins.push_back(point + (corrected_normal * margin));
            }
            else if (normals.size() > 1) {
                V fp = correct_normal(normals[0]);

                // Множество для хранения уникальных нормалей
                std::unordered_set<V, VectorHash, VectorEqual> unique_normals;
                unique_normals.insert(fp);

                for (size_t i = 1; i < normals.size(); i++) {
                    auto cur_norm = correct_normal(normals[i]);
                    if (unique_normals.find(cur_norm) == unique_normals.end()) {
                        fp = fp + cur_norm;
                        unique_normals.insert(cur_norm);
                    }
                }
                //fp = correct_normal(fp);
                fp = fp / unique_normals.size();

                pins.push_back(point + (fp * margin));
            }
        }
    }
    CGAL::convex_hull_3(pins.begin(), pins.end(), output);

    return true;
}
