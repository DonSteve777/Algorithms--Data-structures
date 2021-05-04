//Problema de la mochila con objetos enteros
///////////////////////////////////////////////////////
        //Problema de la mochila con objetos enteros
///////////////////////////////////////////////////////
/*
Si se pueden dividir lo resolvíamos con voraz

La solución va a ser un conjunto de índices
j = peso máx
objetos del 1 al i

Se cunple optimalidad de Bellman: 
así que podemos definirlo de manera recursiva


///////////////////////////////////////////////////////
                Tiro al palíndromo
///////////////////////////////////////////////////////
Recursión:
    
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
    solo usamos los valores por encima de la diagonal principal de casos base