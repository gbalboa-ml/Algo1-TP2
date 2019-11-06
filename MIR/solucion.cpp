#include "solucion.h"
#include "auxiliares.h"
#include <algorithm>
#include <vector>
#include <tuple>
#include <math.h>

bool enRangoProfundidad(audio vector, int profundidad);

int limiteProfundidad(int p);

void replicarEnCanal(const audio &a, int canal, audio &replica, int i);

void revertirBloque(const audio &a, int canal, audio &revertido, int i);

void maximosPorCanal(const audio &a, int canal, int i, vector<int> &maximos, vector<int> &posicionesMaximos);

double disminuirEn(int p, int p2);

vector<int> copyArray(vector<int> &vector);

int abs(int n) {
    if (n<0) {
        return -n;
    } else {
        return n;
    }
}

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

int limiteProfundidad(int p) { return (int)pow ((double)2, (double)(p - 1)); }

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
vector<int> redirigir(vector<int> a, int c, int p) {
    int inicio = 1; // me ubico en el canal 1 por defecto
    int direccion = -1;
    vector<int> result = a;
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

void bajaCalidadAudio(vector<int> &a, int p, int p2) {
    for (int &i : a) {
        i = floor(i / disminuirEn(p, p2));
    }
}

double disminuirEn(int p, int p2) { return pow((double)2, (double)p - p2); }

// EJ 7
bool esSoft(vector<int> a, int largo, int umbral) {
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

void audiosSoftYHard(vector<vector<int>> sa, int p, int largo, int umbral, vector<vector<int>> &soft, vector<vector<int>> &hard) {
    for(int audio=0; audio<sa.size(); audio++) {
        if (esSoft(sa[audio],largo,umbral)) {
            soft.push_back(sa[audio]);
        } else {
            hard.push_back(sa[audio]);
        }
    }
}

// EJ 8
void reemplazarSubAudio(vector<int> &a, vector<int> a1, vector<int> a2, int p) {
    vector<int> reemplazo = {};
    int reinicio;
    int i;
    for (i=0; i<a.size(); i++) {
        if (!enSubAudio(a,i,a1)) {
            reemplazo.push_back(a[i]);
        } else {
            reinicio = i+a1.size();
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

bool enSubAudio(vector<int> audio, int i, vector<int> subaudio) {
    int j=0;
    while (j<subaudio.size() && subaudio[j] == audio[i+j]) {
        j++;
    }
    return !(j<subaudio.size());
}

vector<int> concat (vector<int> v1, vector<int> v2) {
    vector<int> concatenado = v1;
    for (int i=0; i < v2.size(); i++) {
        concatenado.push_back(v2[i]);
    }
    return concatenado;
}

// EJ 9
int encontrarMaximo(vector<int> &a, int desde, int hasta, int cota_min) {
    int max = cota_min;
    for (int i=desde; i<=hasta && i<a.size(); i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

void agregarMaximo(vector<int> &maximos, vector<int> &a, tuple<int,int> intervalo, int cota_min) {  
    int desde = get<0>(intervalo);
    int hasta = get<1>(intervalo);
    int maximo = encontrarMaximo(a,desde,hasta,cota_min);
    maximos.push_back(maximo);
}

void agregarIntervalos(vector<tuple<int,int>> &intervalos, int size, int t) {
    for (int i=0; i<size; i=i+t) {
        auto intervalo = make_tuple(i,i+t-1);
        intervalos.push_back(intervalo);
    }
}

void maximosTemporales(vector<int> a, int p, vector<int> tiempos, vector<tuple<int,int>> &intervalos, vector<int> &maximos) {

    int cota_min = - pow(2, p-1);
    for (int t=0; t<tiempos.size(); t++) {
        agregarIntervalos(intervalos, a.size(), tiempos[t]);
    }
    for (int i=0; i<intervalos.size(); i++) {
        agregarMaximo(maximos, a, intervalos[i], cota_min);
    }
}

// EJ 10
void limpiarAudio(vector<int> &a, int profundidad, vector<int> &atipicos) {
    int percentil = (int) floor(0.95 * a.size());
    vector<int> audioOrdenado = copyArray(a);
    sort(audioOrdenado.begin(), audioOrdenado.end());
    for (int i=0; i<a.size(); i++) {
        if (esOutlier(audioOrdenado, a[i], percentil)) {
            atipicos.push_back(i);
        }
    }
    for (int i=0; i<atipicos.size(); i++) {
        a[atipicos[i]] = reemplazoNoOutlier(a,atipicos[i],atipicos);
    }
}

vector<int> copyArray(vector<int> &a) {
    vector<int> copia;
    copia.reserve(a.size());
    for (int i : a) {
        copia.push_back(i);
    }
    return copia;
}

bool esOutlier(vector<int> a, int n, int percentil) {
    if (a.size() == 1) return false;
    sort(a.begin(), a.end());
    return abs(n) > abs(a[percentil]);
}

bool esPosAtipica(vector<int> atipicos, int i) {
    bool posAtipica = false;
    for (int j=0; j<atipicos.size(); j++) {
        if (atipicos[j] == i) {
            posAtipica = true;
            break;
        }
    }
    return posAtipica;
}

int posNoOutlierIzq (vector<int> a, int i, vector<int> atipicos) {
    int resultado = -1; 
    while (i > 0) {
        i--;
        if (!esPosAtipica(atipicos, i)) {
            resultado = i;
            break;
        }
    }
    return resultado;
}

int posNoOutlierDer (vector<int> a, int i, vector<int> atipicos) {
    int resultado = -1; 
    while (i < a.size()-1) {
        i++;
        if (!esPosAtipica(atipicos, i)) {
            resultado = i;
            break;
        }
    }
    return resultado;
}

int reemplazoNoOutlier(vector<int> a, int i, vector<int> atipicos) {
    if (posNoOutlierIzq(a,i,atipicos) < 0) {
        return a[posNoOutlierDer(a,i,atipicos)];
    } else if (posNoOutlierDer(a,i,atipicos) < 0) {
        return a[posNoOutlierIzq(a,i,atipicos)];
    } else {
        return (floor((a[posNoOutlierIzq(a,i,atipicos)] + a[posNoOutlierDer(a,i,atipicos)]) / 2));
    }
}

