#include <iostream>
#include "gtest/gtest.h"
#include "auxiliares.h"



int main(int argc, char **argv) {
    std::cout << "Implementando TPI!!" << std::endl;
    calcularTiempoEjecucionRevertir();
    calcularTiempoEjecucionLimpiar();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}