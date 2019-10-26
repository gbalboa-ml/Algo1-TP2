#include "solucion.h"
#include "auxiliares.h"
#include <algorithm>

bool enRangoProfundidad(audio vector, int profundidad);

double limiteProfundidad(int p);

using namespace std;

bool formatoValido(audio a, int canal, int profundidad) {
    return a.size() > 0 && a.size() % canal == 0 && enRangoProfundidad(a, profundidad);
}

bool enRangoProfundidad(audio a, int p) {
    bool res = true;
    for (int x : a) {
        res = res && x >= - limiteProfundidad(p) && x <= (limiteProfundidad(p) - 1 );
    }
    return res;
}

double limiteProfundidad(int p) { return pow ((double)2, (double)(p - 1)); }

audio replicar(audio a, int canal, int profundidad) {
    return a;
}

audio revertirAudio(audio a, int canal, int profundidad) {
    return a;
}

void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos) {

}

audio redirigir(audio a, int canal, int profundidad) {
    return a;
}

void bajarCalidad(vector<audio> & as, int profundidad1, int profundidad2) {

}

void audiosSoftYHard(vector<audio> as, int profundidad, int longitud, int umbral, vector<audio>& soft, vector<audio>& hard) {

}

void reemplazarSubAudio(audio& a, audio a1, audio a2, int profundidad) {

}

void maximosTemporales(audio a, int profundidad, vector<int> tiempos, vector<int>& maximos, vector<pair<int,int> > &intervalos ) {

}

void limpiarAudio(audio& a, int profundidad, vector<int>& outliers) {


}

