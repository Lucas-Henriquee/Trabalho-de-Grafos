## ⚙️ Orientações da Parte 2 - Algoritmos de Particionamento de Grafos

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
./execGrupoX ./<arquivo_entrada> ./<arquivo_saida> <algoritmo>
```

#### No Windows:
```sh
.\execGrupoX.exe .\<arquivo_entrada> .\<arquivo_saida> <algoritmo>
```

### Parâmetros de Execução

- `<arquivo_entrada>`: Nome do arquivo contendo as informações do grafo a ser processado.
- `<arquivo_saida>`: Nome do arquivo onde será salvo o resultado da execução.
- `<algoritmo>`: Número que indica o algoritmo a ser utilizado:
  - `0`: Algoritmo Guloso
  - `1`: Algoritmo Guloso Randomizado Adaptativo
  - `2`: Algoritmo Guloso Randomizado Adaptativo Reativo

## Relatório de Resultados

O programa gera um arquivo de saída contendo os resultados do particionamento, incluindo os gaps calculados para cada subgrafo. Esses resultados foram utilizados para a análise do *Minimum Gap Graph Partitioning Problem (MGGPP)* e a criação do [Relatório Final]().