#pragma once
#include "typedefs/typedefs_std.h"

inline void answer_add(const std::string& msg) {
    std::ofstream file(path_data, std::ios::app); // Открываем файл в режиме добавления

    if (file.is_open()) {
        file << msg << std::endl; // Добавляем msg в новую строку
        file.close(); // Закрываем файл
    }
}

inline void answer_clear() {
    std::ofstream file(path_data, std::ios::trunc); // Открываем файл в режиме "trunc", который очищает файл
    if (file.is_open()) {
        // Файл успешно открыт, но мы ничего не записываем, так как это его очистит
        file.close(); // Закрываем файл
    }
}