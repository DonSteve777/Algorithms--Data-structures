#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Cancion {
	int duracion;
	int puntuacion;
};

struct Nodo {
	vector<int> sol;
	int k;
	int beneficio;
	int beneficio_est;	//prioridad
	int tiempoGrabado[2];	//en cada cara
	bool operator<(Nodo const & otro) const {
		return otro.beneficio_est > beneficio_est;
	}
};

int optimista(vector<Cancion> const& canciones, int cara, Nodo Y) {
	int hueco = cara - (Y.tiempoGrabado[0] + Y.tiempoGrabado[1]);
	int N = canciones.size();
	int opt = Y.beneficio;
	int j = Y.k + 1;

	while (j < N && canciones[j].duracion <= hueco) {	//gabar j
		hueco = hueco - canciones[j].duracion;
		opt += canciones[j].puntuacion;
		++j;
	}
	if (j < N-1) {	//quedan canciones. estimacion como la mochila
		opt += (hueco / canciones[j].duracion) * canciones[j].puntuacion;
	}
	return opt;
}

int pesimista(vector<Cancion> const& canciones, int cara, Nodo Y) {
	int aux[2];
	int N = canciones.size();
	int pes = Y.beneficio;
	int j = Y.k + 1;

	aux[0] = Y.tiempoGrabado[0];
	aux[1] = Y.tiempoGrabado[1];


	while (j < N && (aux[0] <= cara || aux[1] <= cara) ) {
		if (aux[0] + canciones[j].duracion <= cara) {
			aux[0] += canciones[j].duracion;
			pes += canciones[j].puntuacion;
		}
		else {
			if (aux[1] + canciones[j].duracion <= cara) {
				aux[1] += canciones[j].duracion;
				pes += canciones[j].puntuacion;
			}
		}
		j++;
	}
	return pes;
}

void maxGrabacion(vector<Cancion> const& canciones, int cara, vector<int>sol_mejor, int & beneficio_mejor) {
	int N = canciones.size();
	//se genera la raiz
	Nodo Y;
	Y.sol = vector<int>(N);
	Y.k = -1;
	Y.beneficio = 0;
	Y.beneficio_est = optimista(canciones, cara, Y);
	priority_queue<Nodo> cola;
	cola.push(Y);
	beneficio_mejor = pesimista(canciones, cara, Y);

	while (!cola.empty() && cola.top().beneficio_est > beneficio_mejor) {
		Y = cola.top(); cola.pop();
		Nodo X(Y);
		++X.k;
		//grabar X.k en cara 1
		if (Y.tiempoGrabado[0] + canciones[X.k].duracion <= cara) {
			X.sol[X.k] = 1;
			X.tiempoGrabado[0] = Y.tiempoGrabado[0] + canciones[X.k].duracion;
			X.tiempoGrabado[1] = Y.tiempoGrabado[1];
			X.beneficio = Y.beneficio + canciones[X.k].puntuacion;
			X.beneficio_est = Y.beneficio_est;
			if (X.k == N-1) {
				sol_mejor = X.sol;
				beneficio_mejor = X.beneficio;
			}
			else
			{
				cola.push(X);
			}
		}
		else {
			if (Y.tiempoGrabado[0] != Y.tiempoGrabado[1]) {
				//grabar en la cara 2
				if (Y.tiempoGrabado[1] + canciones[X.k].duracion <= cara) {
					X.sol[X.k] = 2;
					X.tiempoGrabado[0] = Y.tiempoGrabado[0];
					X.tiempoGrabado[1] = Y.tiempoGrabado[1] + canciones[X.k].duracion;
					X.beneficio = Y.beneficio + canciones[X.k].puntuacion;
					X.beneficio_est = Y.beneficio_est;
					if (X.k == N-1) {
						sol_mejor = X.sol;
						beneficio_mejor = X.beneficio;
					}
					else
					{
						cola.push(X);
						beneficio_mejor = max(beneficio_mejor, pesimista(canciones, cara, X));
					}
				}
			}
		}
	}
}

bool resuelveCaso() {
	int N, cara; //canciones
	int ret;

	cin >> N;
	if (N == 0)
		return false;
	cin >> cara;

	vector<Cancion> canciones(N);
	vector<int> sol(N);

	for (int i = 0; i < N; i++) {
		cin >> canciones[i].duracion >> canciones[i].puntuacion ;
	}

	maxGrabacion(canciones, cara, sol, ret);
	cout << ret << "\n";
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
