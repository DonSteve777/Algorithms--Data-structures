#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
using namespace std;

#define MAX_VALUE 1000000

/*
opcion 1: tenerlo ordenado de forma creciente
opcion 2: ordenar por prioridad de cercania a la mediana
*/

template <typename T = int, typename Comparator = std::less<T>>
class ColaMedianas : PriorityQueue<T, Comparator> {

public:

	ColaMedianas(Comparator c = Comparator()) : PriorityQueue(c) {}

public:

	void insertar(int x) {
		this->push(x);
	}

	bool vacia() const {
		return empty();
	}

	int mediana() const {
		if (empty()) throw std::domain_error("cola vacia exception");
		std::vector<T> sortedArray = array;
		std::vector<int> position(MAX_VALUE, 0);

		int size = array.size() - 1;
		for (int i = 1; i < (int)array.size(); i++) {
			int j = array[i];
			position[j] = i;
		}
		heapsort(sortedArray, antes);
		int N = sortedArray.size() - 1;
		int mediana = sortedArray[(N + 1) / 2];
		return position[mediana];
	}

	void quitarMediana() {
		if (empty())
			throw std::domain_error("cola vacia exception");
		else {
			int positionMediana = mediana();
			array[positionMediana] = std::move(array.back());
			array.pop_back();
			if (!empty()) hundir(positionMediana);
		}
	}
};

template <typename T, typename Comparador = std::less<T>>
void heapsort(std::vector<T> & v, Comparador cmp = Comparador()) {
	// monticulizar
	for (int i = (v.size() - 1) / 2; i >= 0; --i)
		hundir_max(v, v.size(), i, cmp);
	// ordenar
	for (int i = v.size() - 1; i > 0; --i) {
		// eliminar top
		std::swap(v[i], v[0]);
		//restaurar monticulo sin antiguo top
		hundir_max(v, i, 0, cmp);
	}
}

template <typename T, typename Comparador>
void hundir_max(std::vector<T> & v, int N, int j, Comparador cmp) {
	// montículo en v en posiciones de 0 a N-1
	T elem = v[j];
	int hueco = j;
	int hijo = 2 * hueco + 1; // hijo izquierdo, si existe
	while (hijo < N) {
		// cambiar al hijo derecho si existe y va antes que el izquierdo
		if (hijo + 1 < N && cmp(v[hijo], v[hijo + 1]))
			++hijo;
		// flotar el hijo mayor si va antes que el elemento hundiéndose
		if (cmp(elem, v[hijo])) {
			v[hueco] = v[hijo];
			hueco = hijo; hijo = 2 * hueco + 1;
		}
		else break;
	}
	v[hueco] = elem;
}

bool resuelveCaso() {
	int n, x;
	vector<int> v;


	cin >> n;
	if (!std::cin)
		return false;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x > 0)
			cola.insertar(x);
		else {
			if (cola.vacia())
				cout << "ECSA ";
			else {
				cout << cola.mediana() << " ";
				cola.quitarMediana();
			}
		}
	}
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
