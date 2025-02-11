#include "controller.h"

namespace s21 {

bool _3DViewer_controller::load_obj_from_file(std::string file_name) {
  return model->load_file(file_name);
};

const std::vector<Edge>& _3DViewer_controller::getEdges() const {
  return model->getEdges();
}
const std::vector<Vector3>& _3DViewer_controller::getVertices() const {
  return model->getVertices();
}

int _3DViewer_controller::getVerticesCount() const {
  return model->getVerticesCount();
};
int _3DViewer_controller::getEdgesCount() const {
  return model->getEdgesCount();
};

void _3DViewer_controller::move_object(float x, float y, float z) {
  model->move_object(x, y, z);
};

void _3DViewer_controller::rotate_model(float x, float y, float z) {
  model->rotate_model(x, y, z);
};

void _3DViewer_controller::scaling(float scale) { model->scaling(scale); };
};  // end of namespace s21
