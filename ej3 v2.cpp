//#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>
#include <math.h>
#include <algorithm>

using namespace std;


int n,r, UTP,fibra_Optica, modems, cantCasos, caso;
double gastoUTP, gastoFibra;

vector <tuple<double,int,int,int>>  E;
vector<vector<int>> nodos;


double distancia(double x0, double x1, double y0, double y1) {
    double deltaX = x0 - y0;
    double deltaY = x1 - y1;

    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

void armarAristas(){
    //vector<tuple<double,int,int, int>> E;
    double cost; // precio del cable
    int tipoDeCable; // 0 si es UTP, 1 si es Fibra Optica
    for (int i = 0; i < nodos.size(); i++){
        for (int j = i+1; j < nodos.size(); j++){
            if (i!=j){
                int x1=nodos[i][0];
                int y1=nodos[i][1];

                int x2=nodos[j][0];
                int y2=nodos[j][1];
                double d = distancia(x1,y1,x2,y2);
                if (d<=r){
                    cost = UTP*d;
                    tipoDeCable = 0;
                }else{
                    cost = fibra_Optica*d;
                    tipoDeCable = 1;
                }
                E.emplace_back(cost,i,j, tipoDeCable);
            }
        }

    }
}
struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }
    int find2(int v) { // No optima, busca recorriendo hasta la raíz
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}
    int find(int v){// Óptima, busca y va redefiniendo el padre como la raíz
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};
bool peso (const tuple<double,int,int,int>& x, const tuple<double,int,int,int>& y){
    return get<0>(x) <= get<0>(y);
}

void kruskal(){
    sort(E.begin(),E.end(),peso);
    int aristas = 0;
    int componentes=n;
    DSU dsu(n);
    for(auto actualArista : E){
        double c = get<0>(actualArista);
        int u = get<1>(actualArista);
        int v = get<2>(actualArista);
        int t = get<3>(actualArista);
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            if (t){
                gastoFibra+=c;
            }else{
                gastoUTP+=c;
            }
            aristas++;
            componentes--;
            if (componentes==modems) break;
        }
    }
    if(aristas == n-modems) cout << "Caso #" << caso+1 << ": " << fixed << setprecision(3) << gastoUTP << " " << gastoFibra << endl;
    else cout<<"IMPOSSIBLE\n";
}

int main() {
    cin >> cantCasos;
    for (int it=0; it< cantCasos;it++){
        caso=it;
        cin >> n >> r >> modems >> UTP >> fibra_Optica;
        gastoUTP=0;
        gastoFibra=0;

        for(int i=0; i<n ;i++){
            int x;
            int y;

            cin>> x >> y;
            nodos.push_back({x,y});
        }
        armarAristas();
        kruskal();
        nodos.clear();
        E.clear();

    }
    return 0;
}
