#include "../h/typedefs/typedefs_mesh.h"
#include "../h/typedefs/io.h"
#include <CGAL/Polygon_mesh_processing/measure.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>
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

	/*for (size_t i = 0; i < meshes.size(); i++) {
		std::cout << std::format("offsetting:({}/{})<{}>:",i+1, meshes.size(), meshes[i].size_of_facets());
		meshes[i] = mesh_offset(meshes[i], offset_const);
		std::cout << std::format("offsetted:({})\n", meshes[i].size_of_facets());
	}*/

	int last_remeshed_fasets_size = 0;

	Mesh first = meshes[0];
	for (size_t i = 1; i < meshes.size(); i++) {
		std::cout << std::format("unioning:({}/{}) ", i + 1, meshes.size());

		if (first.size_of_facets() - last_remeshed_fasets_size > 5000) {
			remesh_planar(first);
			last_remeshed_fasets_size = first.size_of_facets();
		}

		Mesh result;
		if (PMP::corefine_and_compute_union(first, meshes[i], result)) {
			first = result;
		}
		else {
			std::cout << std::format("fail:<corefine_and_compute_union>\n");
			remesh_planar(first);

			std::cout << std::format("re_offsetting:");
			Mesh offset = mesh_offset(meshes[i], offset_const);
			std::cout << std::format("re_offsetted:({})\n", offset.size_of_facets());

			if (!PMP::corefine_and_compute_union(first, offset, result)) {
			#ifdef DEBUG
				save_to(first, path_m1);
				save_to(meshes[i], path_m2);
			#endif // DEBUG
				throw std::exception("fail:<union_meshes>");
			}

			first = result;
		}
		std::cout << std::format("united:({})\n", first.size_of_facets());
	}

	remesh_planar(first);

	//remesh_almost_planar(first);	

	save_to(first, path_mesh_output);
}