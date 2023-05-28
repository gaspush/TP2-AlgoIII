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
vector<pair<int,vector<int>>> compFC;
vector<bool> visitados;
stack<int> S, ST;
long n, m;

bool pertence(vector<int>& vec, int x){
    bool res = false;
    for(int i = 0; i < vec.size(); i++){
        if (vec[i] == x) return true;
    }
    return false;
}

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
            vector<int> vecinos;

            while(!ST.empty()){
                int next = ST.top();
                ST.pop();
                aux.push_back(next);
            }

            int menor = aux[0];
            for (int i = 0; i < aux.size(); i++){
                int nodotemp = aux[i];
                if (nodotemp < menor) menor = nodotemp;
                for (int j = 0; j < adyacencias[nodotemp].size(); j++){                    
                    int potencial = adyacencias[nodotemp][j];
                    if (pertence(vecinos,potencial) || pertence(aux,potencial)) break;
                    vecinos.push_back(potencial);
                }                
            }

            pair<int,vector<int>> par = make_pair(menor,vecinos);
            compFC.push_back(par);
            aux.clear();
            vecinos.clear();
        }
    }

    

    return 0;
}