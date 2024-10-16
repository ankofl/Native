#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <format>
#include <filesystem>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifdef DEBUG
const std::string path_data = "C:/Users/Public/ankofl/native/bin/Debug/data.txt";
const std::string path_m1 = "C:/Users/Public/ankofl/native/bin/Debug/m1.off";
const std::string path_m2 = "C:/Users/Public/ankofl/native/bin/Debug/m2.off";
#else
const std::string path_data = "C:/Users/Public/ankofl/native/bin/Release/data.txt";
#endif // DEBUG

const std::string start_boolean_mesh_1_mesh_2 = "start_boolean_mesh_1_mesh_2";
const std::string start_union_meshes = "start_union_meshes";