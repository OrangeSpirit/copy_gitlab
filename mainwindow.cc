#include "mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include "parser.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    fileNameEdit(new QLineEdit(nullptr)),
    moveSliderX(new QSlider(Qt::Horizontal, this)),
    moveSliderY(new QSlider(Qt::Horizontal, this)),
    modelViewer(new ModelViewer(this)),
    rotateXEdit(new QLineEdit(this)),
    rotateYEdit(new QLineEdit(this)),
    rotateZEdit(new QLineEdit(this)),
    rotateModelButton(new QPushButton("Rotate Model", nullptr)),
    scaleEdit(new QLineEdit(this)),
    scaleModelButton(new QPushButton("Scale Model", nullptr)),
    timer(new QTimer(this))
{
    setWindowTitle("3D Viewer");
    resize(1600, 1600); 
    setupUI();

    connect(timer, SIGNAL(timeout()), this, SLOT(update_gif()));
}

MainWindow::~MainWindow() {}

void MainWindow::createFileSelectionUI(QVBoxLayout* layout) {
    fileNameEdit = new QLineEdit(this);
    fileNameEdit->setPlaceholderText("File name");

    fileNameLabel = new QLabel("File: Not selected", this);   
    vertexCountLabel = new QLabel("Vertices: 0", this);          
    edgeCountLabel = new QLabel("Edges: 0", this);              

    QPushButton *selectFileButton = new QPushButton("Select model file", this);
    connect(selectFileButton, &QPushButton::clicked, this, &MainWindow::onSelectFileClicked);

    layout->addWidget(fileNameEdit);
    layout->addSpacing(10); 

    layout->addWidget(selectFileButton);
    layout->addWidget(fileNameLabel);       
    layout->addWidget(vertexCountLabel);    
    layout->addWidget(edgeCountLabel); 
}


void MainWindow::createMoveUI(QVBoxLayout* layout) {
    QLabel *moveLabelX = new QLabel("Move X:", this);
    moveSliderX->setRange(-2, 2);
    connect(moveSliderX, &QSlider::valueChanged, this, &MainWindow::onMoveModelButtonClicked);

    QLabel *moveLabelY = new QLabel("Move Y:", this);
    moveSliderY->setRange(-2, 2);
    connect(moveSliderY, &QSlider::valueChanged, this, &MainWindow::onMoveModelButtonClicked);

    layout->addWidget(moveLabelX);
    layout->addWidget(moveSliderX);
    layout->addWidget(moveLabelY);
    layout->addWidget(moveSliderY);
}

void MainWindow::createRotateUI(QVBoxLayout* layout) {
    QLabel *rotateLabelX = new QLabel("Rotate X (degrees):", this);
    rotateXEdit->setPlaceholderText("0");

    QLabel *rotateLabelY = new QLabel("Rotate Y (degrees):", this);
    rotateYEdit->setPlaceholderText("0");

    QLabel *rotateLabelZ = new QLabel("Rotate Z (degrees):", this);
    rotateZEdit->setPlaceholderText("0");

    rotateModelButton = new QPushButton("Rotate Model", this);
    connect(rotateModelButton, &QPushButton::clicked, this, &MainWindow::onRotateModelButtonClicked);

    layout->addWidget(rotateLabelX);
    layout->addWidget(rotateXEdit);
    layout->addWidget(rotateLabelY);
    layout->addWidget(rotateYEdit);
    layout->addWidget(rotateLabelZ);
    layout->addWidget(rotateZEdit);
    layout->addWidget(rotateModelButton);
}

void MainWindow::createScaleUI(QVBoxLayout* layout) {
    QLabel *scaleLabel = new QLabel("Scale (e.g., 1.0):", this);
    scaleEdit->setPlaceholderText("1.0");

    scaleModelButton = new QPushButton("Scale Model", this);
    connect(scaleModelButton, &QPushButton::clicked, this, &MainWindow::onScaleModelButtonClicked);

    layout->addWidget(scaleLabel);
    layout->addWidget(scaleEdit);
    layout->addWidget(scaleModelButton);
}

void MainWindow::createScreenJpgUI(QVBoxLayout* layout) {
    QPushButton *screenJpgButton = new QPushButton("Jpeg", this);
    layout->addWidget(screenJpgButton);
    connect(screenJpgButton, &QPushButton::clicked, this, &MainWindow::onScreenJpgButtonClicked);
}

void MainWindow::createScreenBMPUI(QVBoxLayout* layout) {
    QPushButton *screenBMPButton = new QPushButton("BMP", this);
    layout->addWidget(screenBMPButton);
    connect(screenBMPButton, &QPushButton::clicked, this, &MainWindow::onScreenBMPButtonClicked);
}

void MainWindow::createScreenGifUI(QVBoxLayout* layout) {
    QPushButton *screenGifButton = new QPushButton("Gif", this);
    layout->addWidget(screenGifButton);
    connect(screenGifButton, &QPushButton::clicked, this, &MainWindow::onScreenGifButtonClicked);
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(centralWidget);

    QVBoxLayout *fileLayout = new QVBoxLayout();
    createFileSelectionUI(fileLayout);
    layout->addLayout(fileLayout, 0, 0, 2, 1);

    modelViewer->setMinimumSize(800, 600);
    layout->addWidget(modelViewer, 0, 1, 6, 1);  

    QVBoxLayout *moveLayout = new QVBoxLayout();
    createMoveUI(moveLayout);
    layout->addLayout(moveLayout, 2, 0, 1, 1); 

    QVBoxLayout *rotateLayout = new QVBoxLayout();
    createRotateUI(rotateLayout);
    layout->addLayout(rotateLayout, 3, 0, 1, 1); 

    QVBoxLayout *scaleLayout = new QVBoxLayout();
    createScaleUI(scaleLayout);
    layout->addLayout(scaleLayout, 4, 0, 1, 1);

    QVBoxLayout *screenJpgLayout = new QVBoxLayout(); // Jpeg
    createScreenJpgUI(screenJpgLayout);
    layout->addLayout(screenJpgLayout, 5, 0, 1, 1);

    QVBoxLayout *screenBMPLayout = new QVBoxLayout(); // BMP
    createScreenBMPUI(screenBMPLayout);
    layout->addLayout(screenBMPLayout, 6, 0, 1, 1);

    QVBoxLayout *screenGifLayout = new QVBoxLayout(); // Gif
    createScreenGifUI(screenGifLayout);
    layout->addLayout(screenGifLayout, 7, 0, 1, 1);
    
    layout->setRowStretch(1, 1);  
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 1);
    layout->setRowStretch(5, 1);

    
    adjustUIElements();

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}


void MainWindow::adjustUIElements() {
    rotateModelButton->setFixedSize(100, 30);
    scaleModelButton->setFixedSize(100, 30);
    moveSliderX->setFixedWidth(150);
    moveSliderY->setFixedWidth(150);

    fileNameEdit->setFixedWidth(200);
    rotateXEdit->setFixedWidth(60);
    rotateYEdit->setFixedWidth(60);
    rotateZEdit->setFixedWidth(60);
    scaleEdit->setFixedWidth(60);
}

// Обработка выбора файла
void MainWindow::onSelectFileClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Model File", "", "Model Files (*.obj *.stl);;All Files (*)");
    if (!filePath.isEmpty()) {
        fileNameEdit->setText(filePath);

        ObjParser parser;
        if (parser.parse(filePath.toStdString())) {
            qDebug() << "Файл успешно распарсен!";
            const auto& vertices = parser.getVertices();
            const auto& edges = parser.getEdges();
            modelViewer->setModelData(vertices, edges);

            fileNameLabel->setText("File: " + filePath);                    
            vertexCountLabel->setText("Vertices: " + QString::number(vertices.size()));  
            edgeCountLabel->setText("Edges: " + QString::number(edges.size())); 
            modelViewer->update();
        } else {
            qDebug() << "Ошибка парсинга файла.";
        }
    }
}

// Обработка перемещения модели
void MainWindow::onMoveModelButtonClicked()
{
    int xValue = moveSliderX->value();
    modelViewer->move_x(xValue);
    int yValue = moveSliderY->value();
     modelViewer->move_y(yValue);
    qDebug() << "Move Model: X = " << xValue << ", Y = " << yValue;
    modelViewer->update();
}

// Обработка поворота модели
void MainWindow::onRotateModelButtonClicked()
{
    float rotateX = rotateXEdit->text().toFloat();
    

    modelViewer->rotate_ox (rotateX);

    float rotateY = rotateYEdit->text().toFloat();
    
    modelViewer->rotate_oy (rotateY);
    float rotateZ = rotateZEdit->text().toFloat();
        modelViewer->rotate_oz (rotateZ);

    qDebug() << "Rotate Model: X = " << rotateX << ", Y = " << rotateY << ", Z = " << rotateZ;
    modelViewer->update();
}

// Обработка масштабирования модели
void MainWindow::onScaleModelButtonClicked()
{
    float scale = scaleEdit->text().toFloat();
    modelViewer->scaling (scale);
    qDebug() << "Scale Model: Factor = " << scale;
    modelViewer->update();
}

// Скрин в формате Jpeg
void MainWindow::onScreenJpgButtonClicked()
{
    modelViewer->saveFrameAsJpeg();
}

// Скрин в формате BMP
void MainWindow::onScreenBMPButtonClicked()
{
    modelViewer->saveFrameAsBMP();
}

// Скрин в формате Gif (640x480, 10fps, 5s)
void MainWindow::onScreenGifButtonClicked()
{
    modelViewer->startGif();
    timer->start(100);
}

void MainWindow::update_gif() 
{
    if (modelViewer->getFrameCount() >= 0 && modelViewer->getFrameCount() < 50) {
        modelViewer->addFrameToGif();
    } else if (modelViewer->getFrameCount() >= 50) {
        timer->stop();
        QString filePath = QFileDialog::getSaveFileName(
            this,
            "Сохранить кадр",
            QDir::currentPath(), // Стартовая директория
            "Images (*.gif)"
        );
        modelViewer->endGif(filePath);
    } else {
        timer->stop();
    }
}