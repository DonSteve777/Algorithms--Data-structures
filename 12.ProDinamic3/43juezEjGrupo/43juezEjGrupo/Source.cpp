#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Matriz.h"
using namespace std;

struct decision {
	int posicion;
	int resultado1;
	int resultado2;
};

void asignar(decision d, int p, char r1, char r2) {
	d.posicion = p;
	d.resultado1 = r1;
	d.resultado2 = r2;
}

bool insercion(string entrada, Matriz<decision> & pa, Matriz<decision> & pb, Matriz<decision> & pc) {
	int n = entrada.length();
	int k;
	Matriz<bool> A(n+1, n+1);
	Matriz<bool> B(n+1, n+1);
	Matriz<bool> C(n+1 , n+1);

	for (int i = 1; i <= n; ++i) {
		A[i][i] = entrada[i-1] == 'a';
		B[i][i] = entrada[i-1] == 'b';
		C[i][i] = entrada[i-1] == 'c';
	}

	for (int d = 1; d <= n - 1; ++d) {	//recorrido en diagonales, no habitual
		for (int i = 1; i <= n - d; ++i) {
			int j = i + d;
			A[i][j] = false;
			k = i;
			//A
			while (!A[i][j] && k < j) {
				if (A[i][k] && C[k + 1][j]) {
					A[i][j] = true;
					asignar(pa[i][j], k, 'a', 'c');
				}
				else if (B[i][k] && C[k + 1][j]) {
					A[i][j] = true;
					asignar(pa[i][j], k, 'b', 'c');
				}
				else if (C[i][k] && C[k + 1][j]) {
					A[i][j] = true;
					asignar(pa[i][j], k, 'c', 'a');
				}
				else
					k++;
			}
			B[i][j] = false;
			k = i;
			//B
			while (!B[i][j] && k < j) {
				if (A[i][k] && C[k + 1][j]) {
					B[i][j] = true;
					asignar(pb[i][j], k, 'a', 'c');
				}
				else if (B[i][k] && C[k + 1][j]) {
					B[i][j] = true;
					asignar(pb[i][j], k, 'b', 'c');
				}
				else if (C[i][k] && C[k + 1][j]) {
					B[i][j] = true;
					asignar(pb[i][j], k, 'c', 'a');
				}
				else
					k++;
			}
			//C
			while (!C[i][j] && k < j) {
				if (A[i][k] && C[k + 1][j]) {
					C[i][j] = true;
					asignar(pc[i][j], k, 'a', 'c');
				}
				else if (B[i][k] && C[k + 1][j]) {
					C[i][j] = true;
					asignar(pc[i][j], k, 'b', 'c');
				}
				else if (C[i][k] && C[k + 1][j]) {
					C[i][j] = true;
					asignar(pc[i][j], k, 'c', 'a');
				}
				else
					k++;
			}
		}
	}
	return A[1][n];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	string entrada;
	// leer los datos de la entrada

	cin >> entrada;
	if (!std::cin)  // fin de la entrada
		return false;
	int n = entrada.length();
	Matriz<decision> pa(n+1, n+1);
	Matriz<decision> pb(n + 1, n + 1);
	Matriz<decision> pc(n + 1, n + 1);


	if (insercion(entrada, pa, pb, pc))
		cout << "SI\n";
	else
		cout << "NO\n";

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
