#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <math.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Vector3 {
  float x, y, z;

  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Edge {
  int v1, v2;

  Edge(int v1, int v2) : v1(v1), v2(v2) {}
};

class ObjModel {
 public:
  int edges_count = 0;
  int vertices_count = 0;
  std::vector<Vector3> vertices;
  std::vector<Edge> edges;

  bool parse(const std::string& filePath);

  const std::vector<Vector3>& getVertices() const { return vertices; }
  const std::vector<Edge>& getEdges() const { return edges; }

  int getVerticesCount() const { return vertices_count; }
  int getEdgesCount() const { return edges_count; }

  bool load_file(std::string file_name);

  void move_object(float x, float y, float z);
  void rotate_model(float x, float y, float z);
  void scaling(float size);

 private:
  int parseVertexIndex(const std::string& vertexInfo);
};

#endif  // OBJMODEL_H
