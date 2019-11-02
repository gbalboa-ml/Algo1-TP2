#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(limpiarAudioTEST, audioSinOutliers){
    audio a = {1};
    audio outliers;
    int profundidad = 6;
    audio audioEsperado = {1};
    audio outliersEsperado;

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}

TEST(limpiarAudioTEST, audioConOutliers){
    audio a = {5,6,3,5,4,8,5,3,2,5,67,4,7,4};
    audio outliers;
    int profundidad = 6;
    audio audioEsperado = {5,6,3,5,4,8,5,3,2,5,4,4,7,4};
    audio outliersEsperado = {10};

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}

TEST(limpiarAudioTEST, audioConOutliers2){
    audio a = {5,6,3,5,4,8,42,3,2,5,67,4,7,4};
    audio outliers;
    int profundidad = 6;
    audio audioEsperado = {5,6,3,5,4,8,42,3,2,5,4,4,7,4};
    audio outliersEsperado = {10};

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}

TEST(limpiarAudioTEST, audioConOutliers3){
    audio a = {5,6,3,5,4,8,42,3,2,5,67,4,7,4,3,4,5,6,2,3,5,6,4,2,6};
    audio outliers;
    int profundidad = 6;
    audio audioEsperado = {5,6,3,5,4,8,5,3,2,5,4,4,7,4,3,4,5,6,2,3,5,6,4,2,6};
    audio outliersEsperado = {6,10};

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}
