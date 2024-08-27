#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <iostream>  /* implementações básicas da linguagem */
#include <fstream>   /* manipulação de arquivos */
#include <sstream>   /* manipulação de strings em fluxos de entrada e saída */
#include <vector>    /* implementação do container vector e suas operações */
#include <stack>     /* implementação do container stack e suas operações */
#include <algorithm> /* implementações de algoritmos de ordenação, soma acumulada, reversão de vetores e máximo e mínimos de containers */
#include <map>       /* implementação do container map e suas operações */
#include <cfloat>    /* implementação dos valores maximos para os tipos float e double */
#include <tuple>     /* implementação de tuplas */
#include <functional> /* implementação de função lambda */
#include <unordered_map> /* implementação de mapeamento de variáveis*/

/* implementação do tempo de espera para os ambientes Windows e Unix*/
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#endif // DEFINES_HPP