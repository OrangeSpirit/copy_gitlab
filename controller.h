#ifndef MODELCONTROLLER_H
#define MODELCONTROLLER_H

#include "model.h"

namespace s21 {
class _3DViewer_controller {
 private:
  ObjModel* model;

 public:
  _3DViewer_controller(ObjModel* m) : model(m){};
  bool load_obj_from_file(std::string file_name);
  const std::vector<Edge>& getEdges() const;
  const std::vector<Vector3>& getVertices() const;

  int getVerticesCount() const;
  int getEdgesCount() const;
  void move_object(float x, float y, float z);
  void rotate_model(float x, float y, float z);
  void scaling(float scale);
};
};  // end of namespace s21

#endif