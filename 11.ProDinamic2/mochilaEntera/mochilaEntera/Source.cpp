#include <iostream>
#include <vector>
#include <algorithm>
#include "Matriz.h"
using namespace std;

struct Objeto { int peso; double valor; };

double mochila_rec(vector<Objeto> const& obj, int i, int j,
	Matriz<double> & mochila) {
	if (mochila[i][j] != -1) // subproblema ya resuelto
		return mochila[i][j];
	if (i == 0 || j == 0) mochila[i][j] = 0;
	else if (obj[i - 1].peso > j)
		mochila[i][j] = mochila_rec(obj, i - 1, j, mochila);
	else
		mochila[i][j] = max(mochila_rec(obj, i - 1, j, mochila),
			mochila_rec(obj, i - 1, j - obj[i - 1].peso, mochila)
			+ obj[i - 1].valor);
	return mochila[i][j];
}

double mochila(vector<Objeto> const& objetos, int M, vector<bool> & sol) {
	int n = objetos.size();
	Matriz<double> mochila(n + 1, M + 1, -1);
	double valor = mochila_rec(objetos, n, M, mochila);
	// cálculo de los objetos
	int i = n, j = M;
	sol = vector<bool>(n, false);
	while (i > 0 && j > 0) {	
		if (mochila[i][j] != mochila[i - 1][j]) {
			sol[i - 1] = true; j = j - objetos[i - 1].peso;
		}
		--i;
	}
	return valor;
}

