#include <iostream>
#include <vector>
//#include <fstream>
#include <queue>
#include "Matriz.h"
#include <limits>
using namespace std;


struct Nodo {
	vector<int> sol;		//sol[i] = j		funcionario i, tarea j
	int k;
	int tiempo;	//tiempo acumulado
	int tiempo_estimado;	//prioridad
	vector<bool> asignado; //trabajo ya asignado?
	bool operator<(Nodo const& otro) const {
		return otro.tiempo_estimado < tiempo_estimado;
	}
};

//cota inferior: minimos tiempos para los funcionarios que quedan
/*
int pesimista(Nodo const& X, Matriz<int> relacion) {
	int estimacion = X.tiempo;
	int k = X.k;
	int anterior = numeric_limits<int>::infinity();
	for (int i = 0; i < relacion.numcols(); ++i) {
		if (!X.asignado[i]) {
			estimacion += relacion[k][i];
			++k;
		}
	}
	return estimacion;
}*/

// ret optimista[]. para el funcionario i contiene el tiempo optimista que queda (el minimo)
void pre_calculo_optimista(Matriz<int> relacion, vector<int> & optimista) {
	int N = relacion.numcols();
	optimista = vector<int>(N, 0);
	vector<int> rapido(N, 0);

	for (int i = 0; i < N; ++i) {
		rapido[i] = relacion[i][0];
		for (int j = 1; j < relacion.numcols(); ++j) {
			rapido[i] = min(relacion[i][j], optimista[i]);
		}
	}
	for (int j = N - 1; j = 0; --j) {
		optimista[j] += rapido[j];
	}
}

int funcionarios_rp(Matriz<int> const& relacion) {
	int tiempo_mejor = numeric_limits<int>::max();
	int N = relacion.numfils();
	Nodo Y;
	vector<int> optimista;

	Y.sol = vector<int>(N, -1);
	Y.k = -1;
	Y.tiempo = 0;
	pre_calculo_optimista(relacion, optimista);
	Y.tiempo_estimado = optimista[0];
	priority_queue<Nodo > cola;
	Y.asignado = vector<bool>(N, false);
	cola.push(Y);


	while (!cola.empty() && (cola.top().tiempo_estimado <= tiempo_mejor)) {
		Y = cola.top();	cola.pop();
		Nodo X(Y);
		++X.k;
		for (int i = 0; i < N; ++i) {	//pruebo todas las tareas, a ver cual renta
			if (!X.asignado[i]) {
				X.sol[X.k] = true;
				X.tiempo = Y.tiempo + relacion[X.k][i];
				X.tiempo_estimado = X.tiempo + optimista[X.k];	//lo que llevo + lo que queda
				X.asignado[i] = true;

				if (X.tiempo_estimado < tiempo_mejor) {
					if (X.k == N - 1)
						tiempo_mejor = X.tiempo;
					else
						cola.push(X);
				}
				X.asignado[i] = false;	//desmarco
			}
		}
	}
	return tiempo_mejor;
}

bool resuelveCaso() {
	int N; //funcionarios y trabjos

	cin >> N;
	if (N == 0)
		return false;

	Matriz<int> relacion(N, N);	//relacion funcionrio i trabajo j
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cin >> relacion[i][j];
	}

	cout << funcionarios_rp(relacion) << "\n";
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
/*#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
*/
	while (resuelveCaso());

	// para dejar todo como estaba al principio
/*#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif*/
	return 0;
}
