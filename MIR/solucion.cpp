#include "solucion.h"
#include "auxiliares.h"
#include <algorithm>
#include <vector>
#include <tuple>
#include <math.h>

bool enRangoProfundidad(audio vector, int profundidad);

double limiteProfundidad(int p);

bool cumplePreReplicar(audio vector, int canal, int profundidad);

void replicarEnCanal(const audio &a, int canal, audio &replica, int i);

bool cumplePreRevertir(audio a, int canal, int profundidad);

void revertirBloque(const audio &a, int canal, audio &revertido, int i);

bool cumplePreMagnitudAbsMax(audio vector, int canal, int profundidad);

void maximosPorCanal(const audio &a, int canal, int i, vector<int> &maximos, vector<int> &posicionesMaximos);

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

// EJ 5
vector<int> redirigir(vector<int> a, int c, int p) {
    int inicio;
    int direccion;
    vector<int> result = a;
    if (c==1) {
        inicio = 1; // me ubico en el canal 2
        direccion = -1;
    } else if (c==2) {
        inicio = 0; // me ubico en el canal 1
        direccion = 1;
    }
    for (int i=inicio; i<a.size(); i=i+2) {
        result[i] = clip(a[i]-a[i+direccion],p);
    }
    return result;
}

int clip(int n, int p) {
    int cota_min = pow(-2, p-1);
    int cota_max = pow(2, p-1)-1;
    if (n>cota_max) {
        return cota_max;
    } else if (n<cota_min) {
        return cota_min;
    } else {
        return n;
    }
}

// EJ 6
void bajarCalidad(vector<vector<int>> &as, int p, int p2) {
    for (int i=0; i<as.size(); i++) {
        bajaCalidadAudio(as[i],p,p2);
    }
}

void bajaCalidadAudio(vector<int> &a, int p, int p2) {
    for (int i=0; i<a.size(); i++) {
        a[i] = floor(a[i]/pow(2,p-p2));
    }
}

// EJ 7
bool esSoft(vector<int> a, int largo, int umbral) {
    int superiores = 0;
    for (int i=0; i<a.size() && superiores != largo; i++) {
        if (a[i]>umbral) {
            superiores += 1;
        } else {
            superiores = 0;
        }
    }
    if (superiores == largo) {
        return false;
    } else {
        return true;
    }
}

tuple<vector<vector<int>>, vector<vector<int>>> audiosSoftYHard(vector<vector<int>> sa, int p, int largo, int umbral) {
    vector<vector<int>> soft = {};
    vector<vector<int>> hard = {};
    for(int audio=0; audio<sa.size(); audio++) {
        if (esSoft(sa[audio],largo,umbral)) {
            soft.push_back(sa[audio]);
        } else {
            hard.push_back(sa[audio]);
        }
    }
    auto seqSoftHard = make_tuple(soft,hard);
    return seqSoftHard;
}

// EJ 8
void reemplazarSubAudio(vector<int> &a, vector<int> a1, vector<int> a2, int p) {
    vector<int> reemplazo;
    int reinicio;
    for (int i=0; i<a.size(); i++) {
        if (!enSubAudio(a,i,a1)) {
            reemplazo.push_back(a[i]);
        } else {
            reinicio = i+a1.size();
            break;
        }
    }
    reemplazo = concat(reemplazo,a2);
    for (int i=reinicio; i<a.size(); i++) {
        reemplazo.push_back(a[i]);
    }
    a = reemplazo;
}

bool enSubAudio(vector<int> audio, int i, vector<int> subaudio) {
    bool esSubAudio = false;
    for (int j=0; j<subaudio.size(); j++) {
        if (subaudio[j] == audio[i+j]) {
            esSubAudio = true;
        } else {
            esSubAudio = false;
            break;
        }
    }
    return esSubAudio;
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

tuple<vector<int>, vector<tuple<int,int>>> maximosTemporales(vector<int> a, int p, vector<int> tiempos) {
    vector<tuple<int,int>> intervalos = {};
    vector<int> maximos = {};
    int cota_min = pow(-2, p-1);
    for (int t=0; t<tiempos.size(); t++) {
        agregarIntervalos(intervalos, a.size(), tiempos[t]);
    }
    for (int i=0; i<intervalos.size(); i++) {
        agregarMaximo(maximos, a, intervalos[i], cota_min);
    }
    auto resultado = make_tuple(maximos,intervalos);
    return resultado;
}

// EJ 10
vector<int> limpiarAudio(vector<int> &a) {
    vector<int> atipicos = {};
    for (int i=0; i<a.size(); i++) {
        if (esOutlier(a, a[i])) {
            atipicos.push_back(i);
        }
    }
    for (int i=0; i<atipicos.size(); i++) {
        a[atipicos[i]] = reemplazoNoOutlier(a,atipicos[i],atipicos);
    }
    return atipicos;
}

bool esOutlier(vector<int> a, int n) {
    bool resultado = false;
    int menores = 0;
    for (int i=0; i<a.size(); i++) {
        if (abs(n)>abs(a[i])) {
            menores++;
        }
    }
    if (menores >= floor(0.95*a.size())) {
        resultado = true;
    }
    return resultado;
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

