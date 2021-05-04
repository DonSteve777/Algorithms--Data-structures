
// Álvaro Abad de Donesteve

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct registro {
	int momento;
	int id;
	int periodo;
};

bool operator<(registro const& a, registro const& b) {
	return a.momento < b.momento || (a.momento == b.momento && a.id < b.id);
}

/*
priority_queue<registro, vector<registro>, greater<registro>> cola;
bool operator<(registro const& a, registro const& b) {
	return b < a
*/

/*
nuestro propio comparador
   //class com_registro{ tb vale
   struct comp_registro{
      bool operator()(registro const& a, registro const& b){
      return b.momento < a.momento || (a.momento == b.momento && b.id < a.id);
      }

se instancia así
   priority_queue<registro, vector<registro>, comp_registro> cola;
*/



// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() { // o( N log N + k log N)
	int nUsuarios, id, periodo, k;
   // leer los datos de la entrada
	cin >> nUsuarios;
   if (nUsuarios == 0) return false;

   PriorityQueue<registro> cola;

   for (int i = 0; i < nUsuarios; i++) {	// N log N
	   cin >> id;
	   cin >> periodo;
	   cola.push({ periodo, id, periodo });	//log N
   }
   cin >> k; //envíos
	  
   while (k--) {	//O(k log N)
	   auto e = cola.top();	//O(1)
	   cola.pop();	//O(log N)
	   cout << e.id << '\n';
	   e.momento += e.periodo;
	   cola.push(e);
   }
   cout << "---\n";
   
   // escribir sol
   
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
