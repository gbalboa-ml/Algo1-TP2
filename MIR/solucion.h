#ifndef RECUPERACIONINFORMACIONMUSICAL_SOLUCION_H
#define RECUPERACIONINFORMACIONMUSICAL_SOLUCION_H
#include "definiciones.h"

bool formatoValido(audio a, int canal, int profundidad);
bool formatoValido(audio a, int canal, int profundidad);
audio replicar(audio a, int canal, int profundidad);
audio revertirAudio(audio a, int canal, int profundidad);
void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos);
audio redirigir(audio a, int canal, int profundidad);
void bajarCalidad(vector<audio> & as, int profundidad1, int profundidad2);
void audiosSoftYHard(vector<audio> as, int profundidad, int longitud, int umbral, vector<audio>& soft, vector<audio>& hard);
void reemplazarSubAudio(audio& a, audio a1, audio a2, int profundidad);
void limpiarAudio(audio& a, int profundidad, vector<int>& atipicos);
int clip(int n, int p);
void bajarCalidad(vector<vector<int>> &as, int p, int p2);
bool enSubAudio(vector<int> audio, int i, vector<int> subaudio);
bool esOutlier(audio &audioOrdenado, int n, int percentil);
void selectionSort(audio &s);
int reemplazoNoOutlier(audio a, int i, audio audioOrdenado, int percentil);
void bajaCalidadAudio(vector<int> &a, int p, int p2);
vector<int> concat (vector<int> v1, vector<int> v2);
void maximosTemporales(vector<int> a, int p, vector<int> tiempos, vector<tuple<int,int>> &intervalos, vector<int> &maximos);

#endif //RECUPERACIONINFORMACIONMUSICAL_SOLUCION_H
