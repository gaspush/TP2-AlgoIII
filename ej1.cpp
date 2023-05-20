#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <map>
using namespace std;

vector<int> componentes_Conexas;
vector<vector<int>> adyacencias;
map<vector<int>,bool> puentes;// mapa de aristas a bool. 
int NO_LO_VI = 0, EMPECE_A_VER = 1,TERMINE_DE_VER = 2, n, m;
vector<int> estado;
vector<int> esta2;
vector<int> padres;

void DFS(int v){
    estado[v]= EMPECE_A_VER;
    for(int u: adyacencias[v]){
        if (estado[u] == NO_LO_VI){
            padres[u] = v;

            vector<int> temp1 = {u,v};
            vector<int> temp2 = {v,u};

            puentes[temp1] = puentes[temp2] = true;

            DFS(u);
        }
        else{
            if(estado[u]==TERMINE_DE_VER)continue;
            if (u != padres[v]){    //Encontre Backedge.
                int padre = padres[v];
                int hijo = v;

                while(hijo != u){// Asciendo por el arbol marcando las aristas como cubiertas
                    puentes[{padre,hijo}] = puentes[{hijo,padre}] = false;
                    hijo = padre;
                    padre = padres[hijo];
                }
            }
        }
    }
    estado[v]= TERMINE_DE_VER;
}

int DFS2(int v, int tam_cc){
    int temp_tam=tam_cc;
    esta2[v]= EMPECE_A_VER;
    for(int u: adyacencias[v]){
        if (esta2[u] == NO_LO_VI && !puentes[{u,v}]){
            temp_tam++;
            temp_tam=DFS2(u,temp_tam);
        }
    }
    esta2[v]= TERMINE_DE_VER;
    return temp_tam;
}

void armarComponentes(){
    for(int i = 1; i <= n; i ++){
        if (estado[i] == NO_LO_VI){
            DFS (i);
        }
    }
    for(int i = 1; i <= n; i ++){
        if(esta2[i] == NO_LO_VI){
           int tamCC = DFS2(i,1);
           componentes_Conexas.push_back(tamCC);
        }
    }
}

double fact(int n){
    double res = 1;
    for (int i = 2; i <= n; i++){
        res *=i;
    }
    return res;
}

double combinatorio(int n){
    if (n == 1) return 0;
    return (fact(n) / (fact(n-2)*2));
}

int main(){
    cin >> n >> m;

    double eleccionesTotales = (n*(n-1)/2);

    estado = vector<int>(n+1,NO_LO_VI);
    esta2 = vector<int>(n+1,NO_LO_VI);
    padres = vector<int>(n+1,-1);
    adyacencias = vector<vector<int>>(n+1);

    while (m--){
        int u, v;
        cin >> u >> v;

        adyacencias[u].push_back(v);
        adyacencias[v].push_back(u);
    }

    armarComponentes();

    double ganar = 0;
    for (int i = 0; i < componentes_Conexas.size(); i++){
        ganar += combinatorio(componentes_Conexas[i]);
    }

    double probPerder = 1 - (ganar/eleccionesTotales);
    cout << fixed << setprecision(6) << probPerder << endl;
    return 0;
}
