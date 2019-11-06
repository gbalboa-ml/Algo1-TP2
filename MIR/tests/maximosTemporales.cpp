#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(maximosTemporalesTEST, test){
    audio a = {33,25,-1,3,1};
    vector<int> tiempos = {3,2};
    vector<tuple<int,int>> intervalos = {};
    vector <int> maximos = {};
    vector <int> maximosEsperados = {3, 3, 33, 1, 33};

    int profundidad = 5;

    vector<tuple<int,int>> intervalosEsperados = {make_tuple(2, 3), make_tuple(3, 5), make_tuple(0, 2), make_tuple(4, 5), make_tuple(0, 1)};

    maximosTemporales(a, profundidad, tiempos, intervalos, maximos);

    ASSERT_VECTOR_TUPLES(intervalos, intervalosEsperados);
    ASSERT_VECTOR(maximos, maximosEsperados);
}
