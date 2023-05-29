#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <tuple>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cmath>
#include <math.h>

using namespace std;
vector<vector<int>> adyacencias;
vector<vector<int>> adyacenciasT;
vector<vector<int>> compFC;
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

bool componentCaeSola(vector<int>* comp){
    for (int i = 0; i < (*comp).size(); i++){
        int nodo = (*comp)[i];
        for (int j = 0; j < adyacenciasT[nodo].size(); j++){
            if (!pertence(*comp,adyacenciasT[nodo][j])) return false;
        }
    }
    return true;
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

            vector<int> componente;

            while(!ST.empty()){
                int next = ST.top();
                ST.pop();
                componente.push_back(next);
            }

            sort(componente.begin(),componente.end());

            compFC.push_back(componente);
            componente.clear();
        }
    }
    

    vector<int> representantes;
    for(int i = 0; i < compFC.size(); i++){
        vector<int>* comp = &compFC[i];
        if (componentCaeSola(comp)) representantes.push_back((*comp)[0]);
    }
    sort(representantes.begin(),representantes.end());

    cout << representantes.size() << endl;
    
    for (int i = 0; i < representantes.size(); i++){
        cout << representantes[i] << " ";
    }

    return 0;
}