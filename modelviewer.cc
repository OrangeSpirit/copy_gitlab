#include "modelviewer.h"

ModelViewer::ModelViewer(QWidget* parent) : QOpenGLWidget(parent) {}

void ModelViewer::setModelData(const std::vector<Vector3>& vertices,
                               const std::vector<Edge>& edges) {
  this->vertices = vertices;
  this->edges = edges;
  update();
}

void ModelViewer::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);
  glEnable(GL_DEPTH_TEST);
}

void ModelViewer::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspectRatio = (float)w / (float)h;
  glFrustum(-aspectRatio, aspectRatio, -1.0, 1.0, 2.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void ModelViewer::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLineWidth(lineWidth);
  glLoadIdentity();
  glTranslatef(0.0f, -4.0f, -11.0f);

  glColor3f(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());

  if (lineStyle == Qt::DashLine) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glBegin(GL_LINES);
  for (size_t i = 0; i < edges.size(); i++) {
    const Vector3& v1 = vertices[edges[i].v1];
    const Vector3& v2 = vertices[edges[i].v2];
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
  }
  glEnd();

  glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
  glPointSize(vertexSize);
  glBegin(GL_POINTS);
  for (size_t i = 0; i < vertices.size(); i++) {
    const auto& vertex = vertices[i];
    glVertex3f(vertex.x, vertex.y, vertex.z);
  }

  glEnd();

  if (lineStyle == Qt::DashLine) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void ModelViewer::setBackgroundColor(const QColor& color) {
  backgroundColor = color;
  update();
}

void ModelViewer::setLineWidth(float width) {
  lineWidth = width;
  update();
}

void ModelViewer::setLineStyle(Qt::PenStyle style) {
  lineStyle = style;
  update();
}

void ModelViewer::setEdgeColor(const QColor& color) {
  edgeColor = color;
  update();
}

void ModelViewer::setVertexColor(const QColor& color) {
  vertexColor = color;
  update();
}

void ModelViewer::setVertexSize(float size) {
  vertexSize = size;
  update();
}

void ModelViewer::saveFrameAsJpeg() {
  // Сохраняем содержимое OpenGL в QImage
  QString filePath = QFileDialog::getSaveFileName(
      this, "Сохранить кадр", QDir::currentPath(), "Images (*.jpg)");

  // Если выбран файл, сохраняем
  if (!filePath.isEmpty()) {
    filePath += ".jpg";
    QImage image = grabFramebuffer();
    if (!image.save(filePath, "JPG")) {
      qWarning("Не удалось сохранить изображение в файл: %s",
               qPrintable(filePath));
    }
  }
}

void ModelViewer::saveFrameAsBMP() {
  // Сохраняем содержимое OpenGL в QImage
  QString filePath = QFileDialog::getSaveFileName(
      this, "Сохранить кадр", QDir::currentPath(), "Images (*.bmp)");

  // Если выбран файл, сохраняем
  if (!filePath.isEmpty()) {
    filePath += ".bmp";
    QImage image = grabFramebuffer();
    if (!image.save(filePath, "BMP")) {
      qWarning("Не удалось сохранить изображение в файл: %s",
               qPrintable(filePath));
    }
  }
}

void ModelViewer::startGif() {
  gif = new QGifImage(QSize(640, 480));
  gif->setDefaultDelay(100);
  isRecord = true;
}

int ModelViewer::getFrameCount() {
  if (isRecord) {
    return gif->frameCount();
  } else {
    return -1;
  }
}

void ModelViewer::addFrameToGif() {
  if (!isRecord) {
    return;
  }

  QImage image;
  image = grabFramebuffer();
  image =
      image.scaled(640, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  gif->addFrame(image);
}

void ModelViewer::endGif(QString filepath) {
  if (!isRecord) {
    return;
  }

  if (!filepath.isEmpty()) {
    filepath += ".gif";
    gif->save(filepath);
  }

  delete gif;
}

void ModelViewer::move_object(float x, float y, float z) {
  for (size_t i = 0; i < this->vertices.size(); ++i) {
    if (x != 0) this->vertices[i].x += x;
    if (y != 0) this->vertices[i].y += y;
    if (z != 0) this->vertices[i].z += z;
  }
}

void ModelViewer::rotate_model(float x, float y, float z) {
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

    if (x != 0) {
      // Поворот OX точки относительно центра
      float newStartY = startY * cos(rad_x) - startZ * sin(rad_x);
      float newStartZ = startY * sin(rad_x) + startZ * cos(rad_x);

      // Обновление координат точки после поворота
      this->vertices[i].y = newStartY + centerY;
      this->vertices[i].z = newStartZ + centerZ;
    }

    if (y != 0) {
      // Поворот OY точки относительно центра
      float newStartX = startX * cos(rad_y) + startZ * sin(rad_y);
      float newStartZ = -startX * sin(rad_y) + startZ * cos(rad_y);

      // Обновление координат точки после поворота
      this->vertices[i].x = newStartX + centerX;
      this->vertices[i].z = newStartZ + centerZ;
    }
    if (z != 0) {
      // Поворот OZ точки относительно центра
      float newStartX = startX * cos(rad_z) - startY * sin(rad_z);
      float newStartY = startX * sin(rad_z) + startY * cos(rad_z);

      // Обновление координат точки после поворота
      this->vertices[i].x = newStartX + centerX;
      this->vertices[i].y = newStartY + centerY;
    }
  }
}

// Масштабирование объекта
void ModelViewer::scaling(float size) {
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
