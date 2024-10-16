#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/Polygon_mesh_processing/remesh_planar_patches.h>
#include <CGAL/Polygon_mesh_processing/repair_degeneracies.h>
#include "remesh_almost_planar.h"

inline Mesh& remesh_planar(Mesh& mesh) {	
	int prim = mesh.size_of_facets();

	std::cout << "remeshing... ";

	Mesh remeshed;
	PMP::remesh_planar_patches(mesh, remeshed);
	mesh = remeshed;

	//remesh_almost_planar(mesh);

	int after = mesh.size_of_facets();
	
	if (after == 0) {
		throw std::exception("fail:<remesh_planar>");
	}

	std::cout << std::format("remeshed:<{}> ({})\n", after - prim, after);
	
	return mesh;
}
