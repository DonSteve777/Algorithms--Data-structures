///////////////////////////////////////////////////////
              //  Tiro al palíndromo
///////////////////////////////////////////////////////
/*Recursión:
    
    if (patitios[i] == patitios[j])
        patindromo (i + 1, j - 1) + 2 
    else    !=
        max(patindromo(i + 1, j), patindromo(i, j-1))

Casos base
    patindormo (i, j) = 1      si i = j   solo tenemos un patitio
    patrindormo(i, j) = 0      si i > j      no tenemos patitos

Lamada inicial
    patindromo(0, n -1 )

Problema repetidos: quitar el primer y el ultimo patito

Tabla n*n
    solo usamos los valores por encima de la diagonal principal de casos base*/

//Si queremos reconstruir la solución no podemos mejorar 
//el espacio adicional => Enfoque descendente


int patin_rec(string const & patitos, int i, int j, Matri<int> & patin){
    int & res = patin[i][j];
    if(res == -1){  // ya resuelto el subnproblema??
        if (i > j ) res = 0;  //no hay patitos
        else if (i == j) res = 1;
        else {
            if (patitos[i] == patitos[j]){
                res = patin_rec( i + 1, j - 1) + 2;
            }
            else 
                res = max( patin_rec( i + 1 , j, patin ), patin_rec( i , j-1, patin));
        }
    }
    return ret;
}

//O (n^2)  ConcatenCIÓN TIENE COSTE LINEAL
//llamada incial: i = 0 , j = n-1
string reconstruir(string const & patitos,  Matri<int> & patin, int i, int j ){
    if ( i > j) return {}; // empty string
    if (i == j) return { patitos[i] };  //cadena de un carácter
    if (patitos[i] == patitos[ j ])
        return patitos[i] + reconstruir(patitos, patin, i + 1, j - 1) + patitos[j];
    else if (patin[i][j] == patin[i + 1][j])
        return reconstruir (patitos, patin, i+1, j);
    else 
        return reconstruir (patitos, patin, i, j-1);
}

//Se puede reducir el coste con un parámetro acumulador
void reconstruir(string const & patitos,  Matri<int> & patin, int i, int j, string &sol ){
    if ( i > j) return;
    if (i == j) return sol.psuh_back(patitos[i]) ;
    else if (patitos[i] == patitos[ j ]){
        sol.push_back(patitos[i]);
        reconstruir(patitos, patin, i + 1, j - 1) ;
        sol.push_back(patitos[j]);

    }else if ( patin[i][j] == patin[i + 1][j] )
        reconstruir (patitos, patin, i+1, j, sol);
    else 
        reconstruir (patitos, patin, i, j-1, sol) ;
}

int main(){
    string patitos;
    cin >> patitos;

    int n = patitos.lenght();

    Matriz<int> patindromo(n, n, -1);
    cout << patin_rec(patitos, 0, n-1, patindromo) << '\n';
    cout << reconstruir(patitos, patindromo, 0, n-1) << '\n';

    string sol;
    reconstruir(patitos, patindromo, 0, n-1, sol);
    cout << sol << '\n';

    return 0;
}

