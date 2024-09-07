## ⚙️ Orientações da Parte 1 - Algoritmos Clássicos de Grafos

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
.\execGrupoX.exe .\<arquivo_entrada> .\<arquivo_saida> <Op_Direc> <Op_PesoAresta> <Op_PesoNos>
```

#### Parâmetros de Execução
- `<arquivo_entrada>` : Nome do arquivo contendo as informações do grafo a ser processado.

- `<arquivo_saida>` : Nome do arquivo onde será salvo o grafo e as funcionalidades solicitadas após a execução do programa.

- `<Op_Direc>`  : Define se o grafo é direcionado ou não. Use 1 para grafos direcionados e 0 para grafos não direcionados.

- `<Op_PesoAresta>`  : Especifica se as arestas do grafo possuem peso. Use 1 se as arestas são ponderadas e 0 se não são ponderadas.

- `<Op_PesoNos>`  : Indica se os vértices possuem peso associado. Use 1 se os vértices são ponderados e 0 se não são ponderados.

### Testes

Para garantir a funcionalidade correta da biblioteca, foi incluido testes automatizados usando a biblioteca GTest. Para executá-los:

- Certifique-se de que a biblioteca Gtest está instalada no seu sistema.

- Compile e execute os testes com o comando:
    ```sh
    make test
    ```

Os testes validarão as funcionalidades implementadas e garantirão que o código está funcionando conforme esperado.

### Exemplo de Arquivo para Compilar ou Fazer os Testes
Os arquivos de exemplo estão localizados na pasta [**instances_example**](./instances_example/) do repositório. Esses arquivos contêm grafos diferentes que podem ser usados para compilar o programa ou executar os testes. Utilize esses arquivos para garantir que todas as funcionalidades da biblioteca estejam funcionando corretamente.