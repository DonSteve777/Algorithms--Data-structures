template <typename T, typename Comparador = std::less<T>>
void heapsort(std::vector<T> & v, Comparador cmp = Comparador()) {
	// monticulizar
	for (int i = (v.size() - 1) / 2; i >= 0; --i)
		hundir_max(v, v.size(), i, cmp);
	// ordenar
	for (int i = v.size() - 1; i > 0; --i) {
		// eliminar top
		std::swap(v[i], v[0]);
		//restaurar monticulo (sin el antiguo top)
		hundir_max(v, i, 0, cmp);
	}
}

template <typename T, typename Comparador>
void hundir_max(std::vector<T> & v, int N, int j, Comparador cmp) {
	// montículo en v en posiciones de 0 a N-1
	T elem = v[j];
	int hueco = j;
	int hijo = 2 * hueco + 1; // hijo izquierdo, si existe
	while (hijo < N) {
		// cambiar al hijo derecho si existe y va antes que el izquierdo
		if (hijo + 1 < N && cmp(v[hijo], v[hijo + 1]))
			++hijo;
		// flotar el hijo mayor si va antes que el elemento hundiéndose
		if (cmp(elem, v[hijo])) {
			v[hueco] = v[hijo];
			hueco = hijo; hijo = 2 * hueco + 1;
		}
		else break;
	}
	v[hueco] = elem;
}

string a_minusculas(string s) {
	for (char & c : s) c = tolower(c);
	return s;
}

class ComparaString {
public:
	bool operator()(string a, string b) {
		return a_minusculas(a) < a_minusculas(b);
	}
};

heapsort(datos, ComparaString());