#include "../h/typedefs/typedefs_mesh.h"
#include <CGAL/Polygon_mesh_processing/measure.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include "../h/load_dir.h"
#include "../h/remesh/remesh_planar.h"
#include <CGAL/Polygon_mesh_processing/autorefinement.h>
#include "../h/offset/mesh_offset.h"

inline void union_meshes(
	const std::string& path_meshes,
	const std::string& path_mesh_output) {

	std::vector<Mesh> meshes;
	if (!load_dir(path_meshes, meshes)) {
		return;
	}

	Mesh first = meshes[0];
	for (size_t i = 1; i < meshes.size(); i++) {
		Mesh result;
		if (PMP::corefine_and_compute_union(first, meshes[i], result)) {
			first = result;
		}
		else {
			remesh_planar(first, first);
			remesh_planar(meshes[i], meshes[i]);

			Mesh offset;
			if (mesh_offset(meshes[i], 0.000000001, offset)) {
				if (PMP::corefine_and_compute_union(first, offset, result)) {
					first = result;
				}
				else {
					save_to(first, std::format("C:/dev/data/Log/BBox/{}-one.off", i));
					save_to(meshes[i], std::format("C:/dev/data/Log/BBox/{}-two.off", i));
				}
			}				
		}
		std::cout << i + 1 << '/' << meshes.size() << std::endl;
	}

	remesh_planar(first, first);

	save_to(first, path_mesh_output);
}