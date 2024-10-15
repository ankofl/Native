#pragma once
#include "../typedefs/typedefs_mesh.h"
#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include "mesh_decompose.h"
#include "mesh_expand.h"

inline Mesh mesh_offset(Mesh& mesh, double offset) {
	Mesh output;

	std::vector<Mesh> meshes = mesh_decompose(mesh);
	
	output = meshes[0];
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

	if (output.is_empty()) {
		throw std::exception("fail:<mesh_offset>");
	}

	return output;
}
