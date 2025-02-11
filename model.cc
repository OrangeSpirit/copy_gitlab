#include "model.h"

// Метод для парсинга индекса вершины из строки "v/vt/vn"
int ObjModel::parseVertexIndex(const std::string& vertexInfo) {
  std::istringstream iss(vertexInfo);
  std::string indexStr;
  std::getline(iss, indexStr, '/');  // Берём первую часть до символа '/'
  return std::stoi(indexStr) - 1;  // Индексы в OBJ начинаются с 1, вычитаем 1
                                   // для преобразования в 0-базовый индекс
}

// Метод для чтения и парсинга OBJ файла
bool ObjModel::parse(const std::string& filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть файл " << filePath << std::endl;
    return false;
  }
  this->edges.clear();
  this->vertices.clear();
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

bool ObjModel::load_file(std::string file_name) {
  bool result = false;
  if (this->parse(file_name)) result = true;
  return result;
}

void ObjModel::move_object(float x, float y, float z) {
  for (size_t i = 0; i < this->vertices.size(); ++i) {
    if (x != 0) this->vertices[i].x += x;
    if (y != 0) this->vertices[i].y += y;
    if (z != 0) this->vertices[i].z += z;
  }
}

// Поворот объекта

void ObjModel::rotate_model(float x, float y, float z) {
  double rad_x = x * M_PI / 180.0;
  double rad_y = y * M_PI / 180.0;
  double rad_z = z * M_PI / 180.0;

  // Находим центр объекта
  float sumX = 0, sumY = 0, sumZ = 0;
  for (size_t i = 0; i < this->vertices.size(); ++i) {
    sumX += this->vertices[i].x;
    sumY += this->vertices[i].y;
    sumZ += this->vertices[i].z;
  }

  float centerX = sumX / this->vertices.size();
  float centerY = sumY / this->vertices.size();
  float centerZ = sumZ / this->vertices.size();

  for (size_t i = 0; i < this->vertices.size(); ++i) {
    float startX = this->vertices[i].x - centerX;
    float startY = this->vertices[i].y - centerY;
    float startZ = this->vertices[i].z - centerZ;

    float newStartX = startX;
    float newStartY = startY;
    float newStartZ = startZ;

    // Поворот OX
    if (x != 0) {
      float tmpY = newStartY;
      newStartY = tmpY * cos(rad_x) - newStartZ * sin(rad_x);
      newStartZ = tmpY * sin(rad_x) + newStartZ * cos(rad_x);
    }

    // Поворот OY
    if (y != 0) {
      float tmpX = newStartX;
      newStartX = tmpX * cos(rad_y) + newStartZ * sin(rad_y);
      newStartZ = -tmpX * sin(rad_y) + newStartZ * cos(rad_y);
    }

    // Поворот OZ
    if (z != 0) {
      float tmpX = newStartX;
      float tmpY = newStartY;
      newStartX = tmpX * cos(rad_z) - tmpY * sin(rad_z);
      newStartY = tmpX * sin(rad_z) + tmpY * cos(rad_z);
    }

    // Обновление координат с учетом центра
    this->vertices[i].x = newStartX + centerX;
    this->vertices[i].y = newStartY + centerY;
    this->vertices[i].z = newStartZ + centerZ;
  }
}

// Масштабирование объекта
void ObjModel::scaling(float size) {
  for (size_t i = 0; i < this->vertices.size(); ++i) {
    if (size > 0) {
      this->vertices[i].x *= size;
      this->vertices[i].y *= size;
      this->vertices[i].z *= size;
    } else if (size < 0) {
      this->vertices[i].x *= 1 / abs(size);
      this->vertices[i].y *= 1 / abs(size);
      this->vertices[i].z *= 1 / abs(size);
    }
  }
}