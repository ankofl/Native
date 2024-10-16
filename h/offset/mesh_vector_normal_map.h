#pragma once
#include "../typedefs/typedefs_mesh.h"

inline void mesh_vector_normal_map(Mesh& mesh, std::vector<std::map<P, std::vector<V>>>& vector_normal_map) {
    // ������� ��������� ����� ��� �������� ��������
    std::map<P, std::vector<V>> normal_map;

    // �������� �� ���� ������ (facets) � mesh
    for (auto face = mesh.facets_begin(); face != mesh.facets_end(); ++face) {
        // ��������� ������� ��� ������� �����
        V normal = PMP::compute_face_normal(face, mesh);

        // �������� �� ���� �������� ������� �����
        auto halfedge = face->halfedge();
        do {
            // �������� ����� (�������)
            P point = halfedge->vertex()->point();

            // ���������, ���������� �� ��� ����� ������� ��� ���� �����
            auto& normals = normal_map[point];
            if (std::find(normals.begin(), normals.end(), normal) == normals.end()) {
                // ���� ����� ������� ��� ���, ��������� �
                normals.push_back(normal);
            }

            halfedge = halfedge->next();
        } while (halfedge != face->halfedge());
    }

    // ��������� ���� ����� �������� � ������ ����
    vector_normal_map.push_back(normal_map);
}
