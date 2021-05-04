#include <iostream>
#include <fstream>
#include "PriorityQueue.h"
#include <cstdlib>

using namespace std;

#define MAX_VALUE 1000000
#define MAX_EVENTOS 200000

/*
quiero tener 2 colas de misma size o diferencia = 1

*/

class ColaMedianas{
	PriorityQueue<int, less<int>> minimos;//= PriorityQueue<int, less<int>>();
	PriorityQueue<int, greater<int>> maximos;//= PriorityQueue<int, less<int>>();
	int totalSize = 0;

public:


	void equilibrar() {
		if (abs(minimos.size() - maximos.size()) > 1) {
			if (minimos.size() > maximos.size()) {
				int elem = minimos.top();
				maximos.push(minimos.top());
				minimos.pop();
			}
			else {
				int elem = maximos.top();
				minimos.push(maximos.top());
				maximos.pop();
			}
		}
	}

	void insertar(int x) {
		if (totalSize == 0)
			maximos.push(x);
		else if (x > mediana())	//tener en cuenta totalSize par o impar??
			minimos.push(x);
		else
			maximos.push(x);
		totalSize++;
		equilibrar();
	}

	bool vacia() const {
		return totalSize == 0;
	}

	int mediana() const {
		if (maximos.size() >= minimos.size())
			return maximos.top();
		else
			return minimos.top();
	}

	void quitarMediana() {
		if (maximos.size() >= minimos.size())
			maximos.pop();
		else
			minimos.pop();
		totalSize--;
	}
};


bool resuelveCaso() {
	int n, x;
	vector<int> v;
	ColaMedianas cola;

	cin >> n;
	if (!std::cin)
		return false;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x > 0) {
		//	int mediana;
		//	if (!cola.vacia())
		//		mediana = cola.mediana();	//debug
			cola.insertar(x);
		}
		else {
			if (cola.vacia())
				cout << "ECSA ";
			else {
				cout << cola.mediana() << " ";
				cola.quitarMediana();
			}
		}
	}
	cout << '\n';
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
