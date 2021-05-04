using namespace std;
// Nombre y Apellidos

// coste O(n) donde n es el número de agujeros	
#include <iostream>
#include <fstream>
#include <vector>


int parches(vector<int> const& D, int K/*, vector<bool> & g*/) {
	g[0] = true; // sale con el depósito lleno
	int parches = 1;
	int desde = D[0]; 
	for (int i = 1; i < D.size(); ++i) {
		if (D[i] - desde <= K) {
			g[i] = false;	//no implica parche nuevo / inicio de parche 
		}
		else {
			//g[i] = true; // hay que parar
			++parches;
			desde = D[i];
			g[i] = true;
		}
		//desde += D[i]; // seguimos hasta gi+1
	}
	return parches;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, L;	//agujeros, longitud
	vector<int> pos(100000);
   // leer los datos de la entrada
	cin >> N;
   if (!std::cin)  // fin de la entrada
      return false;
   cin >> L;
   for (int i = 0; i < N; i++)
	   cin >> pos[i];
   cout << parches(pos, L) << "\n";
   
   // escribir sol
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
//#ifndef DOMJUDGE
  // std::ifstream in("casos.txt");
 //  auto cinbuf = std::cin.rdbuf(in.rdbuf());
//#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
//#ifndef DOMJUDGE
 //  std::cin.rdbuf(cinbuf);
 //  system("PAUSE");
//#endif
   return 0;
}
