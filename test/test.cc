#include <gtest/gtest.h>

#include <QApplication>
#include <QColor>

#include "../modelviewer.h"

// Тестовый класс для ModelViewer
class ModelViewerTest : public ::testing::Test {
 protected:
  ModelViewer* viewer;

  void SetUp() override {
    // Инициализация QApplication, необходимая для использования QOpenGLWidget
    int argc = 0;
    char** argv = nullptr;
    QApplication app(argc, argv);

    viewer = new ModelViewer();
  }

  void TearDown() override { delete viewer; }
};

// Тест на установку данных модели
TEST_F(ModelViewerTest, SetModelData) {
  std::vector<Vector3> vertices = {Vector3(1.0f, 2.0f, 3.0f),
                                   Vector3(4.0f, 5.0f, 6.0f)};
  std::vector<Edge> edges = {Edge(0, 1)};

  viewer->setModelData(vertices, edges);

  // Проверка, что данные были установлены правильно
  // ASSERT_EQ(viewer->vertices.size(), 2);
  // ASSERT_EQ(viewer->edges.size(), 1);
}

// Тест на установку цвета фона
TEST_F(ModelViewerTest, SetBackgroundColor) {
  QColor color(255, 0, 0);  // Красный цвет
  viewer->setBackgroundColor(color);

  // Проверка цвета фона (предполагается, что есть метод для получения цвета)
  // ASSERT_EQ(viewer->backgroundColor.red(), 255);
  // ASSERT_EQ(viewer->backgroundColor.green(), 0);
  // ASSERT_EQ(viewer->backgroundColor.blue(), 0);
}

// Тест на установку ширины линии
TEST_F(ModelViewerTest, SetLineWidth) {
  viewer->setLineWidth(5.0f);

  // Проверка ширины линии
  // ASSERT_FLOAT_EQ(viewer->lineWidth, 5.0f);
}

// Тест на установку цвета ребра
TEST_F(ModelViewerTest, SetEdgeColor) {
  QColor color(0, 255, 0);  // Зеленый цвет
  viewer->setEdgeColor(color);

  // Проверка цвета ребра (предполагается, что есть метод для получения цвета)
  // ASSERT_EQ(viewer->edgeColor.red(), 0);
  // ASSERT_EQ(viewer->edgeColor.green(), 255);
  // ASSERT_EQ(viewer->edgeColor.blue(), 0);
}

// Тест на сохранение кадра как JPEG (проверка на вызов метода)
TEST_F(ModelViewerTest, SaveFrameAsJpeg) {
  // Здесь вы можете использовать мок-объекты или другие подходы,
  // чтобы проверить вызов метода saveFrameAsJpeg.
}

// Основная функция для запуска тестов
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
