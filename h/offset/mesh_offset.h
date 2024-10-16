#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include "mesh_decompose.h"
#include "mesh_expand.h"
#include "expand.h"

const double offset_const = 0.00000001;

inline Mesh mesh_offset(Mesh& mesh, double offset) {
	std::cout << "offsetting... ";

	expand_polyhedron(mesh, offset);
	return mesh;

	std::vector<Mesh> meshes = mesh_decompose(mesh);
	
	Mesh output = meshes[0];
	if (meshes.size() == 1) {
		Mesh expand;
		if (mesh_expand(output, offset, expand)) {
			output = expand;
		}
	}
	else {
		// если больше одной составляющей
		for (size_t i = 1; i < meshes.size(); i++) {
			Mesh expand;
			if (mesh_expand(meshes[i], offset, expand)) {
				Mesh united;
				if (PMP::corefine_and_compute_union(output, expand, united)) {
					output = united;
				}
			}
		}
	}

	int after = output.size_of_facets();

	if (after == 0) {
		throw std::exception("fail:<mesh_offset>");
	}

	std::cout << std::format("offsetted:({})\n", after);

	return output;
}
