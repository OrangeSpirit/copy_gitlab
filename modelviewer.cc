#include "modelviewer.h"

ModelViewer::ModelViewer(QWidget *parent) : QOpenGLWidget(parent){ 
    }

void ModelViewer::setModelData(const std::vector<Vector3>& vertices, const std::vector<Edge>& edges) {
    this->vertices = vertices;
    this->edges = edges;
    update();  
}

void ModelViewer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), 1.0f);
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
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(), backgroundColor.blueF(), 1.0f);
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
        this,
        "Сохранить кадр",
        QDir::currentPath(),
        "Images (*.jpg)"
        );

    // Если выбран файл, сохраняем
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
        QDir::currentPath(),
        "Images (*.bmp)"
        );

    // Если выбран файл, сохраняем
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








