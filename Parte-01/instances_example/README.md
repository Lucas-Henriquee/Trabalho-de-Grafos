# 🗂️ Instâncias de Exemplo 

As instâncias de exemplo para a biblioteca de grafos estão organizadas em dois tipos de grafos: direcionados e não direcionados. Cada arquivo de instância segue um padrão de nomenclatura e formato para facilitar a utilização.

## Padrão de Nomenclatura 

Os arquivos de instância são nomeados de acordo com o padrão:

- `D` indica que o grafo é direcionado.
- `U` indica que o grafo é não direcionado.
- `_n` indica que o grafo contém arestas negativas.

Por exemplo:
- `10nD.dat` para um grafo direcionado com 10 nós e arestas não-negativas.
- `15nU.dat` para um grafo não direcionado com 15 nós e arestas não-negativas.
- `10nD_n.dat` para um grafo direcionado com 10 nós e arestas negativas.
- `15nU_n.dat` para um grafo não direcionado com 15 nós e arestas negativas.

## Formato do Arquivo 

Cada arquivo de instância segue o formato abaixo:

1. **Primeira Linha**: Contém o tamanho da instância, que é o número total de nós no grafo.
2. **Linhas Subsequentemente**: Cada linha representa uma aresta do grafo no formato:

<p align="center">
5<br>
1 - 2 -  10 <br>
2 - 3 - -5 <br>
3 - 4 -  12 <br>
4 - 5 -  11 <br>
5 - 1 - -3
</p>

- **Primeira Linha**: `5`, indicando que o grafo tem 5 nós.
- **Linhas Subsequentemente**:
  - `1 - 2 - 10`: Uma aresta do nó 1 para o nó 2 com peso 10.
  - `2 - 3 - -5`: Uma aresta do nó 2 para o nó 3 com peso -5.
  - `3 - 4 - 12`: Uma aresta do nó 3 para o nó 4 com peso 12.
  - `4 - 5 - 11`: Uma aresta do nó 4 para o nó 5 com peso 11.
  - `5 - 1 - -3`: Uma aresta do nó 5 para o nó 1 com peso -3.


# 🔧 Testes Automatizados 

Os arquivos de instância são utilizados automaticamente para configurar e executar os testes da biblioteca. Isso garante que todas as funcionalidades da biblioteca sejam validadas de forma consistente.