# Biblioteca de Grafos em C++

## 🎯 Resumo

Este projeto implementa uma biblioteca em C++ para manipulação de grafos simples, tanto direcionados quanto não direcionados, e ponderados ou não ponderados. Utilizando listas de adjacência, a biblioteca oferece uma série de funcionalidades úteis para a análise e manipulação de grafos.

## 🚀 Funcionalidades Implementadas - Parte 1

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

## ⚙️ Orientações

### Compatibilidade
O programa é compatível com os ambientes Linux, Windows e iOS.
### Compilação
O padrão para compilação a ser utilizado o  será `g++ *.c* -o execGrupoX`.

Para compilar o programa, utilize o Makefile incluído no repositório. Execute o seguinte comando:
```sh
make
```
### Execução
Para executar o programa, basta executar o seguinte comando:

#### No Linux e iOS:
```sh
./execGrupoX ./<arquivo_entrada> ./<arquivo_saida> <Op_Direc> <Op_PesoAresta> <Op_PesoNos>
```

#### No Windows:
```sh
.\execGrupoX .\<arquivo_entrada> .\<arquivo_saida> <Op_Direc> <Op_PesoAresta> <Op_PesoNos>
```

#### Parâmetros de Execução
- `<arquivo_entrada>` : Nome do arquivo contendo as informações do grafo a ser processado.

- `<arquivo_saida>` : Nome do arquivo onde será salvo o grafo e as funcionalidades solicitadas após a execução do programa.

- `<Op_Direc>`  : Define se o grafo é direcionado ou não. Use 1 para grafos direcionados e 0 para grafos não direcionados.

- `<Op_PesoAresta>`  : Especifica se as arestas do grafo possuem peso. Use 1 se as arestas são ponderadas e 0 se não são ponderadas.

- `<Op_PesoNos>`  : Indica se os vértices possuem peso associado. Use 1 se os vértices são ponderados e 0 se não são ponderados.

### Testes

Para garantir a funcionalidade correta da biblioteca, foi incluido testes automatizados usando a biblioteca Catch2. Para executá-los:

- Certifique-se de que a biblioteca Catch2 está instalada no seu sistema.

- Compile e execute os testes com o comando:
    ```sh
    make test
    ```

Os testes validarão as funcionalidades implementadas e garantirão que o código está funcionando conforme esperado.

### Exemplo de Arquivo para Compilar ou Fazer os Testes
Os arquivos de exemplo estão localizados na pasta [**instances_example**](instances_example) do repositório. Esses arquivos contêm grafos diferentes que podem ser usados para compilar o programa ou executar os testes. Utilize esses arquivos para garantir que todas as funcionalidades da biblioteca estejam funcionando corretamente.


## 👥 Integrantes do Grupo
- Breno Montanha Costa
- Lucas Henrique Nogueira
- Pedro Henrique de Souza Rodrigues 


## 📚 Teoria dos Grafos
**Disciplina:** Teoria dos Grafos (DCC059) - UFJF  
**Período:** 2024/1 