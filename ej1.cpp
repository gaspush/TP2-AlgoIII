#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

vector<vector<int>> aristas;
vector<vector<int>> adyacencias;
vector<tuple<vector<int>,bool>> treeEdges;
int NO_LO_VI = 0, EMPECE_A_VER = 1,TERMINE_DE_VER = 2, n, m;
vector<int> estado;
vector<int> padres;


void DFS(int v){
    estado[v]= EMPECE_A_VER;
    for(int u: adyacencias[v]){
        if (estado[u] == NO_LO_VI){
            padres[u] = v;
            vector<int> tmp;
            tmp.push_back(v);
            tmp.push_back(u);
            tuple<vector<int>,bool> tup = make_tuple(tmp,true);
            treeEdges.push_back(tup);
            DFS(u);
        }
        else{
            if (u != padres[v]){    //Encontre Backedge.
                int padre = padres[v];
                int hijo = v;
                while(hijo != u){
                    for (tuple<vector<int>,bool> tup : treeEdges){
                        if (get<0>(tup)[0] == padre && get<0>(tup)[1] == hijo){
                            get<1>(tup) = false;
                        }
                    }
                    hijo = padre;
                    padre = padres[hijo];
                }
            }

        }
    estado[v]= TERMINE_DE_VER;
    }
    for ( tuple<vector<int>,bool> tup : treeEdges){
        if(get<1> (tup)){
            int tempA = BFS(get<0>(tup)[0],get<0>(tup)[1]);
            int tempB = BFS(get<0>(tup)[1],get<0>(tup)[0]);
        }
    }
    
}


void main(){
    cin >> n >> m;

    estado = vector<int>(n,NO_LO_VI);
    padres = vector<int>(n,-1);

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

    DFS(1);
}