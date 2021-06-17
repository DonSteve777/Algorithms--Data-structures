#include <iostream>
#include <fstream>
#include <string>
#include"EnterosInf.h"
#include "Matriz.h"
#include <algorithm>
using namespace std;

/*
Recursion
	aiofobia(i, j) =
			aiofobia(i+1, j-1)		if patitos[i] == patitos[j]
			min ( aiofobia(i+1, j) , aiofobia(i, j+1) )		else
*/

int patin_rec(string const& patitos, int i, int j, Matriz<int> & patin) {
	int & res = patin[i][j];
	if (res == -1) {
		if (i > j) res = 0;
		else if (i == j) res = 0;
		else if (patitos[i] == patitos[j])
			res = patin_rec(patitos, i + 1, j - 1, patin);
		else
			res = 1 + min(patin_rec(patitos, i + 1, j, patin) ,
				patin_rec(patitos, i, j - 1, patin) );
	}
	return res;
}

EntInf min(EntInf a, EntInf b) {
	if (a < b)
		return a;
	else
		return b;
}


EntInf patinAscendente(string const& patitos,) {
	int N = patitos.length();
	Matriz<EntInf> patin
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= i ; j++)
		{
			if (i > j) patin[i][j] = 0;
			else if (i == j) patin[i][j] = 0;
			else if (patitos[i] == patitos[j])
				patin[i][j] = patin[i + 1][j - 1];
			else
				patin[i][j] = (EntInf)1 + min(patin[i + 1][j],
					patin[i][j - 1]);
		}
	}
	
	return patin[0][N-1];
}

string reconstruir(string const& patitos, Matriz<EntInf> const& patin, int i, int j) {
	if (i > j)	return{};
	if (i == j) return { patitos[i] };
	if (patitos[i] == patitos[j])
		return patitos[i] + reconstruir(patitos, patin, i + 1, j - 1) + patitos[j];
	else if (patin[i][j] == patin[i + 1][j] + 1)
		return patitos[i] + reconstruir(patitos, patin, i + 1, j) + patitos[i];
	else
		return patitos[j] + reconstruir(patitos, patin, i, j - 1) + patitos[j];
}
/*
string reconstruir(string const& patitos, Matriz<EntInf> const& patin,	int i, int j) {
	if (i > j)	return{};
	if (i == j) return { patitos[i] };
	if (patitos[i] == patitos[j])
		return patitos[i] + reconstruir(patitos, patin, i + 1, j - 1) + patitos[j];
	else if (patin[i][j] == patin[i + 1][j] + 1)
		return patitos[i] + reconstruir(patitos, patin, i + 1, j) + patitos[i];
	else
		return patitos[j] + reconstruir(patitos, patin, i, j - 1) + patitos[j];
}*/


bool resuelveCaso() {
	string caso;
	cin >> caso;

	if (!std::cin)
		return false;
	int N = caso.length();
	//Matriz<EntInf> patin(N, N, Infinito);
	//Matriz<int> patin(N, N, -1);
	//cout << patin_rec(caso, 0, N - 1, patin) << " ";
	cout << patinAscendente(caso, patin) << " ";
	cout << reconstruir(caso, patin, 0, N - 1) << '\n';

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
