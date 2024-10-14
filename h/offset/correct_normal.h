#pragma once
#include "../typedefs/typedefs_mesh.h"

inline V correct_normal(V normal) {
    // Функция для округления до ближайшего значения с точностью 0.05
    auto round_to_nearest = [](double value) {
        return std::round(value / 0.05) * 0.05;
    };

    // Округляем каждую из координат нормали
    double x = round_to_nearest(CGAL::to_double(normal.x()));
    double y = round_to_nearest(CGAL::to_double(normal.y()));
    double z = round_to_nearest(CGAL::to_double(normal.z()));
    V fp = V(x, y, z);
    double d = CGAL::sqrt(CGAL::to_double(fp.squared_length()));
    return V(x / d, y / d, z / d);
}
