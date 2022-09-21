#include <iostream>
#include <vector>
#include <list>
#include <pthread.h>

#define INFINITY 1000

using namespace std;
pthread_mutex_t mutexEdges = PTHREAD_MUTEX_INITIALIZER;

void print(vector<int>& A){
    for( auto && a : A){
        cout<<a<<" ";
    }
    cout<<"\n";
}

//Disjoint sets (union find)
class Floresta{
    public:
        int n_arvores;
        vector<int> pai;
        vector<int> rank;
        vector<list<int>> arvore;

        Floresta(){}
        void create(int n_nodes){
            
            n_arvores = n_nodes;
            pai.resize(n_nodes);
            rank.resize(n_nodes);
            arvore.resize(n_nodes);
            for(int i =0; i < n_nodes; i++){
                pai[i] = i;
                rank[i]= 0;
                arvore[i].push_back(i);
            }
        }

        int Find(int node){
            if (pai[node] == node){
                return pai[node];
            }
            
            int raiz = Find(pai[node]);
            pai[node] = raiz;
            return raiz;
        }

        void Union(int node1, int node2){
            int raiz1 = Find(node1);
            int raiz2 = Find(node2);
            
            if (rank[raiz1] > rank[raiz2])
                swap(raiz1,raiz2);
            
            if (rank[raiz1] == rank[raiz2])
                rank[raiz2]++;

            arvore[raiz2].splice(arvore[raiz2].end(), 
                                      arvore[raiz1]);
        
            pai[raiz1] = pai[raiz2];
            this->n_arvores -= 1;
        }     
};

struct aresta{
    int node1;
    int node2;
    int peso;
    aresta(int p){
        peso = p;
    }
    aresta(int n1, int n2, int p){
        node1 = n1;
        node2 = n2;
        peso = p;
    }
};

vector<vector<pair<int,int>>>grafo;
vector<aresta> mst;
Floresta f;
list<int>*arvore;
int n_nodes;
vector<aresta> best_edges;

void* find_best_edge(void*arg){
    int node = *(int *)arg;
    if(f.pai[node] == node){
        // melhor aresta que liga esta arvore a outra
        arvore[node] = f.arvore[node];
        
        struct aresta best_edge(INFINITY);
        
        // para cada node na arvore
        for(auto node : arvore[node]){
        //olha todas arestas ligadas a este node
            for (auto a : grafo[node]){
                int vizinho           = a.first;
                int peso_node_vizinho = a.second;
                
                //apenas arestas que ligam a arvore a outra
                if (f.Find(vizinho) == f.Find(node)) continue;

                if(best_edge.peso > peso_node_vizinho){
                    best_edge = aresta(node,vizinho,peso_node_vizinho);
                };
                
            }
        }
        pthread_mutex_lock(&mutexEdges);
            best_edges.push_back(best_edge);
        pthread_mutex_unlock(&mutexEdges);
    }
    pthread_exit(NULL);
}

void find_best_edges(){
    int n_nodes = grafo.size();
    pthread_t threadsEdge[n_nodes];
    for (int node = 0; node < n_nodes; node++){
        if(pthread_create(&threadsEdge[node], NULL, &find_best_edge, (void *)&node)){ //Criando uma Thread e passando a função 'decrement' como parâmetro e o ID da Thread como argumento
            perror("Failed to create thread");
        }
    }   
    for(int i = 0; i < n_nodes; i++){ //Join em todas as Threads que já foram criadas
        if(pthread_join(threadsEdge[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }
}

void boruvka(){
    n_nodes = grafo.size();
    f.create(n_nodes);//criar conjunto de arvores (floresta)
   
    //enquanto numero de arvores  > 1:
    while (f.n_arvores >  1){
        //achar melhor edge para cada arvore
        find_best_edges();
        
        //commit das arestas e uniao das arvores:
        for(auto best_edge : best_edges){
            
            int n1 = best_edge.node1;
            int n2 = best_edge.node2;
            
            if(f.Find(n1) != f.Find(n2)){
                mst.push_back(best_edge);
                f.Union(n1,n2);
            }
        }
    }
}

int main() {
        /* Let us create the following graph
       2   3
   (0)--(1)--(2) 
    |      /  |       
   6|   8/    |7       
    |  /      |       
   (3)-------(4)
        9     */
    int V = 5;
    grafo = {
            {make_pair(1,2),make_pair(3,6)},  //0
            {make_pair(0,2),make_pair(2,3)},//1
            {make_pair(1,3),make_pair(3,8),make_pair(4,7)},//2
            {make_pair(0,6),make_pair(2,8),make_pair(4,9)},//3
            {make_pair(3,9),make_pair(2,7)}//4
            };
    arvore = new list<int>[grafo.size()];
    boruvka();
    for (auto a: mst){
        cout<< a.node1<<" - "<<a.node2<< " " << a.peso<< endl;
    }
    return 0;
}