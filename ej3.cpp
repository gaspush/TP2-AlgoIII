#include <iostream>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <iomanip>
#include <map>
#include <cmath>
#include <math.h>
#include <algorithm>

using namespace std;

typedef pair<int,int> nodo;
typedef long long ll;
typedef pair<double, pair<nodo, nodo>> arista;

int r, n, c, UTP,fibra_Optica, modems;
vector<pair<long double,long double>> gastosC;
long double gastoUTP, gastoFibra;
vector <nodo> nodos;
vector<arista> aristas; // cada arista es un par <pesoArista,(u,v)>
map<nodo,nodo> padre;
map<nodo,int> rango;
int limitN=1000;
int limitR=10000;

double distancia ( nodo u, nodo v){
    if (u.first==v.first || u.second == v.second) return abs(u.first - v.first + u.second - v.second); //Si estan alineados, nos ahorramos unas cuentas
    return (sqrt(pow(u.second - v.second,2) + pow(u.first - v.first ,2))); //dif triangular, distancia de 2 ptos en un plano
}

void armarAristas(vector<pair<int,int>> nodos){ // esto ya cuesta O(n^2) por lo tanto la implementación de Kruskal que sirve es la que cuesta O(n^2)
    int tope= (nodos.size()-1)/2;
    for (int i=0; i< nodos.size();i++){
        nodo u=nodos[i];
        for (int j=0; j<i;j++){  //No sube complejidad son n aristas para n nodos => n^2
             nodo v = nodos[j];
            double d=distancia(u,v);
            
            arista temp = {d,{u,v}};
            aristas.push_back(temp);          
        }
    }
}

void makeSet(nodo u){
    padre[u]=u;
    rango[u]=0;    
}

nodo findSet(nodo x) {
  if (x != padre[x]) padre[x] = findSet(padre[x]);
  return padre[x];
}

void unionSet(nodo u, nodo v){
    if (rango[u] > rango[v]) padre[v] = u;
    else padre[u] = v;
    if (rango[u] == rango[v]) ++rango[v];
}

bool peso (arista x, arista y){
    return x.first <= y.first;
}

double Kruskal (int n, vector<arista> a){
    for(int i = 0; i < n; ++i) makeSet(nodos[i]); // creo los el bosque, c/u es su representante
    sort(a.begin(),a.end(),peso);
    
    int maxIt = n-modems;  
    for (auto arista : a){
        nodo u = findSet(arista.second.first);
        nodo v = findSet(arista.second.second);
        if (u==v) continue;
        if (arista.first<=r){
            gastoUTP+=arista.first*UTP;  
        } else {
            gastoFibra+=arista.first*fibra_Optica;
        }
        unionSet(u,v);
        maxIt--;
        if (maxIt==0) break; // como genero un árbol al poner la arista numero n-1 por invariante de Kruskal ya está.
    }    
    return 0;
}



int main(){ 
    cin >> c;
    for (int it=0; it< c;it++){
        cin >> n >> r >> modems >> UTP >> fibra_Optica;
        gastoUTP=0;
        gastoFibra=0;
        nodos.clear();
        aristas.clear();
        padre.clear();
        rango.clear();
        for(int i=0; i<n ;i++){
            int x;
            int y;
            
            cin>> x >> y;
            nodos.push_back({x,y});
        }
        armarAristas(nodos);
        Kruskal(n,aristas);
        pair<long double, long double> temp = make_pair(gastoUTP,gastoFibra);
        gastosC.push_back(temp);
       
    }
    for (int i=0;i<c;i++){
        cout << "Caso #" << i << ":" << fixed << setprecision(3) << gastosC[i].first << " " << gastosC[i].second << endl;
    }
    return 0;
}

/* cosas a tener en cuenta para implementación de Kruskal e informe:
Use of Kruskal’s algorithm’s invariant: After the Kth iteration, we have a minimum spanning 
forest of n-k connected components. This is, among all the spanning forests of n-k connected components, the one that Kruskal forms has the least weight. 
This is important, for example, if we wish to find a minimum spanning forest using only k edges.*/
// https://fedelebron.com/a-dense-version-of-kruskals-algorithm