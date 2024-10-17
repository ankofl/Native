#pragma once
#include "typedefs/typedefs_mesh.h"
#include <CGAL/boost/graph/copy_face_graph.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

inline Surface convert_to(const Mesh& mesh) {
	Surface surface;
	CGAL::copy_face_graph(mesh, surface);
	return surface;
}

inline Mesh convert_to(const Surface& surface) {
	Mesh mesh;
	CGAL::copy_face_graph(surface, mesh);
	return mesh;
}