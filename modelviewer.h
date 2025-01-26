#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <vector>

#include "gif/qgifimage.h"
#include "mainwindow.h"
#include "parser.h"

class ModelViewer : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  ModelViewer(QWidget* parent = nullptr);
  ~ModelViewer() = default;

  void setModelData(const std::vector<Vector3>& vertices,
                    const std::vector<Edge>& edges);
  void setBackgroundColor(const QColor& color);

  void setLineWidth(float width);
  void setLineStyle(Qt::PenStyle style);
  void setEdgeColor(const QColor& color);
  void setVertexColor(const QColor& color);
  void setVertexSize(float size);

  void saveFrameAsJpeg();
  void saveFrameAsBMP();
  void startGif();
  int getFrameCount();
  void addFrameToGif();
  void endGif(QString filepath);

  void move_object(float x, float y, float z);
  void rotate_model(float x, float y, float z);
  void scaling(float size);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  std::vector<Vector3> vertices;
  std::vector<Edge> edges;

  QGifImage* gif;
  bool isRecord;
  QColor backgroundColor = QColor(0, 0, 0);
  float lineWidth = 1.0f;
  Qt::PenStyle lineStyle = Qt::SolidLine;
  QColor edgeColor = Qt::white;
  QColor vertexColor = Qt::red;
  float vertexSize = 1.0f;
};

#endif  // MODELVIEWER_H
