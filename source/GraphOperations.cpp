#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

ostringstream output_buffer;

void menu(Graph *g, string file_exit)
{

    // Variável para a escolha do menu.
    int i = -2;

    // Variáveis para armazenar o tamanho, vértices de origem e destino.
    size_t size, vertex_1, vertex_2;

    // Loop do menu.
    do
    {
        system("clear||cls");

        cout << "\n\t  Menu de Operações do Grafo\n\n\n";
        cout << "  01) Fecho Transitivo Direto de um Vértice" << endl;
        cout << "  02) Fecho Transitivo Indireto de um Vértice" << endl;
        cout << "  03) Caminho Mínimo entre Dois Vértices (Dijkstra)" << endl;
        cout << "  04) Caminho Mínimo entre Dois Vértices (Floyd)" << endl;
        cout << "  05) Árvore Geradora Mínima (Prim)" << endl;
        cout << "  06) Árvore Geradora Mínima (Kruskal)" << endl;
        cout << "  07) Caminhamento em Profundidade" << endl;
        cout << "  08) Propriedades do Grafo" << endl;
        cout << "  09) Vértices de Articulação" << endl;
        cout << "  10) Mostrar Grafo" << endl;
        cout << "  -1) Sair do Programa" << endl;
        cout << "\n\n  Escolha uma opção: ";

        cin >> i;

        system("clear||cls");

        // Chamando a função para validar a operação no grafo.
        if (!validate_graph(g, i))
            continue;

        // Switch case para as opções do menu.
        switch (i)
        {
        case 1: // Fecho Transitivo Direto.
        {
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            transitive_direct(g, vertex_1);
            break;
        }
        case 2: // Fecho Transitivo Indireto.
        {
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            transitive_indirect(g, vertex_1);
            break;
        }
        case 3: // Caminho Mínimo (Dijkstra).
        {
            cout << "\n  Digite os IDs dos vértices (origem destino): ";
            cin >> vertex_1 >> vertex_2;
            dijkstra_shortest_path(g, vertex_1, vertex_2);
            break;
        }
        case 4: // Caminho Mínimo (Floyd).
        {
            cout << "\n  Digite os IDs dos vértices (origem destino): ";
            cin >> vertex_1 >> vertex_2;
            floyd_shortest_path(g, vertex_1, vertex_2);
            break;
        }
        case 5: // Árvore Geradora Mínima (Prim).
        {
            cout << "\n  Digite o número de vértices no subconjunto: ";
            cin >> size;
            if(size == 0)
            {
                cout << "  O subconjunto de vértices não pode ser vazio." << endl;
                sleep_for_seconds(2, false);
                break;
            }
            size_t *sub_vertices = new size_t[size];
            cout << "\n  Digite os IDs dos vértices: ";
            for (size_t j = 0; j < size; ++j)
                cin >> sub_vertices[j];
            prim_minimum_generating_tree(g, sub_vertices, size);
            delete[] sub_vertices;
            break;
        }
        case 6: // Árvore Geradora Mínima (Kruskal).
        {
            cout << "\n  Digite o número de vértices no subconjunto: ";
            cin >> size;
            if(size == 0)
            {
                cout << "  O subconjunto de vértices não pode ser vazio." << endl;
                sleep_for_seconds(2, false);
                break;
            }
            size_t *sub_vertices = new size_t[size];
            cout << "\n  Digite os IDs dos vértices: ";
            for (size_t j = 0; j < size; ++j)
                cin >> sub_vertices[j];
            kruskal_minimum_generating_tree(g, sub_vertices, size);
            delete[] sub_vertices;
            break;
        }
        case 7: // Caminhamento em Profundidade.
        {
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            deep_walking(g, vertex_1);
            break;
        }
        case 8: // Propriedades do Grafo.
        {
            properties_graph(g);
            break;
        }
        case 9: // Vértices de Articulação.
        {
            articulation_vertices(g);
            break;
        }
        case 10: // Mostrar Grafo.
        {
            g->print_graph();
            break;
        }
        case -1: // Sair do Programa.
        {
            cout << "\n  Encerrando o programa..." << endl;
            break;
        }
        default: // Opção inválida.
        {
            cout << "\n  Opção inválida! Tente novamente." << endl;
            sleep_for_seconds(2, false);
        }
        }

        output_buffer << "\n  -------------------------------------------------------------\n\n";
        cout << output_buffer.str();
        sleep_for_seconds(1, false);

        // Salvando a saída no arquivo.
        if ((i >= 1 && i <= 10) && i != 10)
        {
            cout << "\n\n  Deseja salvar esses dados em um arquivo? (s/n): ";
            char option;
            cin >> option;
            if (option == 's')
                save_exit(g, file_exit);
        }

        // Limpando o buffer.
        output_buffer.str("");
        output_buffer.clear();

    } while (i != -1);

    return;
}

bool validate_graph(Graph *g, int i)
{
    // Verificando se o grafo é direcionado antes de realizar a operação de fecho transitivo.
    if ((i == 1 || i == 2) && !g->get_directed())
    {
        cout << "\n  ATENÇÃO! O grafo solicitado não é direcionado, portanto, a operação não pode ser realizada. Por favor, selecione outra opção no menu." << endl;
        sleep_for_seconds(5, false);
        return false;
    }

    // Verificando se o grafo possui pesos nas arestas e se ele é conexo antes de realizar a operação de propriedades do grafo.
    if (i == 8)
    {
        if (!g->get_weighted_edges())
        {
            cout << "\n  ATENÇÃO! O grafo solicitado não possui pesos nas arestas, portanto, a operação não pode ser realizada. Por favor, selecione outra opção no menu." << endl;
            sleep_for_seconds(5, false);
            return false;
        }

        if (!g->is_connected_graph())
        {
            cout << "\n  ATENÇÃO! O grafo solicitado não é conexo, portanto, a operação não pode ser realizada. Por favor, selecione outra opção no menu." << endl;
            sleep_for_seconds(5, false);
            return false;
        }
    }

    // Verificando se o grafo é não direcionado antes de realizar a operação dos vérticies articulados.
    if ((i == 9) && g->get_directed())
    {
        cout << "\n  ATENÇÃO! O grafo solicitado é direcionado, portanto, a operação não pode ser realizada. Por favor, selecione outra opção no menu." << endl;
        sleep_for_seconds(5, false);
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
    // Verificando se os vértices fazem parte do grafo.
    if (g->find_node(vertex_1) == NULL || g->find_node(vertex_2) == NULL)
    {
        output_buffer << "  Um ou mais vértices não fazem parte do grafo." << endl;
        return;
    }

    // Criando o vetor de distâncias.
    vector<float> distance(g->get_num_nodes());

    // Criando o vetor de pais.
    vector<int> parents(g->get_num_nodes(), -1);

    // Criando o vetor para mapear a posição do nó.
    vector<size_t> node_at_index(g->get_num_nodes(), 0);

    // Criando o vetor para armazenar o caminho.
    vector<size_t> path;

    // Chamando a função dijkstra.
    g->dijkstra(vertex_1, distance, parents, node_at_index);

    // Caso o grafo nao tenha ciclos negativos.
    if (find(node_at_index.begin(), node_at_index.end(), vertex_1) != node_at_index.end())
    {
        // Verificando se há conexão entre os vértices.
        if (find(node_at_index.begin(), node_at_index.end(), vertex_2) == node_at_index.end())
        {
            output_buffer << "  Não há conexão entre os vértices " << vertex_1 << " e " << vertex_2 << "." << endl;
            return;
        }

        // Construíndo o caminho mínimo de vertex_1 para vertex_2.
        for (int v = find(node_at_index.begin(), node_at_index.end(), vertex_2) - node_at_index.begin(); v != 0; v = parents[v])
            path.push_back(v);

        // Adicionando o vértice de origem.
        path.push_back(0);

        // Invertendo o vetor de caminho.
        reverse(path.begin(), path.end());

        // Escrevendo no buffer o caminho mínimo.
        output_buffer << "  Caminho Mínimo (Dijkstra) entre " << vertex_1 << " e " << vertex_2 << ": ";

        for (size_t i = 0; i < path.size(); i++)
        {
            output_buffer << node_at_index[path[i]];
            if (i != path.size() - 1)
                output_buffer << " -> ";
        }

        // Escrevendo a distância no buffer.
        output_buffer << "\n  Distância: " << distance[find(node_at_index.begin(), node_at_index.end(), vertex_2) - node_at_index.begin()] << endl;
    }

    // Caso contrário, o grafo possui ciclos negativos.
    else
        return;
}

void floyd_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2)
{
    // Verificando se os vértices fazem parte do grafo.
    if (g->find_node(vertex_1) == NULL || g->find_node(vertex_2) == NULL)
    {
        cout << "  Um ou mais vértices não fazem parte do grafo." << endl;
        return;
    }

    // Armazenando o número de nós.
    size_t n = g->get_num_nodes();

    // Criando a matriz de distâncias.
    vector<vector<float>> distance(n, vector<float>(n));

    // Criando a matriz de pais.
    vector<vector<int>> parents(n, vector<int>(n));

    // Criando o vetor para mapear a posição do nó.
    vector<size_t> node_at_index(n, 0);

    // Criando o vetor para armazenar o caminho.
    vector<size_t> path;

    // Chamando a função floyd.
    g->floyd(vertex_1, distance, parents, node_at_index);

    // Caso o grafo nao tenha ciclos negativos.
    if (find(node_at_index.begin(), node_at_index.end(), vertex_1) != node_at_index.end())
    {
        // Verificando se há conexão entre os vértices.
        if (distance[find(node_at_index.begin(), node_at_index.end(), vertex_1) - node_at_index.begin()][find(node_at_index.begin(), node_at_index.end(), vertex_2) - node_at_index.begin()] == FLT_MAX)
        {
            cout << "  Não há conexão entre os vértices " << vertex_1 << " e " << vertex_2 << "." << endl;
            return;
        }

        // Construíndo o caminho mínimo de vertex_1 para vertex_2.
        size_t p_v1 = find(node_at_index.begin(), node_at_index.end(), vertex_1) - node_at_index.begin();
        size_t p_v2 = find(node_at_index.begin(), node_at_index.end(), vertex_2) - node_at_index.begin();

        // Adicionando os vértices ao caminho.
        for (; p_v2 != p_v1; p_v2 = parents[p_v1][p_v2])
            path.insert(path.begin(), node_at_index[p_v2]);

        // Adicionando o vértice de origem.
        path.insert(path.begin(), vertex_1);

        // Escrevendo no buffer o caminho mínimo.
        output_buffer << "  Caminho Mínimo (Floyd) entre " << vertex_1 << " e " << vertex_2 << ": ";

        // Escrevendo o caminho no buffer.
        for (size_t i = 0; i < path.size(); i++)
        {
            output_buffer << path[i];
            if (i != path.size() - 1)
                output_buffer << " -> ";
        }

        // Escrevendo a distância no buffer.
        output_buffer << "\n  Distância: " << distance[find(node_at_index.begin(), node_at_index.end(), vertex_1) - node_at_index.begin()][find(node_at_index.begin(), node_at_index.end(), vertex_2) - node_at_index.begin()] << endl;
    }

    // Caso contrário, o grafo possui ciclos negativos.
    else
        return;
}

void prim_minimum_generating_tree(Graph *g, size_t *vertices, size_t size)
{
    // Vetores para armazenar o pai, chave e se o nó está na árvore.
    vector<size_t> parent(size);
    vector<float> key(size);
    vector<bool> mst_set(size);

    // Verificando se os vértices fazem parte do grafo.
    for (size_t i = 0; i < size; i++)
        if (g->find_node(vertices[i]) == NULL)
        {
            output_buffer << "  Um ou mais vértices não fazem parte do grafo." << endl;
            return;
        }

    // Verificando se o subconjunto de vértices é conexo.
    int connected = g->is_connected(vertices, size);
    if (connected == -1)
    {
        output_buffer << "  O subconjunto de vértices não é conexo." << endl;
        return;
    }

    // Chamando a função prim.
    g->prim(vertices, size, parent, key, mst_set, connected);

    // Escrevendo no buffer.
    output_buffer << "  Árvore Geradora Mínima (Prim) para os vértices: ";
    for (size_t i = 0; i < size; ++i)
    {
        if (i != (size - 1))
            output_buffer << vertices[i] << " ";
        else
            output_buffer << vertices[i] << ":\n\n";
    }

    // Calculando o valor da árvore geradora mínima e escrevendo no buffer.
    float vt_agm = 0;
    for (size_t i = 0; i < size; i++)
    {
        if(parent[i] == static_cast<size_t>(-1))
            continue;
        output_buffer << "\t\t\t" << vertices[parent[i]];
        if (g->get_directed())
            output_buffer << " -> ";
        else
            output_buffer << " - ";
        output_buffer << vertices[i] << "\n";
        vt_agm += key[i];
    }
    output_buffer << "\n  Valor da árvore geradora mínima: " << vt_agm << "\n";
}

void kruskal_minimum_generating_tree(Graph *g, size_t *vertices, size_t size)
{
    // Vetores para armazenar as arestas da árvore e as arestas.
    vector<pair<float, pair<size_t, size_t>>> tree_edges;
    vector<pair<float, pair<size_t, size_t>>> edges;

    // Variável para armazenar o valor da árvore geradora mínima.
    float vt_agm = 0;

    // Função para encontrar o conjunto disjunto.
    function<size_t(size_t, size_t *)> find_ds;

    // Verificando se os vértices fazem parte do grafo.
    for (size_t i = 0; i < size; i++)
        if (g->find_node(vertices[i]) == NULL)
        {
            output_buffer << "  Um ou mais vértices não fazem parte do grafo." << endl;
            return;
        }

    // Verificando se o subconjunto de vértices é conexo.
    if (g->is_connected(vertices, size) == -1)
    {
        output_buffer << "  O subconjunto de vértices não é conexo." << endl;
        return;
    }

    // Chamando a função kruskal.
    g->kruskal(edges, vertices, size, find_ds, tree_edges);

    // Escrevendo no buffer.
    output_buffer << "  Árvore Geradora Mínima (Kruskal) para os vértices: ";
    for (size_t i = 0; i < size; ++i)
    {
        if (i != (size - 1))
            output_buffer << vertices[i] << " ";
        else
            output_buffer << vertices[i] << ":\n\n";
    }

    // Calculando o valor da árvore geradora mínima e escrevendo no buffer.
    for (size_t i = 0; i < tree_edges.size(); i++)
    {
        output_buffer << "\t\t\t" << tree_edges[i].second.first;
        if(g->get_directed())
            output_buffer << " -> ";
        else
            output_buffer << " - ";
        output_buffer << tree_edges[i].second.second << endl;
        vt_agm += tree_edges[i].first;
    }

    output_buffer << "\n  Valor da árvore geradora minima: " << vt_agm << "\n";
}

void deep_walking(Graph *g, size_t vertex)
{
    // Vetor para armazenar as arestas de retorno.
    vector<pair<size_t, size_t>> return_edges;

    // Mapa para armazenar a lista de adjacência.
    map<size_t, vector<size_t>> adj_list;

    // Chamando a função de busca em profundidade.
    if (g->dfs_call(vertex, return_edges, adj_list))
    {
        // Escrevendo no buffer o caminhamento em profundidade.
        output_buffer << "  Caminhamento em Profundidade a partir do vértice " << vertex << ":" << endl;
        output_buffer << "\n  Lista de Adjacência:" << endl;

        for (auto &entry : adj_list)
        {
            // Escrevendo a lista de adjacência no buffer.
            output_buffer << "\t\t\t" << entry.first << " -> ";

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
        for (auto &edge : return_edges)
            output_buffer << "  (" << edge.first << ", " << edge.second << ") ";
        output_buffer << endl;
    }
    // Caso o nó não seja encontrado no grafo.
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
    // Verificando se o grafo possui vértices.
    if (g->get_num_nodes() == 0)
    {
        cout << "  Grafo vazio, sem vértices de articulação. " << endl;
        return;
    }

    // Vetores para armazenar os vértices visitados, tempo de descoberta, tempo de baixa, pai e vértices de articulação.
    vector<bool> visited(g->get_num_nodes(), false);
    vector<int> disc_time(g->get_num_nodes(), -1);
    vector<int> low_time(g->get_num_nodes(), -1);
    vector<size_t> parent(g->get_num_nodes(), static_cast<size_t>(-1));
    vector<bool> art_point(g->get_num_nodes(), false);

    // Variável para armazenar o tempo.
    int time = 0;

    // Chamando a função de articulação para cada vértice não visitado.
    for (size_t i = 0; i < g->get_num_nodes(); ++i)
        if (!visited[i])
            g->dfs_articulation(i, visited, disc_time, low_time, parent, art_point, time);

    // Escrevendo no buffer os vértices de articulação.
    output_buffer << "  Vértices de Articulação do Grafo: ";

    // Verificando se há vértices de articulação.
    bool found_art_point = false;
    for (size_t i = 0; i < g->get_num_nodes(); ++i)
        if (art_point[i])
        {
            output_buffer << i + 1 << " ";
            found_art_point = true;
        }

    // Caso não haja vértices de articulação.
    if (!found_art_point)
        output_buffer << "Nenhum";

    output_buffer << endl;
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
        sleep_for_seconds(3, false);

        // Fechando o arquivo.
        output_file.close();
    }

    // Caso contrário.
    else
        cout << "  Erro ao abrir o arquivo para salvar a saída." << endl;
}

void print_start()
{
    // Barra de progresso.
    int progressBarWidth = 50;

    // Imprimindo a barra de progresso.
    cout << "\n\n\t\tInicializando grafo...\n";
    cout << "[";

    for (int i = 0; i < progressBarWidth; ++i)
        cout << " ";

    cout << "]\r[";

    cout.flush();

    // Simulando o carregamento.
    for (int i = 0; i < progressBarWidth; ++i)
    {
        sleep_for_seconds(10, true);
        cout << "=";
        cout.flush();
    }

    cout << "]\n";
    cout << "\t   Grafo inicializado com sucesso!\n";
    sleep_for_seconds(2, false);
}

void sleep_for_seconds(int seconds, bool miliseconds)
{
    // Função para aguardar um tempo em segundos nos ambientes Windows e Unix.
#ifdef _WIN32
    if (miliseconds)
        Sleep(seconds * 10);
    else
        Sleep(seconds * 1000);
#else
    if (miliseconds)
        usleep(seconds * 10000);
    else
        sleep(seconds);
#endif
}