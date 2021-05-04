#include <iostream>
#include <fstream>
using namespace std;


bool resuelveCaso() {
   
   
   if (caso especial)
      return false;
   
      
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
