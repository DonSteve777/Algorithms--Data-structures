#include <algorithm>
#include <iostream>
#include "Matriz.h"
#include <fstream>
using namespace std;

/*
Recurrencia

tablero(i, j) =
		entrada(i, j) if i == N
		max (entrada(i, j),

		f(1, j) = T[1][j]
		f(i, j) = T[i][j] + max(f(i - 1, j - 1, f(i - 1, j), f(i - 1, j + 1)) i>1:

*/
const vector<pair<int, int>> dirs = { { -1,0 },{ -1,1 },{ -1,-1 }  };


bool valid(int ni, int n) {
	return ni >= 0 && ni < n;
}


int myMax(Matriz<int>  const & entrada, Matriz<int>  const & salida, int i, int j, int n) {
	int ret;
	for (auto d : dirs) {
		int ni = i + d.first, nj = j + d.second;
		if (valid(ni,  n))
			ret = max(salida[i][j], salida[ni][nj] + entrada[i][j]);
	}
	return ret;
}

int myMax2(Matriz<int>  const & entrada, int i, int j, int n) {
	bool izq, vertical, der;
	int ni = i - 1;
	int nj;
	int vi = i - 1, vj = j;

	izq = valid(j - 1, n);
	der = valid(j + 1, n);
	int ret = entrada[vi][vj];

	if (izq){
		nj = j - 1;
		ret = max(ret, entrada[ni][nj]);
	}
	if (der) {
		nj = j + 1;
		ret = max(ret, entrada[ni][nj]);
	}
	return ret;
}


void dinamica(Matriz<int> entrada, int & maximo, int & col) {
	int n = entrada.numcols();
	maximo = -1;
	col = -1;

	for (int i = 1; i < n; i++){
		for (int j = 0; j < n; j++) {
			entrada[i][j] = entrada[i][j] + myMax2(entrada, i, j, n);
			
			if (i == n-1) {
				maximo = max(maximo, entrada[i][j]);
				int anterior = j > 0 ? entrada[i][j-1] : -1;
				col = maximo == entrada[i][j] && maximo != anterior ? j : col;
			}
		}
	}
}


bool resuelveCaso() {
	int N;
	
	cin >> N;

	if (!std::cin)
		return false;
	
	Matriz<int> entrada(N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> entrada[i][j];
		}
	}
	int maximo, col;
	dinamica(entrada, maximo, col);
	cout << maximo << " " << col+1 << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
