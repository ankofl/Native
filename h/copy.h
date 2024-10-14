#pragma once
#include "typedefs/typedefs_mesh.h"
#include <CGAL/boost/graph/copy_face_graph.h>

inline Mesh copy(Mesh& mesh) {
	Mesh out;
	CGAL::copy_face_graph(mesh, out);
	return out;
}


inline void copy(const Mesh& mesh, Surface& surface) {
	surface.clear();
	CGAL::copy_face_graph(mesh, surface);
}

inline void copy(const Surface& surface, Mesh& mesh) {
	mesh.clear();
	CGAL::copy_face_graph(surface, mesh);
}