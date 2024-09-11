## 🗂️ Instâncias de Exemplo

O conjunto de benchmark consiste em 225 instâncias do problema Minimum Gap Graph Partitioning Problem (MGGPP). As instâncias estão organizadas conforme as características descritas abaixo, e os arquivos seguem um formato padronizado. Para obter os resultados e produzir o relatório final, foram selecionadas apenas 19 instâncias de exemplo entre as 225 disponíveis.

### Padrão de Nomenclatura

Os arquivos de instância seguem o padrão de nomenclatura abaixo, indicando as propriedades de cada instância:

- **Número de vértices**: Representado por "n", seguido pelo número de vértices (n = 100, 200, 300, 400, 500).
- **Densidade do grafo**:
  - `"pla"` para instâncias planares.
  - `"d03"` para instâncias esparsas (grafos aleatórios com `m = (n(n-1))/3` arestas).
  - `"d06"` para instâncias densas (grafos aleatórios com `m = 2n(n-1)/3` arestas).
- **Parâmetro `p`**: Define o número de subgrafos.
  - `"p1"` para `p = round(ln(n))`.
  - `"p2"` para `p = round(n)`.
  - `"p3"` para `p = round(n / ln(n))`.
- **Índice**: `"i"` seguido por um índice `i` (1, 2, 3, 4, 5) para distinguir entre diferentes instâncias da mesma classe.

### Exemplo de Nomenclatura

- `100pla_p1_i1.dat`: Instância planar com 100 vértices, `p = round(ln(100))`, primeira instância dessa classe.
- `200d03_p2_i3.dat`: Grafo esparso com 200 vértices, `p = round(200)`, terceira instância dessa classe.

### Formato do Arquivo

Os arquivos estão no formato MathProg (AMPL) e possuem a seguinte estrutura:

- **p**: Número de subgrafos.
- **V**: Conjunto de vértices.
- **w**: Vetor de pesos dos vértices, organizado de forma que os pesos estejam em ordem crescente.
- **E**: Conjunto de arestas.