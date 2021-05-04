

using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h" 

#define INF 1000000000000


// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int ebanisto(vector<int> const& cortes, Matriz<int> & esfuerzo){
	int n = cortes.size();
	Matriz<int> esfuerzo(n + 1, n + 1, 0);

	for (int i = 1; i <= n - d; ++i) {	//elementos en la diagonal
		
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int L, N;
	
	// leer los datos de la entrada
	cin >> L >> N;
	if (!L && !N)
		return false;

	vector<int> cortes(N, 0);

	for (int i = 0; i < N; ++i)
		cin >> cortes[i];

	Matriz<int> esfuerzo(N, N, INF);
	cout << ebanisto(cortes, esfuerzo);

	return true;
}


//Coste en tiempo: O(n^3)
//Coste en espacio: O(n^2)
int multiplica_marices(vector<int> const& D, Matriz<int> & P) {
	int n = D.size() - 1;
	Matriz<int> matrices(n + 1, n + 1, 0);	//aunque sólo usa de la 1 a la n
	P = Matriz<int>(n + 1, n + 1, 0);
	for (int d = 1; d <= n - 1; ++d)	//diagonales
		for (int i = 1; i <= n - d; ++i) {	//elementos en la diagonal
			int j = i + d;
			matrices[i][j] = INF;
			//cálculo del mínimo
			for (int k = i; k <= j - 1; ++k) {
				int temp = matrices[i][k] + matrices[k + 1][j] + D[i - 1] * D[k] * D[j];
				if (temp < matrices[i][j]) {
					matrices[i][j] = temp;
					P[i][j] = k;
				}
			}
		}
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
