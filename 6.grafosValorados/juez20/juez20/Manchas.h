#include <vector>
#include "ConjuntosDisjuntos.h"
#include <string>
#include <algorithm>
using namespace std;

using Mapa = vector<string>;

class Manchas{
public:
	Manchas(Mapa const& M): F(M.size()), C(M[0].size()), visit(F, vector<bool>(C, false)), manchasCjtos(M.size()*M[0].size()){
		int ctoDjto;
		for (int i = 0; i < F; ++i) {
			for (int j = 0; j < C; ++j) {
				if(!visit[i][j] && M[i][j] == '#') {
					 dfs(M, i, j);
					 int nuevoTam = manchasCjtos.cardinal(elemento(i, j));
					maxim = max(maxim, nuevoTam);
				}	
			}
		} 
	}
	void nuevaImagen(Mapa const& M, int i, int j) {
		int a, b;
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == '#') {
				a = elemento(i, j);
				b = elemento(ni, nj);
				if (!manchasCjtos.unidos(a, b)) {	//no creo que haga falta
					manchasCjtos.unir(a, b);
					maxim = max(manchasCjtos.cardinal(a), maxim);
				}
			}
		}
		
	}

  int numero() const { return num; }
  int maximo() const { return maxim; }

private:
	int F, C; //filas columnas

	ConjuntosDisjuntos manchasCjtos;
  vector<vector<bool>> visit;
  int num;	//manchas
  int maxim;

  const vector<pair<int, int>> dirs = { {1, 0},{ 0, 1 },{ -1, 0 },{ 0, -1 }, {1, -1}, {-1, 1},{-1, -1},{1, 1} };
  
  bool correcta(int i, int j) const {
	  return 0 <= i  && i < F && 0 <= j && j < C;
  }

  int elemento(int i, int j) {
	  return i*C + j;
  }
  
  void dfs(Mapa const& M, int i, int j) {
	  visit[i][j] = true;
	  for (auto d : dirs) {
		  int ni = i + d.first, nj = j + d.second;
		  if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {
			  int a, b;
			  a = elemento(i, j);
			  b = elemento(ni, nj);
			  if (!manchasCjtos.unidos(a, b)) {	//no creo que haga falta
				  manchasCjtos.unir(a, b);
			  }
			  dfs(M, ni, nj);
		  }
	  }
  }

};
