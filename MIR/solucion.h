#ifndef RECUPERACIONINFORMACIONMUSICAL_SOLUCION_H
#define RECUPERACIONINFORMACIONMUSICAL_SOLUCION_H
#include "definiciones.h"

// EJ 1
bool formatoValido(audio a, int canal, int profundidad);
bool enRangoProfundidad(audio a, int p);
int limiteProfundidad(int p);

// EJ 2
audio replicar(audio a, int canal, int profundidad);
void replicarEnCanal(const audio &a, int canal, audio &replica, int i);

// EJ 3
audio revertirAudio(audio a, int canal, int profundidad);
void revertirBloque(const audio &a, int canal, audio &revertido, int i);

// EJ 4
void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos);
void maximosPorCanal(const audio &a, int canal, int i, vector<int> &maximos, vector<int> &posicionesMaximos);

// EJ 5
audio redirigir(audio a, int c, int p);
int clip(int n, int p);

// EJ 6
void bajarCalidad(vector<audio> &as, int p, int p2);
void bajaCalidadAudio(audio &a, int p, int p2);
double disminuirEn(int p, int p2);

// EJ 7
void audiosSoftYHard(vector<audio> sa, int p, int largo, int umbral, vector<audio>& soft, vector<audio>& hard);
bool esSoft(audio a, int largo, int umbral);

// EJ 8
void reemplazarSubAudio(audio& a, audio a1, audio a2, int p);
bool enSubAudio(audio a, int i, audio subaudio);
audio concat (audio v1, audio v2);

// EJ 9
//void maximosTemporales(audio a, int p, vector<int> tiempos, vector<tuple<int,int>> &intervalos, vector<int> &maximos);
void maximosTemporales(audio a, int p, vector<int> tiempos, vector<tuple<int,int>> &intervalos, vector<int> &maximos);
void agregarIntervalos(vector<tuple<int,int>> &intervalos, int size, int t);
void agregarMaximo(vector<int> &maximos, audio &a, tuple<int,int> intervalo, int cota_min);
int encontrarMaximo(audio &a, int desde, int hasta, int cota_min);

// EJ 10
void limpiarAudio(audio& a, int profundidad, vector<int>& atipicos);
bool esOutlier(audio &audioOrdenado, int n, int percentil);
int reemplazoNoOutlier(audio a, int i, audio audioOrdenado, int percentil);
int posNoOutlierIzq (audio &audioOrdenado, audio &a, int i, int percentil);
int posNoOutlierDer (audio &audioOrdenado, audio &a, int i, int percentil);
void selectionSort(audio &s);
int encontrarPosMin(audio &s, int d, int h);
void swap(audio &s, int i, int j);


#endif //RECUPERACIONINFORMACIONMUSICAL_SOLUCION_H
