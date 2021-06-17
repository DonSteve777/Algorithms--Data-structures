#pragma once
#include <vector>
#include "ConjuntosDisjuntos.h"
#include <algorithm>    // std::max
using namespace std;

#define MAX_DIM 1000

/*
En el problema de las manchas se usaba un recorrido dfs de manera que se recorría toda la
matriz y además cada componente conexa otra vez O(v+A + F*C)
No se construía el grafo

*/
using Mapa = vector<string>;	//grafico

class Manchas {
public:
	Manchas(Mapa & M, int F, int C) : F(F), C(C),
		maxim(0), cj(C*F), visit(F, vector<bool>(C, false)) {
		
		for (int i = 0; i < F; ++i) {
			for (int j = 0; j < C; ++j) {
				if (!visit[i][j] && M[i][j] == '#'){
					dfs(M, i, j);	//O(V+A)
					int tam = cj.cardinal(elem(i, j));
					maxim = max(maxim, tam);
				}
			}
		}
	}

	void nuevaMancha(int i, int j, Mapa & M) {
		M[i][j] = '#';
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == '#') {
				int a = elem(i, j);
				int b = elem(ni, nj);
				cj.unir( a, b);
				maxim = max( cj.cardinal(a), maxim);
			}
		}
	}


	int getMaxim() { return maxim; }


private:
	int F, C;
	vector<vector<bool>> visit;
	int maxim;
	ConjuntosDisjuntos cj;

	void dfs(Mapa const& map, int i, int j) {
		visit[i][j] = true;
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && map[ni][nj] == '#' && !visit[ni][nj]) {
				dfs(map, ni, nj);
				int a = elem(i, j);
				int b = elem(ni, nj);
				cj.unir(a, b);
			}
		}
	}
	
	int elem(int i, int j) {	//asigno un valor para el conjunto a cada mancha segun sus cordenadas
		return i*C + j;
	}

	bool correcta(int i, int j) const {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	const vector<pair<int, int>> dirs = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 }, {1, -1 }, {-1, 1}, {-1, -1}, {1, 1} };

	
};