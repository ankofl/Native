#pragma once
#include "typedefs/typedefs_mesh.h"


inline bool load_dir(const std::string& directory, std::vector<Mesh>& meshes) {
	for (const auto& entry : std::filesystem::directory_iterator(directory)) {
		if (entry.is_regular_file() && entry.path().extension() == ".off") {
			Mesh loaded;
			if (load_from(loaded, entry.path().string())) {
				meshes.push_back(loaded);
			}
		}
	}
	return meshes.size() > 0;
}