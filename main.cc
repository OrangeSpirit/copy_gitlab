#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  ObjModel cur_model{};
  s21::_3DViewer_controller cur_controller(&cur_model);

  QApplication app(argc, argv);

  MainWindow mainWindow(&cur_controller);
  mainWindow.show();

  return app.exec();
}
