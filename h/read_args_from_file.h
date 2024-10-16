#pragma once
#include "typedefs/typedefs_std.h"

inline bool read_args_from_file(const std::string& filepath, std::vector<std::string>& args) {
    std::ifstream file(filepath); // ��������� ���� ��� ������
    args.clear();

    if (file.is_open()) {
        std::string line;
        // ������ ��� ������ �� �����
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string word;
            // ��������� ������ �� �������� � ��������� ����� � ������
            while (iss >> word) {
                args.push_back(word);
            }
        }
        file.close();
    }
    return args.size() > 0;
}
