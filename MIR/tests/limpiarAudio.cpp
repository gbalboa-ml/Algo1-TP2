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

/*TEST(limpiarAudioTEST, audioConOutliers){
    audio a = {5,6,3,5,4,8,5,3,2,5,67,4,7,4};
    audio outliers;
    int profundidad = 6;
    audio audioEsperado = {5,6,3,5,4,8,5,3,2,5,4,4,7,4};
    audio outliersEsperado = {10};

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}*/

/*TEST(limpiarAudioTEST, audioConOutliers2){
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
}*/

TEST(limpiarAudioTEST, audioConOutliersEnBordesYCentro){
    audio a = {100,1,2,3,4,5,6,7,8,99,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98};
    audio outliers;
    int profundidad = 8;
    audio audioEsperado = {1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,96,96};
    audio outliersEsperado = {0,9,97,98};

    limpiarAudio(a, profundidad, outliers);

    ASSERT_VECTOR(a, audioEsperado);
    ASSERT_VECTOR(outliers, outliersEsperado);
}