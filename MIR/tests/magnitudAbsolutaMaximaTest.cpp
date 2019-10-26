#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(magnitudAbsolutaMaximaTEST, unCanal){
    audio a = {1,2,3,-2};
    int canal = 1;
    int profundidad = 6;
    audio maximos, posicionesMaximos = {};

    audio maximosEsperados = {3};
    audio posicionesMaximosEsperados = {2};

    magnitudAbsolutaMaxima(a, canal, profundidad, maximos, posicionesMaximos);

    ASSERT_VECTOR(maximos, maximosEsperados);
    ASSERT_VECTOR(posicionesMaximos, posicionesMaximosEsperados);
}

TEST(magnitudAbsolutaMaximaTEST, dosCanales){
    audio a = {1,2,3,-2,7,8,-3,-4};
    int canal = 2;
    int profundidad = 6;
    audio maximos, posicionesMaximos = {};

    audio maximosEsperados = {7,8};
    audio posicionesMaximosEsperados = {4,5};

    magnitudAbsolutaMaxima(a, canal, profundidad, maximos, posicionesMaximos);

    ASSERT_VECTOR(maximos, maximosEsperados);
    ASSERT_VECTOR(posicionesMaximos, posicionesMaximosEsperados);
}

TEST(magnitudAbsolutaMaximaTEST, dosCanalesMaximosNegativos){
    audio a = {1,2,3,-2,-7,-8,-3,-4,6,7};
    int canal = 2;
    int profundidad = 6;
    audio maximos, posicionesMaximos = {};

    audio maximosEsperados = {-7,-8};
    audio posicionesMaximosEsperados = {4,5};

    magnitudAbsolutaMaxima(a, canal, profundidad, maximos, posicionesMaximos);

    ASSERT_VECTOR(maximos, maximosEsperados);
    ASSERT_VECTOR(posicionesMaximos, posicionesMaximosEsperados);
}

TEST(magnitudAbsolutaMaximaTEST, dosCanalesTodosCero){
    audio a = {0,0,0,0,0,0,0,0};
    int canal = 2;
    int profundidad = 6;
    audio maximos, posicionesMaximos = {};

    audio maximosEsperados = {0,0};
    audio posicionesMaximosEsperados = {6,7};

    magnitudAbsolutaMaxima(a, canal, profundidad, maximos, posicionesMaximos);

    ASSERT_VECTOR(maximos, maximosEsperados);
    ASSERT_VECTOR(posicionesMaximos, posicionesMaximosEsperados);
}