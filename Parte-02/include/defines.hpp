#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <iostream>   /* implementações básicas da linguagem */
#include <fstream>    /* manipulação de arquivos */
#include <sstream>    /* manipulação de strings em fluxos de entrada e saída */
#include <vector>     /* implementação do container vector e suas operações */
#include <stack>      /* implementação do container stack e suas operações */
#include <algorithm>  /* implementações de algoritmos de ordenação, soma acumulada, reversão de vetores e máximo e mínimos de containers */
#include <map>        /* implementação do container map e suas operações */
#include <cfloat>     /* implementação dos valores maximos para os tipos float e double */
#include <functional> /* implementação de funções lambda */
#include <queue>      /* implementação do container queue e suas operações */
#include <cstdlib>    /* implementação do rand() */
#include <ctime>      /* implementação do time() */
#include <cmath>      /* implementação do ceil() */
#include <iomanip>    /* manipulação de entrada e saída */

using namespace std;  /* definição do namespace padrão */

/* implementação do tempo de espera para os ambientes Windows e Unix*/
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#endif // DEFINES_HPP