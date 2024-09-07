#include "../include/Graph.hpp"
#include "../include/defines.hpp" 


Graph::Graph(ifstream &instance)
{
    // Inicializa o número de arestas e nós.
    _number_of_edges = 0;
    _number_of_nodes = 0;

    // Inicializa os ponteiros do primeiro e do último nó.
    _first = NULL;
    _last = NULL;

    // Chamando a função para ler o grafo.
    read_graph(instance);
}

Graph::Graph()
{
    // Inicializa o número de arestas e nós.
    _number_of_edges = 0;
    _number_of_nodes = 0;

    // Inicializa os ponteiros do primeiro e do último nó.
    _first = NULL;
    _last = NULL;
}

Graph::~Graph()
{
    // Criando o nó auxiliar para percorrer o grafo.
    Node *aux_node_1 = _first;

    // Percorrendo todos os nós do grafo.
    while (aux_node_1 != NULL)
    {
        // Realizando processo de remoção das arestas.
        Edge *aux_edge_1 = aux_node_1->_first_edge;
        while (aux_edge_1 != NULL)
        {
            Edge *aux_edge_2 = aux_edge_1->_next_edge;
            delete aux_edge_1;
            aux_edge_1 = aux_edge_2;
        }
        Node *aux_node_2 = aux_node_1->_next_node;
        delete aux_node_1;
        aux_node_1 = aux_node_2;
    }
}

void Graph::read_graph(ifstream &instance)
{
    // String para armazenar a linha do arquivo.
    string line;

    // Lendo primeira linha.
    getline(instance, line);
    istringstream iss(line);
    iss >> _number_of_nodes;
    for (size_t i = 1; i <= _number_of_nodes; i++)
        add_node(i, 0);

    // Inicializando leitura do arquivo.
    while (getline(instance, line))
    {
        // Se houver linha vazia durante a leitura.
        if (line.empty())
            continue;

        // Inicializa a leitura da linha.
        istringstream iss(line);

        // Variáveis para armazenar os valores da linha.
        size_t node_1, node_2;
        float node_1_weight = 1.0, node_2_weight = 1.0, edge_weight = 1.0;

        // Realizando a leitura dos valores.


        // Adicionando os nós e as arestas ao grafo.
        add_edge(node_1, node_2);
    }
}

void Graph::remove_node(size_t node_id)
{
    // Encontrando o nó a ser removido.
    Node *aux_node = find_node(node_id);

    // Verificando se o nó foi encontrado.
    if (!aux_node)
        return;

    // Verificando se a remoção do nó deixará o grafo desconexo.
    for (size_t i = 0; i < _number_of_nodes; ++i)
        if (i != node_id && !(conected(node_id, i) || conected(i, node_id)))
            return;

    // Inicializando o vetor de nós conectados.
    size_t *conected_nodes = new size_t[aux_node->_number_of_edges];

    // Armazenando os nós conectados ao nó a ser removido.
    int i = 0;
    for (Edge *aux_edge = aux_node->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
    {
        conected_nodes[i] = aux_edge->_target_id;
        i++;
    }

    // Removendo as arestas do nó a ser removido.
    for (size_t i = 0; i < aux_node->_number_of_edges; i++)
        remove_edge(node_id, conected_nodes[i]);

    // Atualizando a lista de nós.
    aux_node->_next_node = aux_node->_previous_node;
    aux_node->_previous_node = aux_node->_next_node;

    // Atualizando o número de nós.
    _number_of_nodes--;

    // Deletando o nó.
    delete aux_node;
    delete[] conected_nodes;
}

void Graph::remove_edge(size_t node_id_1, size_t node_id_2)
{
    // Encontrando os nós da aresta a ser removida.
    Node *aux_node_1 = find_node(node_id_1);
    Node *aux_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!aux_node_1 || !aux_node_2)
        return;

    // Verificando se a remoção da aresta deixará o grafo desconexo.
    if (!conected(node_id_1, node_id_2) && !conected(node_id_2, node_id_1))
        return;

    // Inicializando as arestas auxiliares.
    Edge *aux_edge_1 = aux_node_1->_first_edge;
    Edge *aux_edge_2 = NULL;

    // Procurando a aresta a ser removida.
    while (aux_edge_1 != NULL)
    {
        // Verificando se a aresta foi encontrada.
        if (aux_edge_1->_target_id == node_id_2)
        {
            // Atualizando a lista de arestas.
            if (aux_edge_2 != NULL)
                aux_edge_2->_next_edge = aux_edge_1->_next_edge;
            else
                aux_node_1->_first_edge = aux_edge_1->_next_edge;

            delete aux_edge_1;
            aux_node_1->_number_of_edges--;
            break;
        }

        // Atualizando as arestas auxiliares.
        aux_edge_2 = aux_edge_1;
        aux_edge_1 = aux_edge_1->_next_edge;
    }
}

void Graph::add_node(size_t node_id, float weight)
{
    // Verificando se o nó já existe.
    if (find_node(node_id) != NULL)
        return;

    // Criando um novo nó.
    Node *aux = new Node;
    aux->_number_of_edges = 0;
    aux->_id = node_id;
    aux->_weight = weight;
    aux->_next_node = NULL;
    aux->_first_edge = NULL;

    // Verificando se o grafo está vazio.
    if (_last == NULL)
    {
        _first = aux;
        _last = aux;
    }

    // Caso contrário.
    else
    {
        _last->_next_node = aux;
        aux->_previous_node = _last;
        _last = aux;
    }
}

void Graph::add_edge(size_t node_id_1, size_t node_id_2)
{
    // Procurando se os nós já existem.
    Node *search_node_1 = find_node(node_id_1);
    Node *search_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!search_node_1 || !search_node_2)
        return;

    // Criando uma nova aresta.
    Edge *new_edge_1 = new Edge;
    new_edge_1->_target_id = node_id_2;
    new_edge_1->_next_edge = NULL;

    // Atualizando o número de arestas.
    search_node_1->_number_of_edges = search_node_1->_number_of_edges + 1;

    // Verificando se o nó possui arestas.
    if (search_node_1->_first_edge != NULL)
    {
        // Adicionando a aresta ao nó.
        Edge *aux_edge = search_node_1->_first_edge;
        for (; aux_edge->_next_edge != NULL; aux_edge = aux_edge->_next_edge)
            ;
        aux_edge->_next_edge = new_edge_1;
    }

    // Caso o nó não possua arestas.
    else
        search_node_1->_first_edge = new_edge_1;

    // Criando uma nova aresta.
    Edge *new_edge_2 = new Edge;
    new_edge_2->_target_id = node_id_1;
    new_edge_2->_next_edge = NULL;
    // Atualizando o número de arestas.
    search_node_2->_number_of_edges = search_node_2->_number_of_edges + 1;
    // Verificando se o nó possui arestas.
    if (search_node_2->_first_edge != NULL)
    {
        // Adicionando a aresta ao nó.
        Edge *aux_edge = search_node_2->_first_edge;
        for (; aux_edge->_next_edge != NULL; aux_edge = aux_edge->_next_edge)
            ;
            aux_edge->_next_edge = new_edge_2;
    }
    // Caso o nó não possua arestas.
    else
        search_node_2->_first_edge = new_edge_2;
    

    // Atualizando o número de arestas.
    _number_of_edges = _number_of_edges + 1;
}

void Graph::print_graph()
{
    // Implementação da função de impressão do grafo no menu.

    int i = 0;

    while (i != -1)
    {
        system("clear||cls");
        cout << "\n\t\t\t Grafo\n\n\n";

        cout << "  Dados do Grafo:" << endl;
        cout << "  Número de Nós: " << _number_of_nodes << endl;
        cout << "  Número de Arestas: " << _number_of_edges << endl;
        cout << "  Tipo do Grafo: Direcionado\n\n\n";

        cout << "\n\n";

        // Imprimindo o grafo.
        for (Node *node = _first; node != NULL; node = node->_next_node)
        {
            cout << "\t\t\t" << node->_id;
            for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
                cout << " -> " << edge->_target_id;
            cout << endl;
        }

        cout << "\n\n  Digite -1 para voltar ao menu: ";
        cin >> i;
    }
}

void Graph::print_graph(ofstream &output_file)
{
    // Armazena dados do grafo no buffer.
    output_file << "\n\t\t\t\tImprimindo Grafo\n\n\n";

    output_file << "  Dados do Grafo:" << endl;
    output_file << "  Número de Nós: " << _number_of_nodes << endl;
    output_file << "  Número de Arestas: " << _number_of_edges << endl;
    output_file << "  Tipo do Grafo: Direcionado\n\n\n";

    // Verifica se o grafo está vazio.
    if (_first == NULL)
    {
        output_file << "  O grafo está vazio." << endl;
        return;
    }

    // Itera sobre todos os nós do grafo
    for (Node *node = _first; node != NULL; node = node->_next_node)
    {
        // Imprime o nó atual
        output_file << "\t\t  " << node->_id;

        // Verifica se há arestas saindo do nó
        bool first_edge = true;
        for (Edge *edge = node->_first_edge; edge != NULL; edge = edge->_next_edge)
        {
            // Se não for a primeira aresta, adiciona a conexão
            if (first_edge)
            {
                output_file << " -> " << edge->_target_id;
                first_edge = false;
            }
            else
            {
                output_file << " -> " << edge->_target_id;
            }
        }
        // Quebra de linha após processar todas as arestas do nó atual
        output_file << endl;
    }

    output_file << "\n\n";
}

int Graph::conected(size_t node_id_1, size_t node_id_2)
{
    // Encontrando os nós da aresta a ser encontrada.
    Node *aux_node_1 = find_node(node_id_1);
    Node *aux_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!aux_node_1 || !aux_node_2)
        return 0;

    // Verificando se a aresta existe.
    for (Edge *aux_edge = aux_node_1->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        if (aux_edge->_target_id == node_id_2)
            return 1;

    // Caso a aresta não exista.
    return 0;
}

Node *Graph::find_node(size_t node_id)
{
    // Procurando o nó.
    for (Node *aux_node = _first; aux_node != NULL; aux_node = aux_node->_next_node)
        if (aux_node->_id == node_id)
            return aux_node;

    // Caso o nó não seja encontrado.
    return NULL;
}

size_t Graph::get_num_nodes()
{
    // Retornando o número de nós.
    return _number_of_nodes;
}

Edge *Graph::find_edge(size_t node_id_1, size_t node_id_2)
{
    // Encontrando os nós da aresta a ser encontrada.
    Node *aux_node_1 = find_node(node_id_1);
    Node *aux_node_2 = find_node(node_id_2);

    // Verificando se os nós foram encontrados.
    if (!aux_node_1 || !aux_node_2)
        return NULL;

    // Verificando se a aresta existe.
    for (Edge *aux_edge = aux_node_1->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        if (aux_edge->_target_id == node_id_2)
            return aux_edge;

    // Caso a aresta não exista.
    return NULL;
}

size_t Graph::get_num_edges()
{
    // Retornando o número de arestas.
    return _number_of_edges;
}
