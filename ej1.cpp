#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <map>
using namespace std;

int NO_LO_VI = 0, EMPECE_A_VER = 1,TERMINE_DE_VER = 2, n, m;
vector<int> componentesConexas;// Aqui alamcenaremos los tamanios de las distintas CC una vez "eliminados" los puentes
vector<vector<int>> adyacencias;
map<vector<int>,bool> puentes;// Mapa de aristas a bool. Si value de una arista es true, esta es puente en mi arbol DFS
vector<int> estado;
vector<int> esta2;
vector<int> padres;

void DFSPuentes(int v){
    estado[v]= EMPECE_A_VER;
    for(int u: adyacencias[v]){  // O(m)
        if (estado[u] == NO_LO_VI){ // O(1)
            padres[u] = v; // O(1)

            vector<int> temp1 = {u,v}; // O(1)
            vector<int> temp2 = {v,u}; // O(1)

            puentes[temp1] = puentes[temp2] = true; // Cuando una arista pasa a formar parte del arbol, la asumimos como puente hasta que se demuestre lo contrario.

            DFSPuentes(u); // O(T) a calcular en c/caso, si todas las adyacencias son "no lo vi" [es decir una recta de nodos, por ejemplo] hago para cada adyacencia O(1) operaciones para marcar que son puentes todos. Todo es O(m)
        }
        else{
            if(estado[u]==TERMINE_DE_VER)continue;// Si el nodo ya termino de ser visto, se habia llegado a el desde un nodo hijo y la backedge correspondiente ya fue tenida en cuenta
            if (u != padres[v]){    //Encontre Backedge.
                int padre = padres[v]; // O(1)
                int hijo = v; // O(1)

                while(hijo != u){// Asciendo por el arbol marcando las aristas como cubiertas, es decir, no puentes.  O(n) en peor caso subimos desde la hoja a la raíz pasando por todos los nodos intermedios
                    puentes[{padre,hijo}] = puentes[{hijo,padre}] = false; // O(1)
                    hijo = padre; // O(1)
                    padre = padres[hijo]; // O(1)
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
        if (esta2[u] == NO_LO_VI && !puentes[{u,v}]){//Ignora los nodos conectados por aristas puente
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
            DFSPuentes (i);
        }
    }
    for(int i = 1; i <= n; i ++){
        if(esta2[i] == NO_LO_VI){
           int tamCC = DFS2(i,1);
           componentesConexas.push_back(tamCC);
        }
    }
}
/*
double fact(int n){
    double res = 1;
    for (int i = 2; i <= n; i++){
        res *=i;
    }
    return res;
}
*/
double combinatorio(int n){//Solo nos importa el combinatorio (n 2)
    return ((n-1)*n / (2));
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
    for (int i = 0; i < componentesConexas.size(); i++){
        ganar += combinatorio(componentesConexas[i]);
    }

    double probPerder = 1 - (ganar/eleccionesTotales);
    cout << fixed << setprecision(6) << probPerder << endl;
    return 0;
}
