#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <tuple>
#include <iomanip>
#include <map>
#include <cmath>
#include <math.h>

using namespace std;
vector<vector<int>> adyacencias;
vector<vector<int>> adyacenciasT;
vector<vector<int>> compFC;
vector<bool> visitados;
stack<int> S, ST;
long n, m;

void DFS(int nodo){
    visitados[nodo] = true;

    for(int i = 0; i < adyacencias[nodo].size(); i++){
        if (visitados[adyacencias[nodo][i]]) continue;
        DFS(adyacencias[nodo][i]);
    }

    S.push(nodo);
}

void DFST(int nodo){
    visitados[nodo] = true;

    for(int i = 0; i < adyacenciasT[nodo].size(); i++){
        if (visitados[adyacenciasT[nodo][i]]) continue;
        DFST(adyacenciasT[nodo][i]);
    }

    ST.push(nodo);
}

int main(){
    cin >> n >> m;

    adyacencias = vector<vector<int>>(n+1);
    adyacenciasT = vector<vector<int>>(n+1);
    visitados = vector<bool>(n+1,false);

    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adyacencias[u].push_back(v);
        adyacenciasT[v].push_back(u);
    }

    for(int i = 1; i <= n; i++){
        if(!visitados[i]) DFS(i);
    }

    visitados = vector<bool>(n+1,false);

    while(!S.empty()){
        int nodo = S.top();
        S.pop();

        if (!visitados[nodo]){

            DFST(nodo);

            vector<int> aux;

            while(!ST.empty()){
                int next = ST.top();
                ST.pop();
                aux.push_back(next);
            }
            compFC.push_back(aux);
            aux.clear();
        }
    }
    
    return 0;
}