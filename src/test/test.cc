#include <iostream>

#include "../model.h"
#include <gtest/gtest.h>
#define kEpsilon 1e-05

// Тест на масштабирование

TEST(s21_3D_Viewer_test, scaling) {
    
    ObjModel test_object;
    
    std::vector<Vector3> vertices;
    std::vector<Edge> edges;

    vertices.emplace_back(1.0, 1.0, 1.0);
    edges.emplace_back(2, 2);
    
    test_object.vertices = vertices;
    test_object.edges = edges;

    test_object.scaling(2.0);
    

    EXPECT_NEAR(2.0, test_object.vertices[0].x, kEpsilon);
    EXPECT_NEAR(2.0, test_object.vertices[0].y, kEpsilon);
    EXPECT_NEAR(2.0, test_object.vertices[0].z, kEpsilon);
}

TEST(s21_3D_Viewer_test, scaling_2) {
    
    ObjModel test_object;
    
    std::vector<Vector3> vertices;
    std::vector<Edge> edges;

    vertices.emplace_back(1.0, 1.0, 1.0);
    edges.emplace_back(2, 2);
    
    test_object.vertices = vertices;
    test_object.edges = edges;

    test_object.scaling(-3.0);
    

    EXPECT_NEAR(1/3.0, test_object.vertices[0].x, kEpsilon);
    EXPECT_NEAR(1/3.0, test_object.vertices[0].y, kEpsilon);
    EXPECT_NEAR(1/3.0, test_object.vertices[0].z, kEpsilon);
}

// Тест на сдвиг

TEST(s21_3D_Viewer_test, move) {
    
    ObjModel test_object;
    
    std::vector<Vector3> vertices;
    std::vector<Edge> edges;

    vertices.emplace_back(1.0, 1.0, 1.0);
    edges.emplace_back(2, 2);
    
    test_object.vertices = vertices;
    test_object.edges = edges;

    test_object.move_object(2.0, 3.0, 1.0);
    

    EXPECT_NEAR(3.0, test_object.vertices[0].x, kEpsilon);
    EXPECT_NEAR(4.0, test_object.vertices[0].y, kEpsilon);
    EXPECT_NEAR(2.0, test_object.vertices[0].z, kEpsilon);
}

// Тест на поворот

TEST(s21_3D_Viewer_test, rotate) {
    
    ObjModel test_object;
    
    std::vector<Vector3> vertices;
    std::vector<Edge> edges;

    vertices.emplace_back(1.0, 1.0, 1.0);
    edges.emplace_back(2, 2);
    
    test_object.vertices = vertices;
    test_object.edges = edges;

    test_object.rotate_model(2.0, 3.0, 1.0);
    

    EXPECT_NEAR(1.0, test_object.vertices[0].x, kEpsilon);
    EXPECT_NEAR(1.0, test_object.vertices[0].y, kEpsilon);
    EXPECT_NEAR(1.0, test_object.vertices[0].z, kEpsilon);
}

// Тест на загрузку

TEST(s21_3D_Viewer_test, load) {
    
    ObjModel test_object;

    test_object.parse("./test/cube_325");
    

    EXPECT_NEAR(-0.5, test_object.vertices[0].x, kEpsilon);
    EXPECT_NEAR(0.5, test_object.vertices[0].y, kEpsilon);
    EXPECT_NEAR(0.5, test_object.vertices[0].z, kEpsilon);

    EXPECT_NEAR(0.5, test_object.vertices[1].x, kEpsilon);
    EXPECT_NEAR(0.5, test_object.vertices[1].y, kEpsilon);
    EXPECT_NEAR(0.5, test_object.vertices[1].z, kEpsilon);

    EXPECT_NEAR(0.5, test_object.vertices[2].x, kEpsilon);
    EXPECT_NEAR(-0.5, test_object.vertices[2].y, kEpsilon);
    EXPECT_NEAR(0.5, test_object.vertices[2].z, kEpsilon);

    EXPECT_NEAR(-0.5, test_object.vertices[3].x, kEpsilon);
    EXPECT_NEAR(-0.5, test_object.vertices[3].y, kEpsilon);
    EXPECT_NEAR(0.5, test_object.vertices[3].z, kEpsilon);

    EXPECT_NEAR(-0.5, test_object.vertices[4].x, kEpsilon);
    EXPECT_NEAR(0.5, test_object.vertices[4].y, kEpsilon);
    EXPECT_NEAR(-0.5, test_object.vertices[4].z, kEpsilon);

    EXPECT_NEAR(0.5, test_object.vertices[5].x, kEpsilon);
    EXPECT_NEAR(0.5, test_object.vertices[5].y, kEpsilon);
    EXPECT_NEAR(-0.5, test_object.vertices[5].z, kEpsilon);

    EXPECT_NEAR(0.5, test_object.vertices[6].x, kEpsilon);
    EXPECT_NEAR(-0.5, test_object.vertices[6].y, kEpsilon);
    EXPECT_NEAR(-0.5, test_object.vertices[6].z, kEpsilon);

    EXPECT_NEAR(-0.5, test_object.vertices[7].x, kEpsilon);
    EXPECT_NEAR(-0.5, test_object.vertices[7].y, kEpsilon);
    EXPECT_NEAR(-0.5, test_object.vertices[7].z, kEpsilon);

    EXPECT_NEAR(8.0, test_object.vertices_count, kEpsilon);
}

// Тест на ошибку чтения файла

TEST(s21_3D_Viewer_test, error_read) {
    
    ObjModel test_object;

    test_object.parse("./test/error");
    
}

// Тест на загрузку из файла

TEST(s21_3D_Viewer_test, load_from_file) {
    
    ObjModel test_object;

    bool result = test_object.load_file("./test/cube_325");
    EXPECT_TRUE (result);
    
}

