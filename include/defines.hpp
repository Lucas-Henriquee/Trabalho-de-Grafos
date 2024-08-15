#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <algorithm> /* implementações de algoritmos de ordenação, soma acumulada, reversão de vetores e máximo e mínimos de containers */
#include <cmath>     /* implementações de algoritmos matemáticos e estatísticos */
#include <fstream>   /* manipulação de arquivos */
#include <iomanip>   /* manipulação de saída e entrada de dados */
#include <iostream>  /* implementações básicas da linguagem */
#include <utility>   /* implementações de alguns containers e operações de swap */
#include <vector>    /* implementação do container vector e suas operações */
#include <sstream>   /* manipulação de strings em fluxos de entrada e saída */
#include <stack>     /* implementação do container stack e suas operações */
#include <limits>    /* implementação dos valores maximos para os tipos primitivos */
#include <map>       /* implementação do container map e suas operações */
#include <cfloat>    
#include <functional>/* implementação de funções lambda */

/* implementação do tempo de espera */
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#endif // DEFINES_HPP