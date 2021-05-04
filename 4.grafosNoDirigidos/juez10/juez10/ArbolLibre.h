#include <vector>
#include "Grafo.h"
using namespace std;

class ArbolLibre{
public:
  ArbolLibre(Grafo const& G): visit(G.V(), false), s(0){
	  int verticesRecorridos =0;
	  if (G.A() == G.V() - 1) {
		  dfs(G, s, verticesRecorridos);
		  libre = verticesRecorridos == G.V() ? true : false;
	  }
	  else
		  libre = false;
  }

  bool esLibre() {
	  return libre;
  }

private:
  vector<bool> visit;
  bool libre;
  //vector<int> ant;
  int s;
//devuelve el número de aristas recorridas
  void dfs(Grafo const& G, int v, int & verticesRecorridos){
    visit[v] = true;
	verticesRecorridos++;
    for (int w : G.ady(v)){
      if (!visit[w]){
        //ant[w] = v;
		  //verticesRecorridos++;
        dfs(G, w, verticesRecorridos);
      }
    }
  }
};
