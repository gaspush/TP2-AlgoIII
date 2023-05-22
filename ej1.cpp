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
int tin; // ENTRO AL ÁRBOL EN QUÉ ITERACION 
int low; // PUEDO VISITAR UN NODO ANTERIOR DEL ÁRBOL? SI EL VALOR DE CUANDO ENTRÓ N NO ES EL MISMO QUE EL VALOR QUE PUEDO VISITAR ES PORQUE VISITA UNO ANTERIOR
int compConexa=0;
int it=0;
            
void marcarPuentes(int v, int p){ //re corre el grafo como dfs marcando las aristas puente.
    estado[v] = EMPECE_A_VER;
    it++;
    tin[v] = low[v] = it;  // tin = iteración en la que entra al árbol ése nodo. Low = nodo más cercano a V que se puede alcanzar con ése nodo.
    for(int u: adyacencias[v]){  // O(m)
        if(u == p) continue; //
        if (estado[u] == NO_LO_VI){
            
            marcarPuentes(u, v); //sigo bajando marcando en que iteración entran por primera vez
            low[v] = min(low[u], low[v]);// O(1)
            
            if(low[u] > low[v]){ // El nodo hijo "u" sólo alcanza nodos posteriores, no hay backedge que cubra a V.
                puentes[{u, v}] = puentes[{v, u}] = true;
            }
        }
        else{
            low[v] = min(low[v], tin[u]); // actualizo el nodo más cercano que se puede alcanzar comparando con la backedge
            
        }
    }
}
int DFS2(int v, int tam_cc){
    int temp_tam=tam_cc;
    esta2[v]= EMPECE_A_VER;
    for(int u: adyacencias[v]){
        if(estado[v]==NO_LO_VI && !puentes[{u, v}]){//!puentes[{u,v}]){//Ignora los nodos conectados por aristas puente
            temp_tam++;
            temp_tam=DFS2(u,temp_tam);
        }
    }
    esta2[v]= TERMINE_DE_VER;
    return temp_tam;
}

void armarComponentes(){
    for(int i = 1; i <= n; i ++){
        if(estado[i] == NO_LO_VI){
           int tamCC = DFS(i,1);
           componentesConexas.push_back(tamCC);
        }
    }
}
double combinatorio(int n){//Solo nos importa el combinatorio (n 2)
    return ((n-1)*n / (2));
}
int main(){
    cin >> n >> m;
    adyacencias = vector<vector<int>>(n+1);
    componentesConexas = vector<int>(n+1);
    double eleccionesTotales = (n*(n-1)/2);
    estado = vector<int>(n+1,NO_LO_VI);
    while (m--){
        int u, v;
        cin >> u >> v;

        adyacencias[u].push_back(v);
        adyacencias[v].push_back(u);
    }
    for(int i = 1; i <= n; i ++){
        if (estado[i] == NO_LO_VI){
            marcarPuentes (i,0);
        }
    }
    estado = vector<int>(n+1,NO_LO_VI);
    armarComponentes();

    double ganar = 0;
    for (int i = 0; i < componentesConexas.size(); i++){
        ganar += combinatorio(componentesConexas[i]);
    }

    double probPerder = 1 - (ganar/eleccionesTotales);
    cout << fixed << setprecision(5) << probPerder << endl;
    return 0;
}
