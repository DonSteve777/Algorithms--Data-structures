
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "GrafoValorado.h"

class Camion {
public:
	Camion(GrafoValorado<int> const& G, int src, int wiz) : visit(G.V(), false){
			dfs(G, src, wiz);
	}
	// O(1)
	bool esPosible(int destino) const{
		return visit[destino];
	}

private:
	std::vector<bool>visit;
	bool posible;

	void dfs(GrafoValorado<int> const& G, int src, int wiz) {
		visit[src] = true;

		for (auto a : G.ady(src)) {
			if (a.valor() >= wiz) {
				int w = a.otro(src);
				if (!visit[w])
					dfs(G, w, wiz);
				}
			}
		}
	
};

