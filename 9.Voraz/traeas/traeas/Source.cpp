#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ConjuntosDisjuntos.h"

using namespace std;

struct Tarea {
	int plazo;
	int beneficio;
	int id;
};

struct myclass1 {
	bool operator()(Tarea a, Tarea b) {
		return a.beneficio > b.beneficio;
	}
} myobject;



// pre: tareas ordenadas
// Coste: lo que mas cuesta es la ordenacion : O(N log N)
int resolver(vector<Tarea> tareas, vector<int> & sol) {
	//inicializaciones O(n)
	int N = tareas.size();
	/* conjusntos disjuntos
	clases de equivalencia libre(i) = libre(j)
	libre(i) : primer predecesor libre del día i
	cada tarea ti debe realizarse en libre(pi), ultimo día libre en su plazo*/
	vector<int> libre(N + 1, 0);
	for (int i = 0; i <= N; ++i)
		libre[i] = i;
	vector<int> plan(N + 1);    //vamos guardando las tareas seleccionadas. puede haber huecos
	ConjuntosDisjuntos particion(N + 1);	//relacion eq: libre(i) = libre(j) mismo primer dia libre
	int beneficio = 0;
	/*
	caso peor:	2n veces buscar, n veces unir
	si ConjuntosDisjuntos incluye union por tamanios y compresion de caminos : O(N log * N) = O(N)
	*/
	//para cada tarea
	for (int i = 0; i < N; ++i) {
		int c1 = particion.buscar(min(N, tareas[i].plazo)); //dia libre representante del conj para plazo i
		int m = libre[c1];  //primer predecesor
		if (m != 0) {
			plan[m] = tareas[i].id;
			beneficio += tareas[i].beneficio;
			int c2 = particion.buscar(m - 1); //clase del dia anterior
			particion.unir(c1, c2);
			libre[c1] = libre[c2];
		}
	}
	//O(N)
	for (int i = 1; i <= N; ++i) {
		if (plan[i] > 0)
			sol.push_back(plan[i]);
	}
	return beneficio;
}

bool resuelveCaso() {
	int N;

	cin >> N;
	if (N == 0)
		return false;

	vector<Tarea> v(N);
	vector<int> sol;

	for (int i = 0; i < N; ++i) {
		cin >> v[i].plazo >> v[i].beneficio;
		v[i].id = i + 1;
	}
	sort(v.begin(), v.end(), myobject);
	for (int i = 0; i < N; ++i) {
		v[i].id = i + 1;
	}
	cout << resolver(v, sol) << '\n';

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
