#include "solucion.h"
#include "auxiliares.h"
#include <algorithm>
#include <vector>
#include <tuple>
#include <math.h>

int abs(int n) {
    if (n<0) {
        return -n;
    } else {
        return n;
    }
}

using namespace std;

// EJ 1
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

int limiteProfundidad(int p) { return (int)pow ((double)2, (double)(p - 1)); }

// EJ 2
audio replicar(audio a, int canal, int profundidad) {
    audio replica;
    for (int i = 0; i < a.size(); ++i) {
        replicarEnCanal(a, canal, replica, i);
    }
    return replica;
}

void replicarEnCanal(const audio &a, int canal, audio &replica, int i) {
    for (int j = i * canal; j < (i + 1) * canal; ++j) {
        replica.push_back(a[i]);
    }
}

// EJ 3
audio revertirAudio(audio a, int canal, int profundidad) {
    audio revertido;
    for (int i = 0; i < a.size() / canal; ++i) {
        revertirBloque(a, canal, revertido, i);
    }
    return revertido;
}

void revertirBloque(const audio &a, int canal, audio &revertido, int i) {
    for (int j = 0; j < canal; ++j) {
        revertido.push_back(a[a.size() - canal * (i+1) + j]);
    }
}

// EJ 4
void magnitudAbsolutaMaxima(audio a, int canal, int profundidad, vector<int> &maximos, vector<int> &posicionesMaximos) {
    for (int i = 0; i < canal; ++i) {
        maximos.push_back(0);
        posicionesMaximos.push_back(i);
        maximosPorCanal(a, canal, i, maximos, posicionesMaximos);
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

// EJ 5
audio redirigir(audio a, int c, int p) {
    int inicio = 1; // me ubico en el canal 2 por defecto
    int direccion = -1;
    audio result = a;
    if (c==2) {
        inicio = 0;
        direccion = 1;
    }
    for (int i=inicio; i<a.size(); i=i+2) {
        result[i] = clip(a[i]-a[i+direccion],p);
    }
    return result;
}

int clip(int n, int p) {
    int cota_min = - limiteProfundidad(p);
    int cota_max = limiteProfundidad(p)-1;
    if (n>cota_max) {
        return cota_max;
    } else if (n<cota_min) {
        return cota_min;
    } else {
        return n;
    }
}

// EJ 6
void bajarCalidad(vector<audio> &as, int p, int p2) {
    for (audio &a : as) {
        bajaCalidadAudio(a,p,p2);
    }
}

void bajaCalidadAudio(audio &a, int p, int p2) {
    for (int &i : a) {
        i = floor(i / disminuirEn(p, p2));
    }
}

double disminuirEn(int p, int p2) { return pow((double)2, (double)p - p2); }

// EJ 7
bool esSoft(audio a, int largo, int umbral) {
    int superiores = 0;
    for (int i=0; i<a.size() && !(superiores > largo); i++) {
        if (a[i]>umbral) {
            superiores++;
        } else {
            superiores = 0;
        }
    }
    return !(superiores > largo);
}

void audiosSoftYHard(vector<audio> sa, int p, int largo, int umbral, vector<audio> &soft, vector<audio> &hard) {
    for(int audio=0; audio<sa.size(); audio++) {
        if (esSoft(sa[audio],largo,umbral)) {
            soft.push_back(sa[audio]);
        } else {
            hard.push_back(sa[audio]);
        }
    }
}

// EJ 8
/*void reemplazarSubAudio(audio &a, audio a1, audio a2, int p) {
    audio reemplazo = {};
    int reinicio;
    int i;
    for (i=0; i<a.size(); i++) {
        if (!enSubAudio(a,i,a1)) {
            reemplazo.push_back(a[i]);
        } else {
            reinicio = i+a1.size()
                    ;
            break;
        }
    }
    if (i<a.size()) {
        reemplazo = concat(reemplazo,a2);
        for (int j=reinicio; j<a.size(); j++) {
            reemplazo.push_back(a[j]);
        }
    }
    a = reemplazo;
}

bool enSubAudio(audio a, int i, audio subaudio) {
    int j=0;
    while (j<subaudio.size() && i+j < a.size() && subaudio[j] == a[i + j]) {
        j++;
    }
    return !(j<subaudio.size());
}

audio concat (audio v1, audio v2) {
    audio concatenado = v1;
    for (int i=0; i < v2.size(); i++) {
        concatenado.push_back(v2[i]);
    }
    return concatenado;
}*/
audio concat (audio v1, audio v2) {
    audio concatenado = v1;
    for (int i=0; i < v2.size(); i++) {
        concatenado.push_back(v2[i]);
    }
    return concatenado;
}

audio subseq(audio a, int inicio, int fin){
    audio subsecuencia;
    for (int i = inicio; i <= fin; ++i) {
        subsecuencia.push_back(a[i]);
    }
    return subsecuencia;
}

void reemplazarSubAudio(audio &a, audio a1, audio a2, int p){
    int inicio = -1;
    int fin = -1;
    int posAudio1 = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == a1[posAudio1]){
            if (posAudio1 == 0){
                inicio = i;
            }
            if (posAudio1 == a1.size()-1){
                fin = posAudio1;
                break;
            }
            posAudio1++;
        } else {
            posAudio1 = 0;
        }
    }
    if (fin != -1){
        audio respuesta = concat(concat(subseq(a, 0, inicio - 1), a2), subseq(a, inicio + a1.size(), a.size()-1));
        a = respuesta;
    }
}

// EJ 9
void maximosTemporales(audio a, int p, vector<int> tiempos, vector<tuple<int,int>> &intervalos, vector<int> &maximos) {
            intervalos = {};
            maximos = {};
    int cota_min = -pow(2, p-1);
    int maximoDelIntervalo;
    int ultimaPosAudio = a.size()-1;
    int ultimaPosIntervalo;
    for (int t=0; t<tiempos.size(); t++) {
        for (int j=0; j<a.size(); j++) {
            if (j%tiempos[t]==0) {
                        maximoDelIntervalo = cota_min;
                        ultimaPosIntervalo = j+tiempos[t]-1;
                tuple<int,int> intervalo = make_tuple(j,ultimaPosIntervalo);
                intervalos.push_back(intervalo);
            }
            if (a[j] > maximoDelIntervalo) {
                        maximoDelIntervalo = a[j];
            }
            if (j==ultimaPosIntervalo || j==ultimaPosAudio) {
                maximos.push_back(maximoDelIntervalo);
            }
        }
    }
}

// EJ 10
void swap(audio &s, int i, int j) {
    int aux = s[i];
    s[i] = s[j];
    s[j] = aux;
}

int encontrarPosMin(audio &s, int d, int h) {
    int min = d;
    for(int i=d+1; i<h; i++) {
        if (s[i] < s[min]) {
            min = i;
        }
    }
    return min;
}

void selectionSort(audio &s) {
    for(int i=0; i<s.size(); i++) {
        int posMin = encontrarPosMin(s,i,s.size());
        swap(s, i, posMin);
    }
}

bool esOutlier(audio &audioOrdenado, int n, int percentil) {
    return abs(n) > abs(audioOrdenado[percentil]);
}


int posNoOutlierIzq (audio &audioOrdenado, audio &a, int i, int percentil) {
    int resultado = -1;
    while (i > 0) {
        i--;
        if (!esOutlier(audioOrdenado, a[i], percentil)) {
            resultado = i;
            break;
        }
    }
    return resultado;
}

int posNoOutlierDer (audio &audioOrdenado, audio &a, int i, int percentil) {
    int resultado = -1;
    while (i < a.size()-1) {
        i++;
        if (!esOutlier(audioOrdenado, a[i], percentil)) {
            resultado = i;
            break;
        }
    }
    return resultado;
}

int reemplazoNoOutlier(audio a, int i, audio audioOrdenado, int percentil) {
    if (posNoOutlierIzq(audioOrdenado,a,i,percentil) < 0) {
        return a[posNoOutlierDer(audioOrdenado,a,i,percentil)];
    } else if (posNoOutlierDer(audioOrdenado,a,i,percentil) < 0) {
        return a[posNoOutlierIzq(audioOrdenado,a,i,percentil)];
    } else {
        return (floor((a[posNoOutlierIzq(audioOrdenado,a,i,percentil)] + a[posNoOutlierDer(audioOrdenado,a,i,percentil)]) / 2));
    }
}


void limpiarAudio(audio &a, int profundidad, vector<int> &atipicos) {
    int percentil = (int) floor(0.95 * a.size());
    audio audioOrdenado = a;
    audio audioLimpio = a;
    selectionSort(audioOrdenado);
    for (int i=0; i<a.size(); i++) {
        if (esOutlier(audioOrdenado, a[i], percentil)) {
            atipicos.push_back(i);
        }
    }
    for (int i=0; i<atipicos.size(); i++) {
        audioLimpio[atipicos[i]] = reemplazoNoOutlier(a,atipicos[i],audioOrdenado,percentil);
    }
    a = audioLimpio;
}
