#pragma once
#include "typedefs/typedefs_mesh.h"

inline bool load_custom(const std::string path, Mesh& output) {
    std::ifstream input(path);
    if (!input) {
        std::cerr << "������ �������� �����." << std::endl;
        return EXIT_FAILURE;
    }

    // ���������� ��� �������������� ����
    std::vector<P> points;
    std::vector<Face> faces;

    std::string line;
    std::getline(input, line);
    if (line != "OFF") {
        std::cerr << "������: ������������ ������ �����." << std::endl;
        return EXIT_FAILURE;
    }

    // ��������� ���������� ������ � ������
    std::size_t num_vertices, num_faces, num_edges;
    std::getline(input, line);
    std::istringstream iss(line);
    if (!(iss >> num_vertices >> num_faces >> num_edges)) {
        std::cerr << "������: ������������ ���������� ������." << std::endl;
        return EXIT_FAILURE;
    }


    std::getline(input, line);
    // ������ ������
    points.reserve(num_vertices);
    for (std::size_t i = 0; i < num_vertices; ++i) {
        double x, y, z;
        std::getline(input, line);
        std::istringstream iss(line);
        if (!(iss >> x >> y >> z)) {
            std::cerr << "������ ������ ��������� �������." << std::endl;
            return EXIT_FAILURE;
        }
        points.emplace_back(x, y, z);
    }

    // ������ ������
    faces.reserve(num_faces);
    for (std::size_t i = 0; i < num_faces; ++i) {
        std::getline(input, line);
        std::istringstream iss(line);

        std::size_t num_vertices_in_face;
        iss >> num_vertices_in_face;

        if (num_vertices_in_face < 3) {
            std::cerr << "����� " << i << " ����� ����� 3 ������, ������������." << std::endl;
            continue;  // ���������� ����� � ����� ��� 3 ���������
        }

        Face face;
        face.reserve(num_vertices_in_face);
        for (std::size_t j = 0; j < num_vertices_in_face; ++j) {
            std::size_t vertex_index;
            if (!(iss >> vertex_index) || vertex_index >= num_vertices) {
                std::cerr << "������ ������ ������� ������� ��� ������������ ������." << std::endl;
                return EXIT_FAILURE;
            }
            face.push_back(vertex_index);
        }

        // �������� �� ������������ ����
        bool is_valid = true;
        for (std::size_t j = 0; j < face.size(); ++j) {
            std::size_t v1 = face[j];
            std::size_t v2 = face[(j + 1) % face.size()];
            if (v1 == v2) {
                is_valid = false;  // ����������, ���� ���� ������������� ����
                break;
            }
        }

        if (is_valid) {
            faces.push_back(face);  // ������ ���� ����� ���������, ��������� �
        }
    }

    PMP::orient_polygon_soup(points, faces);

    PMP::repair_polygon_soup(points, faces);

    bool soup = PMP::is_polygon_soup_a_polygon_mesh(faces);

    output.clear();
    PMP::polygon_soup_to_polygon_mesh(points, faces, output);

    return false;
}