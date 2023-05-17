#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> treeEdges;
vector<vector<int>> aristas;
vector<vector<int>> adyacencias;
int NO_LO_VI = 0, EMPECE_A_VER = 1,TERMINE_DE_VER = 2, n, m;
vector<int> memo;
vector<int> estado;

int cubren(int v, int p = -1) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    res += backConExtremoInferiorEn[v];
    res -= backConExtremoSuperiorEn[v];
    for (int hijo : treeEdges[v]) if (hijo != p) {
        res += cubren(hijo, v);
    }
    memo[v] = res;
    return res;
}
void dfs (vector<vector<int>> G, int nodo, int p ){
    vector <int> comienzo(n,-1);
    vector <int> fin(n,-1);
    vector <int> padre(n,-1);
    int i=0;
    for (int u=0; u<G[nodo].size();u++){
        if (padre[u]==-1){
            treeEdges[v].push_back(u);
            DFS-visit(G,nodo);
        }else if (u != p){
            backConExtremoInferiorEn[v]++;
            backConExtremoSuperiorEn[u]++;
        }
    }
}


vector<vector<int>> treeEdges; //init en []


void dfs(int v, int p){
    estado[v]= EMPECE_A_VER;
    for(int u: adyacencias[v]){
        if (estado[u] == NO_LO_VI){
            treeEdges[v].push_back(u);
            dfs(u, v);
        }
    estado[v]= TERMINE_DE_VER;
    }
}
 
/*
void DFS-visit (int u, int p){
    i+=1;
    comienzo[u]=k;
    for( int v : G[u]){
        if (padre[u]==-1){
            padre[v]=u;
            DFS-visit(v,V);
        }
    }
    k+=1;
    fin[u]=k;
}*/

void main(){
    cin >> n >> m;

    estado = vector<int>(n,NO_LO_VI);

    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        vector<int> tmp;
        tmp.push_back(u);
        tmp.push_back(v);
        aristas.push_back(tmp);

        adyacencias[u].push_back(v);
        adyacencias[v].push_back(u);
    }

}