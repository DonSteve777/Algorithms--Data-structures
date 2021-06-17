
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N 100000

struct Edificio {
	int w;
	int e;
};
struct myclass1 {
	bool operator() (Edificio a, Edificio b) {
		return a.w < b.w;
	}
} myobject;


//ordeno por edificio.w creciente
int voraz(vector <Edificio> const& edificios) {
	int N = edificios.size();
	int pasadizos = edificios.size();
	int prev_cE = edificios[0].e;

	for (int i = 1; i < N; ++i) {
		int cW = edificios[i].w;
		int cE = edificios[i].e;

		if (cW < prev_cE) {
			pasadizos--;
			if (cE < prev_cE)
				prev_cE = cE;
		}
		else
			prev_cE = cE;	//para la siguiente iteracion
	}
	return pasadizos;	
}


bool resuelveCaso() {
	int N;

	cin >> N;
	if (N == 0)
		return false;

	vector<Edificio> v(N);
	vector<int> sol;
	int maxE;
	for (int i = 0; i < N; ++i) {
		cin >> v[i].w >> v[i].e;
	}
	sort(v.begin(), v.end(), myobject);

	cout << voraz(v) << '\n';
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
