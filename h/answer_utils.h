#pragma once
#include "typedefs/typedefs_std.h"

inline void answer_add(const std::string& msg) {
    std::ofstream file(path_data, std::ios::app); // ��������� ���� � ������ ����������

    if (file.is_open()) {
        file << msg << std::endl; // ��������� msg � ����� ������
        file.close(); // ��������� ����
    }
}

inline void answer_clear() {
    std::ofstream file(path_data, std::ios::trunc); // ��������� ���� � ������ "trunc", ������� ������� ����
    if (file.is_open()) {
        // ���� ������� ������, �� �� ������ �� ����������, ��� ��� ��� ��� �������
        file.close(); // ��������� ����
    }
}