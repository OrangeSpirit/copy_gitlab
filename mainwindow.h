#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QVBoxLayout>

#include "controller.h"
#include "modelviewer.h"

class ModelViewer;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(s21::_3DViewer_controller *controller,
                      QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void onSelectFileClicked();
  void onMoveModelButtonClicked();

  void onRotateModelButtonClicked();
  void onScaleModelButtonClicked();

  void onChangeBackgroundColor();
  void onApplyLineWidthButtonClicked();

  void onApplyTypeEdgeButtonClicked(int index);
  void onChangeEdgeColor();
  void onChangeVertexColor();
  void onChangeVertexSizeButtonClicked();

  void onScreenJpgButtonClicked();
  void onScreenBMPButtonClicked();
  void onScreenGifButtonClicked();

  void update_gif();

 private:
  QLabel *fileNameLabel;
  QLabel *vertexCountLabel;
  QLabel *edgeCountLabel;

  QLineEdit *fileNameEdit;
  ModelViewer *modelViewer;
  s21::_3DViewer_controller *controller;

  QLineEdit *moveXEdit;
  QLineEdit *moveYEdit;
  QLineEdit *moveZEdit;
  QPushButton *moveModelButton;

  QLineEdit *rotateXEdit;
  QLineEdit *rotateYEdit;
  QLineEdit *rotateZEdit;
  QPushButton *rotateModelButton;

  QLineEdit *scaleEdit;
  QPushButton *scaleModelButton;

  QPushButton *changeBackgroundColorButton;

  QPushButton *selectFileButton;

  QLineEdit *lineWidthEdit;
  QPushButton *applyLineWidthButton;

  QComboBox *lineStyleComboBox;

  QPushButton *changeEdgeColorButton;
  QPushButton *vertexColorButton;

  QLineEdit *vertexSizeEdit;
  QPushButton *changeVertexSizeButton;

  QPushButton *screenJpgButton;
  QPushButton *screenBMPButton;
  QPushButton *screenGifButton;

  QTimer *timer;

  void setupUI();
  void createFileSelectionUI(QVBoxLayout *layout);
  void createMoveUI(QVBoxLayout *layout);
  void createRotateUI(QVBoxLayout *layout);
  void createScaleUI(QVBoxLayout *layout);
  void adjustUIElements();
  void createBackgroundColorUI(QVBoxLayout *layout);
  void createEdgeSettingsUI(QVBoxLayout *layout);
  void createTypeEdgeUI(QVBoxLayout *layout);
  void createVertexSizeUI(QVBoxLayout *layout);
  void createScreenJpgUI(QVBoxLayout *layout);
  void createScreenBMPUI(QVBoxLayout *layout);
  void createScreenGifUI(QVBoxLayout *layout);
};

#endif  // MAINWINDOW_H
