// modelviewer.h
#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QFileDialog>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include "mainwindow.h"
#include "qgifimage.h"

class ModelViewer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    ModelViewer(QWidget *parent = nullptr);
    ~ModelViewer() = default;

    void setModelData(const std::vector<Vector3>& vertices, const std::vector<Edge>& edges);

    void saveFrameAsJpeg();
    void saveFrameAsBMP();
    void startGif();
    int getFrameCount();
    void addFrameToGif();
    void endGif(QString filepath);

    void rotate_ox(float corner){

         double rad = corner * M_PI / 180.0;
    double cosVal = cos(rad);
    double sinVal = sin(rad);

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

        // Поворот точки относительно центра
        float newStartY = startY * cosVal - startZ * sinVal;
        float newStartZ = startY * sinVal + startZ * cosVal;

        // Обновление координат точки после поворота
        this->vertices[i].y = newStartY + centerY;
        this->vertices[i].z = newStartZ + centerZ;
    }

    }; 

    void rotate_oy(float corner){
        double rad = corner * M_PI / 180.0;
double cosVal = cos(rad);
double sinVal = sin(rad);

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

    // Поворот точки относительно центра
    float newStartX = startX * cosVal + startZ * sinVal;
    float newStartZ = -startX * sinVal + startZ * cosVal;

    // Обновление координат точки после поворота
    this->vertices[i].x = newStartX + centerX;
    this->vertices[i].z = newStartZ + centerZ;
}

    };

    void rotate_oz(float corner) {
    double rad = corner * M_PI / 180.0;
    double cosVal = cos(rad);
    double sinVal = sin(rad);

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

        // Поворот точки относительно центра по оси Z
        float newStartX = startX * cosVal - startY * sinVal;
        float newStartY = startX * sinVal + startY * cosVal;

        // Обновление координат точки после поворота
        this->vertices[i].x = newStartX + centerX;
        this->vertices[i].y = newStartY + centerY;
    }
};

// Сдвиг по оси x
 void move_x(int pixels){
    
    for (size_t i = 0; i < this->vertices.size(); ++i) {
          this->vertices[i].x += pixels;

 }
 };
    void move_y(int pixels){
    for (size_t i = 0; i < this->vertices.size(); ++i) {
        this->vertices[i].y += pixels;

 }
    }; // Сдвиг по оси y

// Масштабирование объекта
    void scaling(float size){
        for (size_t i = 0; i < this->vertices.size(); ++i) {
        
        if (size > 0)   {
        this->vertices[i].x *= size;
        this->vertices[i].y *= size;
        this->vertices[i].z *= size;
        }
        else if (size < 0)  {
        this->vertices[i].x *= 1/abs(size);
        this->vertices[i].y *= 1/abs(size);
        this->vertices[i].z *= 1/abs(size);
        }
 }
    }; 

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    
    

private:
    std::vector<Vector3> vertices; 
    std::vector<Edge> edges;
    QGifImage *gif;       
    bool isRecord;
};

#endif // MODELVIEWER_H
