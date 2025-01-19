#include "modelviewer.h"

ModelViewer::ModelViewer(QWidget *parent) : QOpenGLWidget(parent){
    setMinimumSize(700, 700);
    resize(1500, 1500);
    }

void ModelViewer::setModelData(const std::vector<Vector3>& vertices, const std::vector<Edge>& edges) {
    this->vertices = vertices;
    this->edges = edges;
    update();  
}

void ModelViewer::saveFrameAsJpeg() {
    // Сохраняем содержимое OpenGL в QImage
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Сохранить кадр",
        QDir::currentPath(), // Стартовая директория
        "Images (*.jpg)"
        );

    // Если пользователь выбрал файл, сохраняем
    if (!filePath.isEmpty()) {
        filePath += ".jpg";
        QImage image = grabFramebuffer();
        if (!image.save(filePath, "JPG")) {
            qWarning("Не удалось сохранить изображение в файл: %s", qPrintable(filePath));
        }
    }
}

void ModelViewer::saveFrameAsBMP() {
    // Сохраняем содержимое OpenGL в QImage
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Сохранить кадр",
        QDir::currentPath(), // Стартовая директория
        "Images (*.bmp)"
        );

    // Если пользователь выбрал файл, сохраняем
    if (!filePath.isEmpty()) {
        filePath += ".bmp";
        QImage image = grabFramebuffer();
        if (!image.save(filePath, "BMP")) {
            qWarning("Не удалось сохранить изображение в файл: %s", qPrintable(filePath));
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
    image = image.scaled(640, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
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

void ModelViewer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Черный фон
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity(); 
    glTranslatef(0.0f, 0.0f, -15.0f); 

    glBegin(GL_LINES);
    for (size_t i = 0; i < edges.size(); ++i) {
        const Vector3& v1 = vertices[edges[i].v1];
        const Vector3& v2 = vertices[edges[i].v2];
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
}
    glEnd();

}










