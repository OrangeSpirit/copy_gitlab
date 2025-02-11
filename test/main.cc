#include "../model.h"
#include <gtest/gtest.h>


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Инициализация Google Test
    return RUN_ALL_TESTS();  // Запуск всех тестов
}