#include <vector>
#include "Grafo.h"
#include <algorithm>
#include <queue>
using namespace std;

class Red{
public:
	Red(Grafo const& g, int s, int ttl): visit(g.V(), false), dist(g.V()), s(s){
		inalcanzables = g.V();
		if (s > 0 && s <= g.V()) {
			bfs(g, s - 1, ttl);
			/*for (int i = 0; i < g.V(); i++) {
				if (visit[i] && dist[i] <= ttl)
					--inalcanzables;
			}*/
		}		
  }
	int getInalcanzables() {
		return inalcanzables;
	}

private:
	int inalcanzables;
  vector<bool> visit;
  vector<int> dist;// dist[v] = aristas en el camino s-v más corto
  int s;

  void bfs(Grafo const& g, int s, int ttl) {
	  std::queue<int> q;
	  inalcanzables--;
	  dist[s] = 0; visit[s] = true;
	  q.push(s);
	  while (!q.empty() /*&& dist[i] <= ttl*/) {
		  int v = q.front(); q.pop();
		  //if (dist[v] + 1 < ttl) {
			  for (int w : g.ady(v)) {
				  if (!visit[w] && dist[v] + 1 <= ttl) {
					  inalcanzables--;
					  dist[w] = dist[v] + 1; visit[w] = true;
					  q.push(w);
				  }
			  }
		 // }
	  }
		 
  }
};
