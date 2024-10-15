#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/Polygon_mesh_processing/remesh_planar_patches.h>
#include <CGAL/Polygon_mesh_processing/repair_degeneracies.h>
#include "remesh_almost_planar.h"

inline Mesh& remesh_planar(Mesh& mesh) {	
	int prim = mesh.size_of_facets();

	Mesh remeshed;
	PMP::remesh_planar_patches(mesh, remeshed);
	mesh = remeshed;

	int after = mesh.size_of_facets();
	
	if (prim != after) {
		std::cout << "remeshed:" << after - prim << std::endl;
	}
	
	return mesh;
}
