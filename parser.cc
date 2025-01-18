#include "parser.h"

// Метод для парсинга индекса вершины из строки "v/vt/vn"
int ObjParser::parseVertexIndex(const std::string& vertexInfo) {
    std::istringstream iss(vertexInfo);
    std::string indexStr;
    std::getline(iss, indexStr, '/'); // Берём первую часть до символа '/'
    return std::stoi(indexStr) - 1;   // Индексы в OBJ начинаются с 1, вычитаем 1 для преобразования в 0-базовый индекс
}

// Метод для чтения и парсинга OBJ файла
bool ObjParser::parse(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filePath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            // Парсинг вершины
            float x, y, z;
            iss >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        } else if (prefix == "f") {
            // Парсинг грани (рёбер)
            std::vector<int> faceVertices;
            std::string vertexInfo;
            while (iss >> vertexInfo) {
                // Индексы вершин могут быть представлены в формате "v/vt/vn"
                int vertexIndex = parseVertexIndex(vertexInfo);
                faceVertices.push_back(vertexIndex);
            }

            // Создание рёбер из индексов вершин
            for (size_t i = 0; i < faceVertices.size(); ++i) {
                int v1 = faceVertices[i];
                int v2 = faceVertices[(i + 1) % faceVertices.size()];
                edges.emplace_back(v1, v2);
            }
        }
    }
    

    file.close();

    // Обновляем счётчики
    vertices_count = vertices.size();
    edges_count = edges.size();

    return true;
}
