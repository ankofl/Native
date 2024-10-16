#include "../h/typedefs/typedefs_mesh.h"
#include "../h/typedefs/io.h"

#include <CGAL/Polygon_mesh_processing/corefinement.h>

inline void boolean_mesh_1_mesh_2(
	const std::string& path_mesh_1, 
	const std::string& path_mesh_2,
	const size_t type,
	const std::string& path_mesh_output) {
	Mesh m1 = load_from(path_mesh_1), m2 = load_from(path_mesh_2), result;
	if (type == 0) {
		if (PMP::corefine_and_compute_union(m1, m2, result)) {
			save_to(result, path_mesh_output);
		}
	}
	else if (type == 1) {
		if (PMP::corefine_and_compute_intersection(m1, m2, result)) {
			save_to(result, path_mesh_output);
		}
	}
	else {
		if (PMP::corefine_and_compute_difference(m1, m2, result)) {
			save_to(result, path_mesh_output);
		}
	}
}
