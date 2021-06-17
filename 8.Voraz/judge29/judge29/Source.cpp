#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


struct tMovie {
	int start;
	int length;
};

//ordeno por hora de finalizacion
struct myclass1 {
	bool operator() (tMovie i, tMovie j) { 
		return (i.length + i.start) < (j.length + j.start); 
	}
} myobject;



// pre : oredenadas
int voraz(vector<tMovie> const & v, int N) {
	vector<bool> verPeli(v.size(), false);
	int ahora;
	int pelis = 0;

	if (N > 0) {
		verPeli[0] = true;
		pelis++;
		ahora = v[0].start + v[0].length;
		for (int i = 0; i < N; i++) {
			if (v[i].start >= ahora + 10) {
				pelis++;
				verPeli[i] = true;
				ahora = v[i].start + v[i].length;
			}
		}
	}

	return pelis;
}
// COSTE
// es un for + un sort = lineal + n log n 
//O n log n

bool resuelveCaso() {
	int N;

	cin >> N;
	if (N == 0)
		return false;

	tMovie film;
	vector<tMovie> maraton;
	char dospuntos;
	int hh, mm;

	for (int i = 0; i < N; i++) {
		//cin.ignore();
		//getline(cin, film.start, ' ');
		cin >> hh;
		cin >> dospuntos;
		cin >> mm;
		film.start = hh * 60 + mm;
		cin >> film.length;
		maraton.push_back(film);
	}
	sort(maraton.begin(), maraton.end(), myobject);
	cout << voraz(maraton, N) << '\n';

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
