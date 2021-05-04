#include <iostream>
//https://en.wikipedia.org/wiki/Heapsort
int rightChild(int i) {	return 2 * i + 2; }
int leftChild(int i) {	return 2 * i + 1; }
int parent(int i) {	return (i - 1) / 2; }

//it finds a leaf which has the property that it and all of its 
//ancestors are greater than or equal to their siblings.
template <typename T, typename Comparador>
T leafSearch(std::vector<T> & v, int N, int i) {
	int j = i;
	while ( rightChild(j) <= N) {
		//que hijo es mayor
		if ( v[rightChild(j)] > v[leftChild(j)] ) 
			j = rightChild(j);
		else
			j = leftChild(j);
	}
	//ultimo nivel, quiza solo un hijo
	if (leftChild(j) <= N)
		j = leftChild(j);
	return j;
}

// no entiendo cual es el nodo que se esta eligiendo para flotarlo
template <typename T, typename Comparador>
void siftDown(std::vector<T> & v, int N, int i, Comparador cmp) {
	int j = leafSearch(v, N, i, cmp);
	while (v[i] > v[j])
		j = parent(j);
	int aux = v[j];
	v[j] = v[i];
	while (j > i) {	//flota
		j = (j - 1) / 2;
		swap(aux, v[j]);
	}
}


//fewer comparisons are required to find that location.
template <typename T, typename Comparador = std::less<T>>
void heapsortFloat(std::vector<T> & v, Comparador cmp = Comparador()) {
	// monticulizar
	for (int i = (v.size() - 1) / 2; i >= 0; --i)
		hundir_max(v, v.size(), i, cmp);
	// ordenar
	for (int i = v.size() - 1; i > 0; --i) {
		std::swap(v[i], v[0]);
		siftDown(v, i, 0, cmp);
	}
}

int main() {
	int v[7] = { 4, 3, 7, 2, 5, 6, 1 };

	
}