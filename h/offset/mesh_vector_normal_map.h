#pragma once
#include "../typedefs/typedefs_mesh.h"

inline void mesh_vector_normal_map(Mesh& mesh, std::vector<std::map<P, std::vector<V>>>& vector_normal_map) {
    // Создаем временную карту для хранения нормалей
    std::map<P, std::vector<V>> normal_map;

    // Проходим по всем граням (facets) в mesh
    for (auto face = mesh.facets_begin(); face != mesh.facets_end(); ++face) {
        // Вычисляем нормаль для текущей грани
        V normal = PMP::compute_face_normal(face, mesh);

        // Проходим по всем вершинам текущей грани
        auto halfedge = face->halfedge();
        do {
            // Получаем точку (вершину)
            P point = halfedge->vertex()->point();

            // Проверяем, существует ли уже такая нормаль для этой точки
            auto& normals = normal_map[point];
            if (std::find(normals.begin(), normals.end(), normal) == normals.end()) {
                // Если такой нормали еще нет, добавляем её
                normals.push_back(normal);
            }

            halfedge = halfedge->next();
        } while (halfedge != face->halfedge());
    }

    // Добавляем нашу карту нормалей в вектор карт
    vector_normal_map.push_back(normal_map);
}
