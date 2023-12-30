/********************************************************************
Aplicacion del algoritmo de Dijkstra para hallar la ruta mas rapida 
entre dos nodos de un grafo

By
Angel Antonio Mendez Hernandez
********************************************************************/

#include <iostream>
#include <climits>
#include <vector>
using namespace std;

const int INF=INT_MAX; //para cuando no hay conexion entre nodos

//encontrar nodo de minima distancia 
int MinDistancia(int distancia[], bool procesado[], int n){
    int min=INF, iMinimo;
    for(int i=0; i<n; i++){
        //es importante verificar que el nodo correspondiente
        //no haya sido visitado
        if (!procesado[i] && distancia[i]<=min){
            min=distancia[i];
            iMinimo=i;
        }
    }
    return iMinimo;
}

//funcion para imprimir camino
void camino(int padre[], int destino) {
    if(padre[destino]==-1){
        cout<<destino;
        return;
    }
    camino(padre, padre[destino]);
    cout<< " -> " <<destino;
}

void dijkstra(int n, vector<vector<int> > grafo, int origen, int destino){
    int d[n]; 
    int padre[n];
    bool p[n];
    for(int i=0; i<n; i++){
        d[i]=INF;
        p[i]=false;
        padre[i]=-1;
    }
    //en el origen hay distancia cero
    d[origen]=0;
    int u;
    for(int i=0; i<n-1; i++){
        //u se vuelve el nodo mas cercano no visitado
        u=MinDistancia(d, p, n);
        //u ya es visitado
        p[u]=true;
        for(int j=0; j<n; j++){
            //si el nodo j no ha sido visitado, y hay una union
            //entonces sumamos la distancia recorrida y guardamos el nodo
            //de paso
            if(!p[j] && grafo[u][j] && d[u]!=INF && d[u]+grafo[u][j]<d[j]){
                d[j]=d[u]+grafo[u][j];
                padre[j]=u;
            }
        }
    }
    cout<<"El camino mas corto desde "<<origen<<" a "<<destino<<" es: ";
    camino(padre, destino);
    cout<<endl;
    cout<<"La distancia minima es: "<<d[destino]<<endl;
}

int main() {
    int n; //nodos
    int origen, destino;

    cout << "Ingresa el numero de nodos: ";
    cin >> n;
    vector<vector<int> > grafo(n, vector<int> (n, 0)); //matriz de adyacencia
    cout << "Ingresa la matriz de adyacencia del grafo (usa " << INF << " para representar la ausencia de conexion):"<<endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++){
            cout<<"Entrada ("<<i+1<<","<<j+1<<"): ";
            cin>>grafo[i][j];
        }
    }
    cout<<"Ingresa el nodo origen y el nodo destino: ";
    cin>>origen>>destino;

    if(origen<0 || origen>=n || destino<0 || destino>=n)
        cout << "Nodos de origen o destino inválidos." << endl;
    else
        dijkstra(n, grafo, origen, destino);

    return 0;
}
