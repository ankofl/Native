
#include "typedefs_std.h"
#include "read_args_from_file.h"
#include "boolean_mesh_1_mesh_2.cpp"
#include "answer_utils.h"

int main() {
    std::vector<std::string> args = read_args_from_file(path_data); // ������ ��������� �� �����    

    // ���������, ��� ������ args �������� ������ ���������� ����������
    if (!args.empty() && args[0] == start_boolean_mesh_1_mesh_2 && args.size() == 5) {
        boolean_mesh_1_mesh_2(
            args[1],            // ������ �������� ��� ������
            args[2],            // ������ �������� ��� ������
            std::stoull(args[3]), // ������ �������� ��� size_t
            args[4]);           // �������� �������� ��� ������
    }
    else {
        answer_add("incorrect_args");
    }

    return 0;
}
