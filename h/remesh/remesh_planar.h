#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/Polygon_mesh_processing/remesh_planar_patches.h>
#include <CGAL/Polygon_mesh_processing/repair_degeneracies.h>
#include "remesh_almost_planar.h"

inline void remesh_planar(Mesh mesh, Mesh& output) {
	Mesh remeshed;
	int prim = mesh.size_of_facets();

	PMP::remesh_planar_patches(mesh, remeshed);
	if (remeshed.size_of_facets() == 0) {
		return;
	}
	mesh = remeshed;
	
	int remesh_one = mesh.size_of_facets();

	remesh_almost_planar(mesh, 0.6, 1);

	if (mesh.is_empty()) {
		return;
	}

	int remesh_two = mesh.size_of_facets();
	
	std::cout << "prim:" << prim << " remesh_one:" << remesh_one - prim << " remesh_two:" << remesh_two - remesh_one << std::endl;

	if (!mesh.is_empty() && mesh.is_closed() && CGAL::is_triangle_mesh(mesh)) {
		output = mesh;
	}
}
