#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <format>
#include <filesystem>

#ifdef DEBUG
const std::string path_data = "C:/dev/ankofl.Native/bin/Debug/data.txt";
#else
const std::string path_data = "C:/dev/ankofl.Native/bin/Debug/data.txt";
//const std::string path_data = "C:/Users/Public/ankofl/Native/1.0.1/data.txt";
#endif // DEBUG

const std::string start_boolean_mesh_1_mesh_2 = "start_boolean_mesh_1_mesh_2";
const std::string start_union_meshes = "start_union_meshes";