#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
using namespace std;
vector<int> componentes_Conexas;
vector<vector<int>> aristas;
vector<vector<int>> adyacencias;
vector<tuple<vector<int>,bool>> treeEdges;
int NO_LO_VI = 0, EMPECE_A_VER = 1,TERMINE_DE_VER = 2, n, m;
vector<int> estado;
vector<int> esta2;
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
            if(estado[u]==TERMINE_DE_VER)continue;
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
    }
    estado[v]= TERMINE_DE_VER;
}

int DFS2(int v, int tam_cc){
    int temp_tam=tam_cc;
    esta2[v]= EMPECE_A_VER;
    for(int u: adyacencias[v]){
        if (esta2[u] == NO_LO_VI){
            temp_tam++;
            temp_tam=DFS2(u,temp_tam);
        }
    }
    esta2[v]= TERMINE_DE_VER;
    return temp_tam;
}

void hacerPiquete(){ //corta los puentes como Moyano :B
    for(tuple<vector<int>,bool> tup : treeEdges){
        if(get<1>(tup)){

            int u = get<0>(tup)[0];
            int v = get<0>(tup)[1];

            for (auto i = adyacencias[u].begin(); i != adyacencias[u].end(); i++){
                if (*i == v){
                    adyacencias[u].erase(i);
                }
            }
            for (auto i = adyacencias[v].begin(); i != adyacencias[v].end(); i++){
                if (*i == u){
                    adyacencias[v].erase(i);
                }
            }
        }
    }
}
void armarComponentes(){
    for(int i = 1; i <= n; i ++){
        if (estado[i] == NO_LO_VI){
            DFS (i);
        }
    }
    hacerPiquete();
    for(int i = 1; i <= n; i ++){
        if(esta2[i] == NO_LO_VI){
           int tamCC = DFS2(i,1);
           componentes_Conexas.push_back(tamCC);
        }
    }
}

double fact(int i){
    if(i == 2) return 2.0;
    return fact(i-1)*i;
}

double comb(int i){
    if (i == 1) return 0;
    int factMenosDos = fact(i-2);
    int res = (i*(i-1)*factMenosDos/(2*factMenosDos));
    return res;
}



int main(){
    cin >> n >> m;

    double eleccionesTotales = (n*(n-1)/2);

    estado = vector<int>(n+1,NO_LO_VI);
    esta2 = vector<int>(n+1,NO_LO_VI);
    padres = vector<int>(n+1,-1);
    adyacencias = vector<vector<int>>(n+1);

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
    armarComponentes();
    double ganar = 0;
    for (int i = 0; i < componentes_Conexas.size(); i++){
        ganar += comb(componentes_Conexas[i]);
    }

    double probPerder = 1- (ganar/eleccionesTotales);
    cout << setprecision(6)<< probPerder << endl;
    return 0;
}
