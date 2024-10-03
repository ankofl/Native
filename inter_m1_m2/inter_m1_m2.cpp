#include <iostream>
#include "..\dif_m1_m2\typedefs.h"

#include <CGAL/Polygon_mesh_processing/corefinement.h>

int main() {
	Mesh m1, m2, result;
	if (load_from(m1, "m1") &&
		load_from(m2, "m2")) {
		if (PMP::corefine_and_compute_intersection(m1, m2, result)) {
			save_to(result, "result");
		}		
	}
	return 0;
}
