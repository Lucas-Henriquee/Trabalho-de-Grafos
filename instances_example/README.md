# 🗂️ Instâncias de Exemplo 

As instâncias de exemplo para a biblioteca de grafos estão organizadas em dois tipos de grafos: direcionados e não direcionados. Cada arquivo de instância segue um padrão de nomenclatura e formato para facilitar a utilização.

## Padrão de Nomenclatura 

Os arquivos de instância são nomeados de acordo com o padrão:

- `D` indica que o grafo é direcionado.
- `U` indica que o grafo é não direcionado.

Por exemplo:
- `10nD.dat` para um grafo direcionado com 10 nós.
- `15nU.dat` para um grafo não direcionado com 15 nós.

## Formato do Arquivo 

Cada arquivo de instância segue o formato abaixo:

1. **Primeira Linha**: Contém o tamanho da instância, que é o número total de nós no grafo.
2. **Linhas Subsequentemente**: Cada linha representa uma aresta do grafo no formato:

<p align="center">
5<br>
1 - 2 - 10<br>
2 - 3 - 5<br>
3 - 4 - 2<br>
4 - 5 - 7<br>
5 - 1 - 3
</p>

- **Primeira Linha**: `5`, indicando que o grafo tem 5 nós.
- **Linhas Subsequentemente**:
  - `1 - 2 - 10`: Uma aresta do nó 1 para o nó 2 com peso 10.
  - `2 - 3 - 5`: Uma aresta do nó 2 para o nó 3 com peso 5.
  - `3 - 4 - 2`: Uma aresta do nó 3 para o nó 4 com peso 2.
  - `4 - 5 - 7`: Uma aresta do nó 4 para o nó 5 com peso 7.
  - `5 - 1 - 3`: Uma aresta do nó 5 para o nó 1 com peso 3.


# 🔧 Testes Automatizados 

Os arquivos de instância são utilizados automaticamente para configurar e executar os testes da biblioteca. Isso garante que todas as funcionalidades da biblioteca sejam validadas de forma consistente.
