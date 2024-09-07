# Biblioteca de Grafos em C++

## 🎯 Resumo

Este projeto implementa uma biblioteca em C++ para manipulação de grafos simples, tanto direcionados quanto não direcionados, e ponderados ou não ponderados. Utilizando listas de adjacência, a biblioteca oferece uma série de funcionalidades úteis para a análise e manipulação de grafos. Na segunda parte, a biblioteca foi estendida para incluir algoritmos avançados de particionamento de grafos, focando na resolução do Minimum Gap Graph Partitioning Problem (MGGPP). Esses algoritmos visam minimizar a diferença de pesos dentro de subgrafos conectados.

## 🚀 Parte 1 - Algoritmos Clássicos de Grafos

1. **Fecho Transitivo Direto**
   - **Descrição:** Calcula o fecho transitivo direto de um vértice em um grafo direcionado.
   - **Parâmetro:** ID do vértice.
   - **Saída:** Fecho transitivo direto.

2. **Fecho Transitivo Indireto**
   - **Descrição:** Calcula o fecho transitivo indireto de um vértice em um grafo direcionado.
   - **Parâmetro:** ID do vértice.
   - **Saída:** Fecho transitivo indireto.

3. **Caminho Mínimo (Dijkstra)**
   - **Descrição:** Encontra o caminho mínimo entre dois vértices usando o algoritmo de Dijkstra.
   - **Parâmetros:** IDs dos dois vértices.
   - **Saída:** Caminho mínimo.

4. **Caminho Mínimo (Floyd)**
   - **Descrição:** Encontra o caminho mínimo entre dois vértices usando o algoritmo de Floyd-Warshall.
   - **Parâmetros:** IDs dos dois vértices.
   - **Saída:** Caminho mínimo.

5. **Árvore Geradora Mínima (Prim)**
   - **Descrição:** Gera uma Árvore Geradora Mínima para um subconjunto de vértices usando o algoritmo de Prim.
   - **Parâmetro:** Subconjunto de vértices.
   - **Saída:** Árvore Geradora Mínima.

6. **Árvore Geradora Mínima (Kruskal)**
   - **Descrição:** Gera uma Árvore Geradora Mínima para um subconjunto de vértices usando o algoritmo de Kruskal.
   - **Parâmetro:** Subconjunto de vértices.
   - **Saída:** Árvore Geradora Mínima.

7. **Árvore de Caminhamento em Profundidade**
   - **Descrição:** Cria uma árvore de caminhamento em profundidade a partir de um vértice inicial.
   - **Parâmetro:** ID do vértice.
   - **Saída:** Árvore de Caminhamento em Profundidade.

8. **Propriedades do Grafo Ponderado**
   - **Descrição:** Calcula o raio, diâmetro, centro e periferia de um grafo ponderado.
   - **Parâmetro:** O grafo ponderado.
   - **Saída:** Propriedades do grafo.

9. **Vértices de Articulação**
   - **Descrição:** Identifica os vértices de articulação em um grafo não direcionado.
   - **Parâmetro:** O grafo não direcionado.
   - **Saída:** Conjunto de vértices de articulação.

### ⚙️ Acesse as Orientações

Para acessar as orientações detalhadas sobre compilação, execução, testes e exemplos de instâncias, entre na pasta [Parte-01](./Parte-01/).

## ✈️ Parte 2 - Algoritmos de Particionamento de Grafos

Na segunda parte do trabalho, a biblioteca foi estendida para incorporar algoritmos para o problema de particionamento de grafos ponderados por vértices, conhecido como *Minimum Gap Graph Partitioning Problem* (MGGPP). Este problema consiste em particionar um grafo não direcionado em subgrafos conectados, minimizando a diferença de pesos (gap) dentro de cada subgrafo.

1. **Algoritmo Guloso**
   - **Descrição:** Algoritmo que realiza o particionamento do grafo em subgrafos conectados de forma determinística, minimizando o gap de pesos.
   - **Parâmetro:** Número predefinido de subgrafos (p).
   - **Saída:** Partição do grafo e gaps minimizados.

2. **Algoritmo Guloso Randomizado Adaptativo**
   - **Descrição:** Variante do algoritmo guloso, que introduz aleatoriedade na construção da solução para explorar diferentes partições.
   - **Parâmetro:** Número predefinido de subgrafos (p).
   - **Saída:** Partição do grafo e gaps minimizados.

3. **Algoritmo Guloso Randomizado Adaptativo Reativo**
   - **Descrição:** Extensão do algoritmo guloso randomizado adaptativo, onde a aleatoriedade é ajustada dinamicamente com base nos resultados obtidos durante a execução.
   - **Parâmetro:** Número predefinido de subgrafos (p).
   - **Saída:** Partição do grafo e gaps minimizados.

### ⚙️ Acesse as Orientações

ara acessar as orientações detalhadas sobre a implementação dos algoritmos e o relatório com os resultados, entre na pasta [Parte-02](./Parte-02/).

🔗 **Referências**
- Artigo de referência: [Link para o artigo](https://www.sciencedirect.com/science/article/abs/pii/S0305054821000939)
- Instâncias disponíveis em: [Instâncias do problema](https://homes.di.unimi.it/cordone/research/research.html)

## 👥 Integrantes do Grupo
- Breno Montanha Costa
- Lucas Henrique Nogueira
- Pedro Henrique de Souza Rodrigues 

## 📚 Teoria dos Grafos
**Disciplina:** Teoria dos Grafos (DCC059) - UFJF  
**Período:** 2024/1