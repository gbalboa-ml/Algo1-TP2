#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(reemplazarSubAudioTEST, unElementoYPresente){
    audio a = {1};
    audio a1 = {1};
    audio a2 = {3};
    int profundidad = 5;
    audio esperado = {3};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_VECTOR(a, esperado);
}

TEST(reemplazarSubAudioTEST, VariosElementosYPresentes){
    audio a = {25, -23, -9, 17, 93, 10};
    audio a1 = {-23, -9, 17};
    audio a2 = {-20,-2};
    int profundidad = 5;
    audio esperado = {25,-20,-2,93,10};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_VECTOR(a, esperado);
}

TEST(reemplazarSubAudioTEST, listaConSubAudio){
    audio a = {1,2,3,4,5};
    audio a1 = {2,3,4};
    audio a2 = {6,7};
    int profundidad = 8;
    audio esperado = {1,6,7,5};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_VECTOR(a, esperado);
}

TEST(reemplazarSubAudioTEST, listaSinSubAudio){
    audio a = {1,2,3,4,5};
    audio a1 = {6,7,8};
    audio a2 = {9,10};
    int profundidad = 8;
    audio esperado = {1,2,3,4,5};

    reemplazarSubAudio(a, a1, a2, profundidad);

    ASSERT_VECTOR(a, esperado);
}