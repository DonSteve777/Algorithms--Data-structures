#include <iostream>
#include <fstream>
#include "Matriz.h" 
#include "EnterosInf.h"
using namespace std;

/**
* economista: lo mas barato
* ingeniero: min numero de cordeles
* matematico: formas diferentes


cordeles(i, j) = min cordeles para formar cuerda de longitud j,
considerando cordeles de tipo 1 al n

Recursión
si mi > j
	cordeles(i -1, j) 	no cogemos tipo i: cogemos monedas mas pequenias
si mi <= j
min(
	cordeles(i-1, j),
	cordeles(i, j-mi) +1)
*/
EntInf min(EntInf a, EntInf b) {
	if (a < b)
		return a;
	return b;
}

void cometa(vector<int> const & l, vector<int> const & c, int L, EntInf & coste, EntInf & numCordeles, EntInf & formas) {
	int n = l.size();
	Matriz<EntInf> cordeles(n + 1, L + 1, Infinito);	//realmente sólo hay que inicialziar la primera fila
	cordeles[0][0] = 0;
	Matriz<EntInf> economico(n + 1, L + 1, Infinito);
	economico[0][0] = 0;
	Matriz<EntInf> matematico(n + 1, L + 1, 0);

	for (int i = 1; i <= n; ++i) {
		cordeles[i][0] = 0;	//cordeles necsarios para formar cuerda de longitud 0 : 0
		economico[i][0] = 0;
		//matematico[i][0] = 0;

		for (int j = 1; j <= L; ++j)
			if (l[i - 1] > j) {	//cordel actual demasiado largo
				cordeles[i][j] = cordeles[i - 1][j];
				economico[i][j] = economico[i - 1][j];
				matematico[i][j] = matematico[i - 1][j];
			}
			else if (l[i - 1] == j){	//cordel actual justo de la longitud deseada
				cordeles[i][j] = 1;
				economico[i][j] = min(economico[i - 1][ j], economico[i - 1][j - l[i - 1]] + c[i-1]);	//min entre coger actual y no cogerlo
				matematico[i][j] = matematico[i-1][j]+1;
			}
			else {
				cordeles[i][j] = min (cordeles[i - 1][j], cordeles[i - 1][j - l[i - 1]] + 1);
				economico[i][j] = min(economico[i - 1][j], economico[i - 1][j - l[i - 1]] + c[i - 1]);	//min entre coger actual y no cogerlo
				EntInf a = matematico[i - 1][j];
				EntInf b = matematico[i - 1][j - l[i - 1]];
				matematico[i][j] = matematico[i - 1][j] + matematico[i-1][j - l[i - 1]];
			}
	}
	coste = economico[n][L];
	numCordeles =  cordeles[n][L];
	formas = matematico[n][L];
}





bool resuelveCaso() {
	int N, L;

	cin >> N >> L;
	if (!std::cin)
		return false;

	vector<int> l(N);
	vector<int> c(N);
	for (int i = 0; i < N; i++) {
		cin >> l[i] >> c[i];
	}

	EntInf numCordeles = 0;
	EntInf coste = 0;
	EntInf formas;
	cometa(l, c, L, coste, numCordeles, formas);
	if (numCordeles != Infinito)
		cout << "SI " << formas << " " << numCordeles << " " << coste <<  '\n';
	else
		cout << "NO" << '\n';
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
