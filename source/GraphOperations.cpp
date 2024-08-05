#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

ostringstream output_buffer;

void menu(Graph *g, string file_exit)
{

    // Variável para a escolha do menu
    int i = -1;

    // Variáveis para armazenar o tamanho, vértices de origem e destino.
    size_t size, vertex_1, vertex_2;

    // Loop do menu
    do
    {
        system("clear||cls");

        cout << "\n\t  Menu de Operações do Grafo\n\n\n";
        cout << "  1) Fecho Transitivo Direto de um Vértice" << endl;
        cout << "  2) Fecho Transitivo Indireto de um Vértice" << endl;
        cout << "  3) Caminho Mínimo entre Dois Vértices (Dijkstra)" << endl;
        cout << "  4) Caminho Mínimo entre Dois Vértices (Floyd)" << endl;
        cout << "  5) Árvore Geradora Mínima (Prim)" << endl;
        cout << "  6) Árvore Geradora Mínima (Kruskal)" << endl;
        cout << "  7) Caminhamento em Profundidade" << endl;
        cout << "  8) Propriedades do Grafo" << endl;
        cout << "  9) Vértices de Articulação" << endl;
        cout << "  0) Sair do Programa" << endl;
        cout << "\n\n  Escolha uma opção: ";

        cin >> i;

        system("clear||cls");

        // Chamando a função para validar a operação no grafo.
        if (!validate_graph(g, i))
            continue;

        // Switch case para as opções do menu
        switch (i)
        {
        case 1:
        {
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            transitive_direct(g, vertex_1);
            break;
        }
        case 2:
        {
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            transitive_indirect(g, vertex_1);
            break;
        }
        case 3:
        {
            cout << "\n  Digite os IDs dos vértices (origem destino): ";
            cin >> vertex_1 >> vertex_2;
            dijkstra_shortest_path(g, vertex_1, vertex_2);
            break;
        }
        case 4:
        {
            cout << "\n  Digite os IDs dos vértices (origem destino): ";
            cin >> vertex_1 >> vertex_2;
            floyd_shortest_path(g, vertex_1, vertex_2);
            break;
        }
        case 5:
        {
            cout << "\n  Digite o número de vértices no subconjunto: ";
            cin >> size;
            size_t *vertices = new size_t[size];
            cout << "\n  Digite os IDs dos vértices: ";
            for (size_t i = 0; i < size; ++i)
                cin >> vertices[i];
            // prim_minimum_generating_tree(g, vertices, size);
            delete[] vertices;
            break;
        }
        case 6:
        {
            cout << "\n  Digite o número de vértices no subconjunto: ";
            cin >> size;
            size_t *vertices = new size_t[size];
            cout << "\n  Digite os IDs dos vértices: ";
            for (size_t i = 0; i < size; ++i)
                cin >> vertices[i];
            // kruskal_minimum_generating_tree(g, vertices, size);
            delete[] vertices;
            break;
        }
        case 7:
        {
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            deep_walking(g, vertex_1);
            break;
        }
        case 8:
        {
            properties_graph(g);
            break;
        }
        case 9:
        {
            // articulation_vertices(g);
            break;
        }
        case 0:
        {
            cout << "\n  Encerrando o programa..." << endl;
            break;
        }
        default:
        {
            cout << "\n  Opção inválida! Tente novamente." << endl;
            sleep_for_seconds(2);
        }
        }

        output_buffer << "\n  -------------------------------------------------------------\n\n";
        cout << output_buffer.str();
        sleep_for_seconds(1);

        // Salvando a saída no arquivo e limpando o buffer.
        if (i != 0)
        {
            cout << "\n\n  Deseja salvar esses dados em um arquivo? (s/n): ";
            char option;
            cin >> option;
            if (option == 's')
                save_exit(g, file_exit);
            output_buffer.str("");
            output_buffer.clear();
        }

    } while (i != 0);

    return;
}

bool validate_graph(Graph *g, int i)
{
    // Verificando se o grafo é direcionado antes de realizar a operação de fecho transitivo.
    if ((i == 1 || i == 2) && !g->get_directed())
    {
        cout << "\n  ATENÇÃO! O grafo solicitado não é direcionado, portanto, a operação não pode ser realizada. Por favor, selecione outra opção no menu." << endl;
        sleep_for_seconds(5);
        return false;
    }

    // Verificando se o grafo possui pesos nos vértices antes de realizar a operação de caminho mínimo.
    if ((i == 8) && !g->get_weighted_edges())
    {
        cout << "\n  ATENÇÃO! O grafo solicitado não possui pesos nos vértices, portanto, a operação não pode ser realizada. Por favor, selecione outra opção no menu." << endl;
        sleep_for_seconds(5);
        return false;
    }

    // Verificando se o grafo é não direcionado antes de realizar a operação dos vérticies articulados.
    if ((i == 9) && g->get_directed())
    {
        cout << "\n  ATENÇÃO! O grafo solicitado é direcionado, portanto, a operação não pode ser realizada. Por favor, selecione outra opção no menu." << endl;
        sleep_for_seconds(5);
        return false;
    }

    return true;
}

void transitive_direct(Graph *g, size_t vertex)
{
    // Criando o vetor de nós visitados.
    vector<bool> visited(g->get_num_nodes() + 1, false);

    // Chamando a função dfs (Busca em Profundidade).
    g->dfs_transitive(vertex, visited, true);

    // Armazenando no buffer os IDs dos nós visitados.
    output_buffer << "  Fecho Transitivo Direto para o vértice " << vertex << ": ";

    for (size_t v = 0; v < visited.size(); v++)
        if (visited[v])
            output_buffer << v << " ";

    // Concluindo a escrita no buffer e exibindo no terminal ao usuário.
    output_buffer << "\n";
}

void transitive_indirect(Graph *g, size_t vertex)
{
    // Criando o vetor de nós visitados.
    vector<bool> visited(g->get_num_nodes() + 1, false);

    // Chamando a função dfs (Busca em Profundidade).
    g->dfs_transitive(vertex, visited, false);

    // Armazenando no buffer os IDs dos nós visitados.
    output_buffer << "  Fecho Transitivo Indireto para o vértice " << vertex << ": ";

    for (int v = visited.size() - 1; v >= 0; v--)
        if (visited[v])
            output_buffer << v << " ";

    // Concluindo a escrita no buffer e exibindo no terminal ao usuário.
    output_buffer << "\n";
}

void dijkstra_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2)
{
    // TODO: Verificar se os vertices fazem parte do grafo Dijkstra
    // Criando o vetor de distâncias.
    vector<float> distance(g->get_num_nodes());

    // Criando o vetor de pais.
    vector<int> parents(g->get_num_nodes(), -1);

    // Criando o vetor para mapear a posição do nó.
    vector<size_t> node_at_index(g->get_num_nodes());

    // Criando o vetor para armazenar o caminho.
    vector<size_t> path;

    // Chamando a função dijkstra.
    g->dijkstra(vertex_1, distance, parents, node_at_index);

    // Construíndo o caminho mínimo de vertex_1 para vertex_2.
    for (int v = find(node_at_index.begin(), node_at_index.end(), vertex_2) - node_at_index.begin(); v != 0; v = parents[v])
        path.push_back(v);

    // Adicionando o vértice de origem.
    path.push_back(0);

    reverse(path.begin(), path.end());

    // Escrevendo no buffer o caminho mínimo.
    output_buffer << "  Caminho Mínimo (Dijkstra) entre " << vertex_1 << " e " << vertex_2 << ": ";

    for (size_t i = 0; i < path.size(); i++)
    {
        output_buffer << node_at_index[path[i]];
        if (i != path.size() - 1)
            output_buffer << " -> ";
    }

    // Concluindo a escrita no buffer e exibindo no terminal ao usuário.
    output_buffer << "\n";
}

void floyd_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2)
{
    // TODO: Verificar se os vertices fazem parte do grafo Dijkstra
    size_t n = g->get_num_nodes();
    vector<vector<float>> distance(n, vector<float>(n));
    vector<vector<int>> parents(n, vector<int>(n));
    vector<size_t> node_at_index(n);
    vector<size_t> path;

    g->floyd(distance, parents, node_at_index);

    size_t p_v1 = find(node_at_index.begin(), node_at_index.end(), vertex_1) - node_at_index.begin();
    size_t p_v2 = find(node_at_index.begin(), node_at_index.end(), vertex_2) - node_at_index.begin();

    for (p_v2; p_v2 != p_v1; p_v2 = parents[p_v1][p_v2])
    {
        path.insert(path.begin(), node_at_index[p_v2]);
    }
    path.insert(path.begin(), vertex_1);

    output_buffer << "  Caminho Mínimo (Floyd) entre " << vertex_1 << " e " << vertex_2 << ": ";

    for (size_t i = 0; i < path.size(); i++)
    {
        output_buffer << path[i];
        if (i != path.size() - 1)
            output_buffer << " -> ";
    }
}

void prim_minimum_generating_tree(Graph *g, size_t *vertices, size_t size)
{
    // TODO: Implementação

    output_buffer << "  Árvore Geradora Mínima (Prim) para os vértices: ";
    for (size_t i = 0; i < size; ++i)
        output_buffer << vertices[i] << " ";

    output_buffer << "\n";
}

void kruskal_minimum_generating_tree(Graph *g, size_t *vertices, size_t size)
{
    // TODO: Implementação

    output_buffer << "  Árvore Geradora Mínima (Kruskal) para os vértices: ";
    for (size_t i = 0; i < size; ++i)
        output_buffer << vertices[i] << " ";

    output_buffer << "\n";
}

void deep_walking(Graph *g, size_t vertex)
{

    // Vetor para armazenar as arestas de retorno.
    vector<pair<size_t, size_t>> return_edges;

    // Mapa para armazenar a lista de adjacência.
    map<size_t, vector<size_t>> adj_list;

    // Encontrando o nó de início.
    if (g->dfs_call(vertex, return_edges, adj_list))
    {
        // Escrevendo no buffer o caminhamento em profundidade.
        output_buffer << "  Caminhamento em Profundidade a partir do vértice " << vertex << ":" << endl;
        output_buffer << "\n  Lista de Adjacência:" << endl;

        for (auto &entry : adj_list)
        {
            output_buffer << "  " << entry.first << " -> ";

            for (size_t i = 0; i < entry.second.size(); ++i)
            {
                if (i > 0)
                    output_buffer << " -> ";

                output_buffer << entry.second[i];
            }

            output_buffer << endl;
        }

        // Escrevendo as arestas de retorno no buffer.
        output_buffer << "\n  Arestas de retorno:" << endl;
        for (size_t i = 0; i < return_edges.size(); ++i)
            output_buffer << "  (" << return_edges[i].first << ", " << return_edges[i].second << ")" << endl;
        output_buffer << endl;
    }

    // Caso contrário.
    else
        output_buffer << "  Nó não encontrado no grafo." << endl;
}

void properties_graph(Graph *g)
{
    // Variáveis para armazenar o raio e o diâmetro.
    float radius;
    float diameter;

    // Vetores para armazenar o centro e a periferia.
    vector<size_t> center;
    vector<size_t> periphery;

    // Chamando a função que calcula as propriedades do grafo.
    g->compute_graph_properties(radius, diameter, center, periphery);

    // Escrevendo as propriedades no buffer.
    output_buffer << "  Propriedades do Grafo:\n\n";
    output_buffer << "  Raio (Valor): " << radius << endl;
    output_buffer << "  Diâmetro (Valor): " << diameter << endl;

    // Escrevendo o centro e a periferia no buffer.
    output_buffer << "  Centro (Nó):  ";
    for (size_t v : center)
        output_buffer << v << " ";
    output_buffer << endl;

    output_buffer << "  Periferia (Nó): ";
    for (size_t v : periphery)
        output_buffer << v << " ";
    output_buffer << endl;
}

void articulation_vertices(Graph *g)
{
    // TODO: Implementação
}

void save_exit(Graph *g, string file_exit)
{
    // Verificando se o arquivo de saída existe.
    ifstream check_file(file_exit);
    bool file_exists = check_file.good();

    // Abrindo o arquivo de saída.
    ofstream output_file(file_exit, ios::out | ios::app);

    // Verificando se o arquivo foi aberto.
    if (output_file.is_open())
    {

        // Caso o arquivo não exista, escrevendo o grafo no arquivo.
        if (!file_exists)
            g->print_graph(output_file);

        // Escrevendo a saída no arquivo.
        output_file << output_buffer.str();

        cout << "  Saída salva no arquivo: " << file_exit << endl;
        sleep_for_seconds(3);

        // Fechando o arquivo.
        output_file.close();
    }

    // Caso contrário.
    else
        cout << "  Erro ao abrir o arquivo para salvar a saída." << endl;
}

void sleep_for_seconds(int seconds)
{
#ifdef _WIN32
    Sleep(seconds * 1000); // Sleep no Windows espera em milissegundos
#else
    sleep(seconds); // sleep no Unix espera em segundos
#endif
}