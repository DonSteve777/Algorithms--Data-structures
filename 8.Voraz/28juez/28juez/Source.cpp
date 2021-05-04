using namespace std;
// Nombre y Apellidos

// coste O(n) donde n es el número de agujeros	
#include <iostream>
#include <fstream>
#include <vector>

//O(nlogn). Mejor coste para ordenación
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(vector<int> & arr, int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;
	// Create temp arrays
	vector<int> L(n1), R(n2);
	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	// Merge the temp arrays back into arr[l..r]
	// Initial index of first subarray
	int i = 0;
	// Initial index of second subarray
	int j = 0;
	// Initial index of merged subarray
	int k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(vector<int> & v, int l, int r) {
	if (l >= r) {
		return;//returns recursively
	}
	int m = (l + r - 1) / 2;
	mergeSort(v, l, m);
	mergeSort(v, m + 1, r);
	merge(v, l, m, r);
}

int victoria(vector<int> const& enemigos, vector<int> const& equipos, vector<bool> & g) {
	int victorias = 0;
	int j = 0, i = 0;
	while (i < enemigos.size() && j < enemigos.size()) {
		if (enemigos[i] <= equipos[j]) {
			g[i] = true;	
			victorias++;
			j++;
			i++;
		}
		else {
			g[i] = false;
				j++;
		}
	}
	return victorias;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N;	//agujeros, longitud
	// leer los datos de la entrada
	cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;
	vector<int> enemigos(N);
	vector<int> equipos(N);
	vector<bool> g(N, false);
	for (int i = 0; i < N; i++)
		cin >> enemigos[i];
	for (int i = 0; i < N; i++)
		cin >> equipos[i];

	mergeSort(enemigos, 0, N - 1);
	mergeSort(equipos, 0, N - 1);
	cout << victoria(enemigos, equipos, g) << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
	//#ifndef DOMJUDGE
	 //std::ifstream in("casos.txt");
	  //auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
	//#ifndef DOMJUDGE
	  //std::cin.rdbuf(cinbuf);
	  //system("PAUSE");
	//#endif
	return 0;
}
