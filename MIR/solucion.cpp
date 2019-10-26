#include "solucion.h"
#include "auxiliares.h"
#include <algorithm>

bool enRangoProfundidad(audio vector, int profundidad);

double limiteProfundidad(int p);

bool cumplePreReplicar(audio vector, int canal, int profundidad);

void replicarEnCanal(const audio &a, int canal, audio &replica, int i);

bool cumplePreRevertir(audio a, int canal, int profundidad);

void revertirBloque(const audio &a, int canal, audio &revertido, int i);

bool cumplePreMagnitudAbsMax(audio vector, int canal, int profundidad);

void maximosPorCanal(const audio &a, int canal, int i, vector<int> &maximos, vector<int> &posicionesMaximos);

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
    if (cumplePreReplicar(a, canal, profundidad)){
        audio replica;
        for (int i = 0; i < a.size(); ++i) {
            replicarEnCanal(a, canal, replica, i);
        }
        return replica;
    } else {
        return a;
    };
}

void replicarEnCanal(const audio &a, int canal, audio &replica, int i) {
    for (int j = i * canal; j < (i + 1) * canal; ++j) {
        replica.push_back(a[i]);
    }
}

bool cumplePreReplicar(audio a, int canal, int profundidad) {
    return canal > 0 && profundidad > 0 && formatoValido(a, 1, profundidad);
}

audio revertirAudio(audio a, int canal, int profundidad) {
    if (cumplePreRevertir(a, canal, profundidad)) {
        audio revertido;
        for (int i = 0; i < a.size() / canal; ++i) {
            revertirBloque(a, canal, revertido, i);
        }
        return revertido;
    } else {
        return a;
    }
}

void revertirBloque(const audio &a, int canal, audio &revertido, int i) {
    for (int j = 0; j < canal; ++j) {
        revertido.push_back(a[a.size() - canal * (i+1) + j]);
    }
}

bool cumplePreRevertir(audio a, int canal, int profundidad) {
    return canal > 0 && profundidad > 0 && formatoValido(a, canal, profundidad);
}

void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos) {
    if (cumplePreMagnitudAbsMax(a, canal, profundidad)){
        for (int i = 0; i < canal; ++i) {
            maximos.push_back(0);
            posicionesMaximos.push_back(i);
            maximosPorCanal(a, canal, i, maximos, posicionesMaximos);
        }
    }
}

//Como no especifica, si hay dos máximos decidimos tomar el último que encontramos (por eso el menor o igual en el if en lugar de menor)
void maximosPorCanal(const audio &a, int canal, int i, vector<int> &maximos, vector<int> &posicionesMaximos) {
    for (int j = 0; j < a.size() / canal; ++j) {
        int posicion = canal * j + i;
        if (abs(maximos[i]) <= abs(a [posicion])){
            maximos[i] = a[posicion];
            posicionesMaximos[i] = posicion;
        }
    }
}

bool cumplePreMagnitudAbsMax(audio a, int canal, int profundidad) {
    return canal > 0 && profundidad > 0 && formatoValido(a, canal, profundidad);
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

