#include <iostream>
#include <fstream>
#include <vector>

namespace s21 {

struct vector3  {
    private:
        float x,y,z;
    
    public:
        vector3 (float x_, float y_, float z_) : x(x_), y(y_), z(z_){}; 
};

struct edges    {
    private:
        int v1, v2;
    public:
        edges (int v1_, int v2_) : v1(v1_), v2(v2_){};
};

class model {

private:
    int edges_count;
    int vertices_count;
    std::vector<edges> edges;
    std::vector<vector3> vertices;

public:

    model() {};
    void read_file(std::ifstream *file_name){}; // Парсер файла .obj
    void rotate_ox(float corner){}; // Поворот объекта по оси OX
    void rotate_oy(float corner){}; // Поворот объекта по оси OY
    void rotate_oz(float corner){}; // Поворот объекта по оси OZ
    void move_x(int pixels){}; // Сдвиг по оси x
    void move_y(int pixels){}; // Сдвиг по оси y
    void move_z(int pixels){}; // Сдвиг по оси z
    void scaling(int size){}; // Масштабирование объекта

};



};

int main()    {
using namespace s21;

model new_model;

return 0;
}