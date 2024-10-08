## ⚙️ Orientações da Parte 2 - Algoritmos de Particionamento de Grafos

### Compatibilidade
O programa é compatível com os ambientes Linux, Windows(wsl) e iOS.
### Compilação
O padrão para compilação a ser utilizado o  será `g++ *.c* -o execGrupoX`.

Para compilar o programa, utilize o Makefile incluído no repositório. Execute o seguinte comando:
```sh
make
```
### Execução
Para executar o programa, basta executar o seguinte comando:

#### No Linux, iOS e Windows(wsl):
```sh
./execGrupoX ./<arquivo_entrada> ./<arquivo_saida> <algoritmo>
```

#### Parâmetros de Execução

- `<arquivo_entrada>`: Nome do arquivo contendo as informações do grafo a ser processado.
- `<arquivo_saida>`: Nome do arquivo onde será salvo o resultado da execução.
- `<algoritmo>`: Número que indica o algoritmo a ser utilizado:
  - `0`: Algoritmo Guloso
  - `1`: Algoritmo Guloso Randomizado Adaptativo
  - `2`: Algoritmo Guloso Randomizado Adaptativo Reativo

### Execução de Todas as Instâncias
Para executar automaticamente todas as instâncias, basta executar o seguinte comando:

#### No Linux, iOS e Windows(wsl):
```sh
./execAll.sh
```

#### Observações Importantes

- **Compilação Prévia:** Antes de executar o script `execAll.sh`, certifique-se de que o programa foi compilado com o comando `make`. 

- **Ambiente Windows (WSL)**: No WSL, os arquivos de instância precisam estar no formato Unix (LF). Antes de executar o script, converta os arquivos de instância utilizando o dos2unix:
```sh
dos2unix execAll.sh
```
Caso o dos2unix não esteja instalado, instale-o manualmente.


### Relatório de Resultados

O programa gera um arquivo de saída contendo os resultados do particionamento, incluindo os gaps calculados para cada subgrafo. Esses resultados foram utilizados para a análise do *Minimum Gap Graph Partitioning Problem (MGGPP)* e a criação do [Relatório Final](./Relatorio_Final.pdf).
 
### Exemplo de Arquivo para Compilar
Os arquivos de exemplo estão localizados na pasta [**instances_example**](./instances_example/) do repositório. Esses arquivos contêm grafos que foram selecionados para análise e elaboração do relatório final. Eles podem ser utilizados para referência quanto à estrutura dos dados.