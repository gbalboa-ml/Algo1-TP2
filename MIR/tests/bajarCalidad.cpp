#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(bajarCalidadTEST, listaVacia){
    vector<audio> as = {};
    int profundidad1 = 4;
    int profundidad2 = 2;
    vector<audio> esperado = {};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_MATRIX(as, esperado);
}

TEST(bajarCalidadTEST, listaSoloUnVector){
    audio a1 = {0,-8,0,8,14,12,6,0,-2,2,6,8,6,-2,-10,-16,-13,-8,-2,0};
    vector<audio> as = {a1};
    int profundidad1 = 5;
    int profundidad2 = 4;
    audio audioEsperado1 = {0,-4,0,4,7,6,3,0,-1,1,3,4,3,-1,-5,-8,-7,-4,-1,0};
    vector<audio> esperado = {audioEsperado1};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_MATRIX(as, esperado);
}

//OJO!! La especificación dice redondear para abajo, por lo tanto se usa la función floor. Al redondear para abajo un número
// negativo, se toma el menor número. Ej: floor (-13) = -7 en lugar de -6. El test del TP1 dice que debería dar -6, lo que no concuerda
// con la especificación dada para el TP.
TEST(bajarCalidadTEST, listaDosVectores){
    audio a1 = {0,-8,0,8,14,12,6,0,-2,2,6,8,6,-2,-10,-16,-13,-8,-2,0};
    audio a2 = {0,4,6,20,-9,-17,14,-8,9,6,-5};
    vector<audio> as = {a1, a2};
    int profundidad1 = 5;
    int profundidad2 = 3;
    audio audioEsperado1 = {0,-2,0,2,3,3,1,0,-1,0,1,2,1,-1,-3,-4,-4,-2,-1,0};
    audio audioEsperado2 = {0,1,1,5,-3,-5,3,-2,2,1,-2};
    vector<audio> esperado = {audioEsperado1, audioEsperado2};

    bajarCalidad(as, profundidad1, profundidad2);
    ASSERT_MATRIX(as, esperado);
}