#ifndef RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
#define RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H

#include "definiciones.h"

//template<typename T>
bool vectoresOrdenadosIguales(vector<int> vector1, vector<int> vector2);
//template<typename T>
void ASSERT_VECTOR(vector<int> vector1, vector<int> vector2);
void ASSERT_MATRIX(vector<audio> mat1, vector<audio> mat2);
void ASSERT_VECTOR_TUPLES(vector<tuple<int,int>> vector1, vector<tuple<int,int>> vector2);

//Escribir y leer audio
void escribirAudio(audio a, string nombreArchivo, int c);
tuple<int, audio> leerAudio(string nombreArchivo);

//Graficos tiempos de ejecución
int indicePrimeraAparicion(vector<int>& v, int elem);
double calcularTiempoEjecucion(vector<int> vector);
void calcularTiempoEjecucionRevertir();
void calcularTiempoEjecucionLimpiar();


#endif //RECUPERACIONINFORMACIONMUSICAL_AUXILIARES_H
