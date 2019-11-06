#include <algorithm>
#include <gtest/gtest.h>
#include "auxiliares.h"
#include <iostream>
#include <fstream>
#include <numeric>
#include "solucion.h"

using namespace std;

void escribirAudio(audio a, string nombreArchivo, int c) {
    ofstream fout;
    fout.open(nombreArchivo);
    fout << c << " ";
    for (int i=0; i < a.size(); i=i+1) {
        fout << a[i];
        if (i == a.size()-1) {
            break;
        }
        fout << " ";
    }
    fout.close();
}

tuple<int, audio> leerAudio(string nombreArchivo) {
    int canal;
    int valor;
    audio a = {};
    ifstream fin;
    fin.open(nombreArchivo, ifstream::in);
    fin >> canal;
    while(!fin.eof()) {
        fin >> valor;
        a.push_back(valor);
    }
    fin.close();
    auto res = make_tuple(canal,a);
    return res;
}

int indicePrimeraAparicion(vector<int>& v, int elem){
    int res = -1;
    for(int i = 0; i < v.size(); i++){
        if(v[i] == elem){
            res = i;
            return res;
        }
    }
}

double calcularRevertir(vector<int> a){
    double t0 = clock();
    revertirAudio(a,1,1);
    double t1 = clock();
    return (double(t1-t0));
}

double calcularLimpiar(vector<int> &a, vector<int> &atipicos){
    double t0 = clock();
    limpiarAudio(a,1,atipicos);
    double t1 = clock();
    return (double(t1-t0));
}

void calcularTiempoEjecucionRevertir(){
    int n = 0; int hasta = 10000000; int paso = 1000000;
    ofstream fout;
    fout.open("datosRevertir.csv");
    fout << "n\t" << "tiempo" <<endl;
    while(n < hasta){
        vector<int> audio (n);
        std::iota(audio.begin(), audio.end(), 0);

        int tiempo = calcularRevertir(audio);
        fout << n << "\t" << tiempo << endl;

        n +=paso;

    }
    fout.close();
}

void calcularTiempoEjecucionLimpiar(){
    int n = 0; int hasta = 10000; int paso = 500;
    ofstream fout;
    fout.open("datosLimpiar.csv");
    fout << "n\t" << "tiempo" <<endl;
    while(n < hasta){
        vector<int> audio (n);
        vector<int> atipicos;
        std::iota(audio.begin(), audio.end(), 0);

        int tiempo = calcularLimpiar(audio, atipicos);
        fout << n << "\t" << tiempo << endl;

        n +=paso;

    }
    fout.close();
}

bool vectoresOrdenadosIguales(vector<int> vector1, vector<int> vector2){
    if(vector1.size() != vector2.size())
        return false;

    for (int i = 0; i < vector1.size(); ++i)
        if (vector1[i] != vector2[i]){return false;}

    return true;
}

bool todasSusFilasEnLaOtraMatriz(vector<vector<int> > mat1, vector<vector<int> > mat2) {
    bool res;
    
    for (int i = 0; i < mat1.size(); ++i){
        res = false;
        for (int j = 0; j < mat2.size(); ++j) {
            if (vectoresOrdenadosIguales(mat1[i], mat2[j])) {
                res = true;
                break;
            }
        }
        if(!res)
            return false;
    }

    return true;
}

bool matricesIguales(vector<vector<int> > mat1, vector<vector<int> > mat2){
    if(mat1.size() != mat2.size())
        return false;

    for (int i = 0; i < mat1.size(); ++i) {
        sort(mat1[i].begin(), mat1[i].end());
        sort(mat2[i].begin(), mat2[i].end());
    }

    return todasSusFilasEnLaOtraMatriz(mat1,mat2) && todasSusFilasEnLaOtraMatriz(mat2,mat1);
}

bool tuplasIguales(vector<tuple<int,int>> vector1, vector<tuple<int,int>> vector2){
    if(vector1.size() != vector2.size())
        return false;

    for (int i = 0; i < vector1.size(); ++i)
        if (vector1[i] != vector2[i]){return false;}

    return true;
}

void ASSERT_VECTOR(vector<int> vector1, vector<int> vector2) {
    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    ASSERT_TRUE(vectoresOrdenadosIguales(vector1, vector2));
}

void ASSERT_MATRIX(vector<audio> mat1, vector<audio> mat2) {
    ASSERT_TRUE(matricesIguales(mat1, mat2));
}

void ASSERT_VECTOR_TUPLES(vector<tuple<int,int>> vector1, vector<tuple<int,int>> vector2){
    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    ASSERT_TRUE(tuplasIguales(vector1, vector2));
}
