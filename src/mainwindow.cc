#include "mainwindow.h"

#include "model.h"

MainWindow::MainWindow(s21::_3DViewer_controller *_controller, QWidget *parent)
    : QMainWindow(parent),
      controller(_controller),
      fileNameEdit(new QLineEdit(nullptr)),
      moveXEdit(new QLineEdit(this)),
      moveYEdit(new QLineEdit(this)),
      moveZEdit(new QLineEdit(this)),
      moveModelButton(new QPushButton("Move Model", this)),
      modelViewer(new ModelViewer(this)),
      rotateXEdit(new QLineEdit(this)),
      rotateYEdit(new QLineEdit(this)),
      rotateZEdit(new QLineEdit(this)),
      rotateModelButton(new QPushButton("Rotate Model", nullptr)),
      scaleEdit(new QLineEdit(this)),
      scaleModelButton(new QPushButton("Scale Model", nullptr)),
      selectFileButton(new QPushButton("Select model file", this)),
      applyLineWidthButton(new QPushButton("Apply Line Width", nullptr)),
      lineStyleComboBox(new QComboBox(nullptr)),
      changeEdgeColorButton(new QPushButton("Change Edge Color", this)),
      vertexColorButton(new QPushButton("Change Vertex Color", this)),
      lineWidthEdit(new QLineEdit("1.0", this)),
      vertexSizeEdit(new QLineEdit(this)),
      changeVertexSizeButton(new QPushButton("Change Vertex Size", this)),
      timer(new QTimer(this)) {
  setWindowTitle("3D Viewer");
  resize(1600, 1600);
  setupUI();

  connect(timer, SIGNAL(timeout()), this, SLOT(update_gif()));
}

MainWindow::~MainWindow() {}

void MainWindow::createFileSelectionUI(QVBoxLayout *layout) {
  fileNameEdit->setPlaceholderText("File name");

  fileNameLabel = new QLabel("File: Not selected", this);
  vertexCountLabel = new QLabel("Vertices: 0", this);
  edgeCountLabel = new QLabel("Edges: 0", this);

  connect(selectFileButton, &QPushButton::clicked, this,
          &MainWindow::onSelectFileClicked);

  layout->addWidget(fileNameEdit);
  layout->addSpacing(10);
  layout->addWidget(selectFileButton);
  layout->addWidget(fileNameLabel);
  layout->addWidget(vertexCountLabel);
  layout->addWidget(edgeCountLabel);
}

void MainWindow::createMoveUI(QVBoxLayout *layout) {
  QLabel *moveLabelX = new QLabel("Move X:", this);
  moveXEdit->setPlaceholderText("0");

  QLabel *moveLabelY = new QLabel("Move Y:", this);
  moveYEdit->setPlaceholderText("0");

  QLabel *moveLabelZ = new QLabel("Move Z:", this);
  moveZEdit->setPlaceholderText("0");

  connect(moveModelButton, &QPushButton::clicked, this,
          &MainWindow::onMoveModelButtonClicked);

  layout->addWidget(moveLabelX);
  layout->addWidget(moveXEdit);
  layout->addWidget(moveLabelY);
  layout->addWidget(moveYEdit);
  layout->addWidget(moveLabelZ);
  layout->addWidget(moveZEdit);
  layout->addWidget(moveModelButton);
}

void MainWindow::createRotateUI(QVBoxLayout *layout) {
  QLabel *rotateLabelX = new QLabel("Rotate X (degrees):", this);
  rotateXEdit->setPlaceholderText("0");

  QLabel *rotateLabelY = new QLabel("Rotate Y (degrees):", this);
  rotateYEdit->setPlaceholderText("0");

  QLabel *rotateLabelZ = new QLabel("Rotate Z (degrees):", this);
  rotateZEdit->setPlaceholderText("0");

  connect(rotateModelButton, &QPushButton::clicked, this,
          &MainWindow::onRotateModelButtonClicked);

  layout->addWidget(rotateLabelX);
  layout->addWidget(rotateXEdit);
  layout->addWidget(rotateLabelY);
  layout->addWidget(rotateYEdit);
  layout->addWidget(rotateLabelZ);
  layout->addWidget(rotateZEdit);
  layout->addWidget(rotateModelButton);
}

void MainWindow::createScaleUI(QVBoxLayout *layout) {
  QLabel *scaleLabel = new QLabel("Scale (e.g., 1.0):", this);
  scaleEdit->setPlaceholderText("1.0");

  connect(scaleModelButton, &QPushButton::clicked, this,
          &MainWindow::onScaleModelButtonClicked);

  layout->addWidget(scaleLabel);
  layout->addWidget(scaleEdit);
  layout->addWidget(scaleModelButton);
}

void MainWindow::createBackgroundColorUI(QVBoxLayout *layout) {
  changeBackgroundColorButton =
      new QPushButton("Change Background Color", this);
  connect(changeBackgroundColorButton, &QPushButton::clicked, this,
          &MainWindow::onChangeBackgroundColor);
  layout->addWidget(changeBackgroundColorButton);
}

void MainWindow::createEdgeSettingsUI(QVBoxLayout *layout) {
  connect(applyLineWidthButton, &QPushButton::clicked, this,
          &MainWindow::onApplyLineWidthButtonClicked);

  layout->addWidget(lineWidthEdit);
  layout->addWidget(applyLineWidthButton);
}

void MainWindow::createTypeEdgeUI(QVBoxLayout *layout) {
  lineStyleComboBox->addItem("Solid Line");
  lineStyleComboBox->addItem("Dashed Line");

  connect(lineStyleComboBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(onApplyTypeEdgeButtonClicked(int)));

  layout->addWidget(lineStyleComboBox);
}

void MainWindow::createVertexSizeUI(QVBoxLayout *layout) {
  vertexSizeEdit->setPlaceholderText("1.0");

  connect(changeVertexSizeButton, &QPushButton::clicked, this,
          &MainWindow::onChangeVertexSizeButtonClicked);

  layout->addWidget(vertexSizeEdit);
  layout->addWidget(changeVertexSizeButton);
}

void MainWindow::createScreenJpgUI(QVBoxLayout *layout) {
  QPushButton *screenJpgButton = new QPushButton("Jpeg", this);
  layout->addWidget(screenJpgButton);
  connect(screenJpgButton, &QPushButton::clicked, this,
          &MainWindow::onScreenJpgButtonClicked);
}

void MainWindow::createScreenBMPUI(QVBoxLayout *layout) {
  QPushButton *screenBMPButton = new QPushButton("BMP", this);
  layout->addWidget(screenBMPButton);
  connect(screenBMPButton, &QPushButton::clicked, this,
          &MainWindow::onScreenBMPButtonClicked);
}

void MainWindow::createScreenGifUI(QVBoxLayout *layout) {
  QPushButton *screenGifButton = new QPushButton("Gif", this);
  layout->addWidget(screenGifButton);
  connect(screenGifButton, &QPushButton::clicked, this,
          &MainWindow::onScreenGifButtonClicked);
}

void MainWindow::setupUI() {
  QWidget *centralWidget = new QWidget(this);
  QGridLayout *layout = new QGridLayout(centralWidget);

  QVBoxLayout *fileLayout = new QVBoxLayout();
  createFileSelectionUI(fileLayout);
  layout->addLayout(fileLayout, 0, 0, 1, 1);

  modelViewer->setMinimumSize(800, 800);
  layout->addWidget(modelViewer, 0, 2, 9, 1);

  QVBoxLayout *moveLayout = new QVBoxLayout();
  createMoveUI(moveLayout);
  layout->addLayout(moveLayout, 1, 0, 1, 1);

  QVBoxLayout *rotateLayout = new QVBoxLayout();
  createRotateUI(rotateLayout);
  layout->addLayout(rotateLayout, 2, 0, 1, 1);

  QVBoxLayout *scaleLayout = new QVBoxLayout();
  createScaleUI(scaleLayout);
  layout->addLayout(scaleLayout, 3, 0, 1, 1);

  QVBoxLayout *backgroundColorLayout = new QVBoxLayout();
  createBackgroundColorUI(backgroundColorLayout);
  layout->addLayout(backgroundColorLayout, 5, 0, 1, 1);

  QVBoxLayout *lineThicknessLayout = new QVBoxLayout();
  createEdgeSettingsUI(lineThicknessLayout);
  layout->addLayout(lineThicknessLayout, 0, 1, 1, 1);

  QVBoxLayout *lineTypeLayout = new QVBoxLayout();
  createTypeEdgeUI(lineTypeLayout);
  layout->addLayout(lineTypeLayout, 1, 1, 1, 1);

  connect(changeEdgeColorButton, &QPushButton::clicked, this,
          &MainWindow::onChangeEdgeColor);
  layout->addWidget(changeEdgeColorButton, 2, 1, 1, 1);

  connect(vertexColorButton, &QPushButton::clicked, this,
          &MainWindow::onChangeVertexColor);
  layout->addWidget(vertexColorButton, 3, 1, 1, 1);

  QVBoxLayout *vertexSizeLayout = new QVBoxLayout();
  createVertexSizeUI(vertexSizeLayout);
  layout->addLayout(vertexSizeLayout, 4, 0, 1, 1);

  QVBoxLayout *screenJpgLayout = new QVBoxLayout();  // Jpeg
  createScreenJpgUI(screenJpgLayout);
  layout->addLayout(screenJpgLayout, 6, 0, 1, 1);

  QVBoxLayout *screenBMPLayout = new QVBoxLayout();  // BMP
  createScreenBMPUI(screenBMPLayout);
  layout->addLayout(screenBMPLayout, 7, 0, 1, 1);

  QVBoxLayout *screenGifLayout = new QVBoxLayout();  // Gif
  createScreenGifUI(screenGifLayout);
  layout->addLayout(screenGifLayout, 8, 0, 1, 1);

  adjustUIElements();

  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);
}

void MainWindow::adjustUIElements() {
  rotateModelButton->setFixedSize(100, 30);
  scaleModelButton->setFixedSize(100, 30);
  moveModelButton->setFixedSize(100, 30);
  changeBackgroundColorButton->setFixedSize(200, 30);
  selectFileButton->setFixedSize(150, 30);
  applyLineWidthButton->setFixedSize(150, 30);
  changeEdgeColorButton->setFixedSize(150, 30);
  vertexColorButton->setFixedSize(150, 30);
  changeVertexSizeButton->setFixedSize(150, 30);

  fileNameLabel->setWordWrap(true);
  fileNameLabel->setFixedWidth(200);
  fileNameEdit->setFixedWidth(200);
  moveXEdit->setFixedWidth(60);
  moveYEdit->setFixedWidth(60);
  moveZEdit->setFixedWidth(60);
  rotateXEdit->setFixedWidth(60);
  rotateYEdit->setFixedWidth(60);
  rotateZEdit->setFixedWidth(60);
  scaleEdit->setFixedWidth(60);
  lineWidthEdit->setFixedWidth(60);
  vertexSizeEdit->setFixedWidth(60);
}

// Обработка выбора файла
void MainWindow::onSelectFileClicked() {
  QString filePath = QFileDialog::getOpenFileName(this, "Open Model File", "",
                                                  "Model Files (*.obj)");

  if (!filePath.isEmpty()) {
    fileNameEdit->setText(filePath);

    if (controller->load_obj_from_file(filePath.toStdString()) == true) {
      qDebug() << "Файл успешно распарсен!";

      modelViewer->setModelData(controller->getVertices(),
                                controller->getEdges());

      fileNameLabel->setText("File: " + filePath);
      vertexCountLabel->setText(
          "Vertices: " + QString::number(controller->getVerticesCount()));
      edgeCountLabel->setText("Edges: " +
                              QString::number(controller->getEdgesCount()));

      modelViewer->update();
    } else {
      qDebug() << "Ошибка парсинга файла.";
    }
  }
}

// Обработка перемещения модели
void MainWindow::onMoveModelButtonClicked() {
  float xValue = moveXEdit->text().toFloat();
  float yValue = moveYEdit->text().toFloat();
  float zValue = moveZEdit->text().toFloat();

  controller->move_object(xValue, yValue, zValue);
  modelViewer->setModelData(controller->getVertices(), controller->getEdges());
  modelViewer->update();
}

// Обработка поворота модели
void MainWindow::onRotateModelButtonClicked() {
  float rotateX = rotateXEdit->text().toFloat();
  float rotateY = rotateYEdit->text().toFloat();
  float rotateZ = rotateZEdit->text().toFloat();
  controller->rotate_model(rotateX, rotateY, rotateZ);
  modelViewer->setModelData(controller->getVertices(), controller->getEdges());
  modelViewer->update();
}

// Обработка масштабирования модели
void MainWindow::onScaleModelButtonClicked() {
  float scale = scaleEdit->text().toFloat();
  controller->scaling(scale);
  modelViewer->setModelData(controller->getVertices(), controller->getEdges());
  modelViewer->update();
}

void MainWindow::onChangeBackgroundColor() {
  QColor color =
      QColorDialog::getColor(Qt::white, this, "Select Background Color");

  if (color.isValid()) {
    modelViewer->setBackgroundColor(color);
    qDebug() << "Background color changed to:" << color.name();
  }
}

void MainWindow::onApplyLineWidthButtonClicked() {
  bool ok;
  float width = lineWidthEdit->text().toFloat(&ok);
  if (ok) {
    modelViewer->setLineWidth(width);
  } else {
    qDebug() << "Invalid line width!";
  }
}

void MainWindow::onApplyTypeEdgeButtonClicked(int index) {
  if (index == 0) {
    modelViewer->setLineStyle(Qt::SolidLine);
  } else if (index == 1) {
    modelViewer->setLineStyle(Qt::DashLine);
  }
}

void MainWindow::onChangeEdgeColor() {
  QColor color = QColorDialog::getColor(Qt::black, this, "Select Edge Color");

  if (color.isValid()) {
    modelViewer->setEdgeColor(color);
    qDebug() << "Edge color changed to:" << color.name();
  }
}

void MainWindow::onChangeVertexColor() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Vertex Color");

  if (color.isValid()) {
    modelViewer->setVertexColor(color);
    qDebug() << "Vertex color changed to:" << color.name();
  }
}

void MainWindow::onChangeVertexSizeButtonClicked() {
  bool ok;
  float size = vertexSizeEdit->text().toFloat(&ok);
  if (ok) {
    modelViewer->setVertexSize(size);
  } else {
    qDebug() << "Invalid vertex size!";
  }
}

// Скрин в формате Jpeg
void MainWindow::onScreenJpgButtonClicked() { modelViewer->saveFrameAsJpeg(); }

// Скрин в формате BMP
void MainWindow::onScreenBMPButtonClicked() { modelViewer->saveFrameAsBMP(); }

// Скрин в формате Gif (640x480, 10fps, 5s)
void MainWindow::onScreenGifButtonClicked() {
  modelViewer->startGif();
  timer->start(100);
}

void MainWindow::update_gif() {
  if (modelViewer->getFrameCount() >= 0 && modelViewer->getFrameCount() < 50) {
    modelViewer->addFrameToGif();
  } else if (modelViewer->getFrameCount() >= 50) {
    timer->stop();
    QString filePath = QFileDialog::getSaveFileName(
        this, "Сохранить кадр",
        QDir::currentPath(),  // Стартовая директория
        "Images (*.gif)");
    modelViewer->endGif(filePath);
  } else {
    timer->stop();
  }
}
