#include <vector>
#include "Grafo.h"
#include <algorithm>
using namespace std;

class Amigos{
public:
	Amigos(Grafo const& G): visit(G.V(), false), grupoMasGrande(0){
	  int longitudComponente=0;
	  for (int v = 0; v < G.V(); ++v) {
		  longitudComponente = 0;
		  if (!visit[v]) {
				dfs(G, v, longitudComponente);
				grupoMasGrande = max(longitudComponente, grupoMasGrande);
		  }
	  }
  }

  int getGrupoMasGrande() {
	  return grupoMasGrande;
  }

private:
  vector<bool> visit;
  int grupoMasGrande;
  //vector<int> ant;
//devuelve el número de aristas recorridas
  void dfs(Grafo const& G, int v, int &longitud){
    visit[v] = true;
	longitud++;
    for (int w : G.ady(v)){
      if (!visit[w]){
        //ant[w] = v;
		  //longitud++; aqui cuneto aristas
        dfs(G, w, longitud);
      }
    }
  }
};
