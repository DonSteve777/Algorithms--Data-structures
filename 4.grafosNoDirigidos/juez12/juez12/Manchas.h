#include <vector>
#include "Grafo.h"
#include <algorithm>    // std::max
using namespace std;

using Mapa = vector<string>;	//grafico

class Manchas {
public:
	Manchas(Mapa const& M) : F(M.size()), C(M[0].size()),
		visit(F, vector<bool>(C, false)), num(0), maxim(0){
		
		for (int i = 0; i < F; ++i) {
			for (int j=0; j < C; ++j) {
				if (!visit[i][j] && M[i][j]=='#') {	//nueva mancha
					++num;
					int nuevoTam = dfs(M, i, j);
					maxim = max(maxim, nuevoTam);
				}
			}
		}
	}

	int getNum() {
		return num;
	}

	int getMaxim() { return maxim; }


private:
	int F, C;	//tam mapa
	vector<vector<bool>> visit; // visit[i][j] = se ha visitado el pixel <i,j>
	int num;
	int maxim;


	bool correcta(int i, int j) const {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	const vector<pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1} };

	int dfs(Mapa const& M, int i, int j) {
		visit[i][j] = true;
		int tam = 1;
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {
				tam += dfs(M, ni, nj);
			}
		}
		return tam;
	}
};