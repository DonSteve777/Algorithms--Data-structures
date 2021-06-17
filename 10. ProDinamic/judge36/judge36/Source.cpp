#include <iostream>
#include <fstream>
#include "EnterosInf.h"
#include "Matriz.h"
#include <algorithm>
using namespace std;

EntInf min(EntInf a, EntInf b) {
	if (a < b)
		return a;
	else
		return b;
}


//enfoque descendente o recursivo
vector<int> cambio(vector<int> const& M, int C) {
	int n = M.size();
	Matriz<EntInf> monedas(n + 1, C + 1, Infinito);	//realmente sólo hay que inicialziar la primera fila
	monedas[0][0] = 0;	// i = 0 : conjunto vacío de tipos de monedas

	for (int i = 1; i <= n; ++i) {
		monedas[i][0] = 0;	//cantidad a pagar 0
		for (int j = 1; j <= C; ++j)
			if (M[i - 1] > j)
				monedas[i][j] = monedas[i - 1][j];
			else
				monedas[i][j] = min(monedas[i - 1][j], monedas[i][j - M[i - 1]] + 1);

	}
	//RECONSTRUCCI�N DE LA SOLUCI�N		O(max(n,C))
	vector<int> sol;
	if (monedas[n][C] != Infinito) {	//si hay solución
		int i = n, j = C;
		while (j > 0) {	//no se ha pagado todo
			if (M[i - 1] <= j && monedas[i][j] != monedas[i - 1][j]) {	//seguro hemos tomado una de tipo i
				sol.push_back(M[i - 1]);
				j = j - M[i - 1];
			}
			else if (M[i - 1] <= j && monedas[i][j] == monedas[i - 1][j]) {	//puedo haber cogido i o no
				if (monedas[i][j] == monedas[i][j - M[i - 1]] + 1) {	//si se coge i
					if (M[i - 1] >= M[i - 2]) {	//y su valor es mas alto que el de la opcion de no cger i
						sol.push_back(M[i - 1]);
						j = j - M[i - 1];
					}
					else {
						sol.push_back(M[i - 2]);
						//j = j - M[i - 1];
						--i;
					}
				}
				else
					--i;	//si no se coge i
			}
			else
				--i;
		}
	}
	return sol;
}

//enfoque ascendente
vector<int> cambio1(vector<int> const& M, int C) {
	int n = M.size();
	vector<EntInf> monedas(C + 1, Infinito);
	monedas[0] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = M[i - 1]; j <= C; ++j) {
			monedas[j] = min(monedas[j], monedas[j - M[i - 1]] + 1);
		}
	}
	//reconstrucci�n de la soluci�n
	vector<int> sol;
	if (monedas[C] != Infinito) {
		int i = n, j = C;
		while (j > 0) {	// no se ha pagado todo
			if (M[i - 1] <= j && monedas[j] == monedas[j - M[i - 1]] + 1) {
				sol.push_back(M[i - 1]);
				j = j - M[i - 1];
			}
			else --i;
		}
	}
	return sol;
}



bool resuelveCaso() {
	int target, S;

	cin >> target >> S;
	if (!std::cin)
		return false;

	vector<int> sectores(S);
	for (int i = 0; i < S; i++) {
		cin >> sectores[i];
	}

	vector<int> sol = cambio1(sectores, target);
	int dardos = sol.size();
	if (dardos > 0) {
		cout << dardos << ": ";
		for (int i = 0; i < dardos; i++)
			cout << sol[i] << " ";
		cout << '\n';
	}
	
	else
		cout << "Imposible \n";
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
