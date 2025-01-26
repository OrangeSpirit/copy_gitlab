#ifndef OBJPARSER_H
#define OBJPARSER_H

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

class ObjParser {
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

 private:
  int parseVertexIndex(const std::string& vertexInfo);
};

#endif  // OBJPARSER_H
