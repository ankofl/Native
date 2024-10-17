#include "h/read_args_from_file.h"
#include "cpp/boolean_mesh_1_mesh_2.cpp"
#include "cpp/union_meshes.cpp"

int main() {
    try {
        std::vector<std::string> args; // ������ ��������� �� ����� 
        if (read_args_from_file(path_data, args)) {
            if (args[0] == start_boolean_mesh_1_mesh_2 && args.size() == 5) {
                boolean_mesh_1_mesh_2(
                    args[1],            // ������ �������� ��� ������
                    args[2],            // ������ �������� ��� ������
                    std::stoull(args[3]), // ������ �������� ��� size_t
                    args[4]);           // �������� �������� ��� ������
            }
            else if (args[0] == start_union_meshes && args.size() == 3) {
                union_meshes(
                    args[1], // ���� � ����� � .off �������
                    args[2]);// ���� ���������� ������������ .off �����
            }
        }
    }
    catch (std::exception e) {
        std::cout << e.what();
        std::cin.get();
    }
    return 0;
}
