using namespace std;
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include "Sumidero.h"  // propios o los de las estructuras de datos de clase


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int V, A;	//tareas, relaciones
	int v, w;
   
	cin >> V;
   if (!std::cin)  // fin de la entrada
      return false;
   cin >> A;

   Digrafo g(V);
   for (int i = 0; i < M; i++) {
	   cin >> v >> w;
	   g.ponArista(v-1, w-1);
   }
   Sumidero sum(g);
   if (sum.hayCiclo())
	   cout << "Imposible";
   else {
	   vector<int> _orden = orden.orden();
	   for (int w : _orden) {
		   cout << w << " ";
	   } 
   }
	   
   cout << "\n";
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
