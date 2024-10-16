#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/minkowski_sum_3.h>

typedef CGAL::Nef_polyhedron_S2<K> Nef_polyhedron;
typedef Nef_polyhedron::Sphere_circle Sphere_circle;

inline void expand_polyhedron(Mesh& mesh, double distance) {

	Nef nef(mesh);

	Nef sphera;

    int subdivisions = 16;

    Surface sphere_mesh;
    // ��������� ����� ��� ��������� �����
    std::vector<P> points;
    for (int i = 0; i <= subdivisions; ++i) {
        double theta = i * M_PI / subdivisions;
        for (int j = 0; j <= 2 * subdivisions; ++j) {
            double phi = j * M_PI / subdivisions;
            double x = distance * sin(theta) * cos(phi);
            double y = distance * sin(theta) * sin(phi);
            double z = distance * cos(theta);
            points.push_back(P(x, y, z));
        }
    }

    // ������ �������� �������� ��� ����� �����
    CGAL::convex_hull_3(points.begin(), points.end(), sphere_mesh);

    // ������������ Polyhedron � Nef
    Nef sphere_nef(sphere_mesh);

	Nef res = CGAL::minkowski_sum_3(sphere_nef, sphera);

	Mesh mesh_res;
	res.convert_inner_shell_to_polyhedron(res.volumes_begin()->shells_begin(), mesh_res);

    mesh = mesh_res;
}
