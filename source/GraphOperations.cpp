#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

ostringstream output_buffer;

void menu(Graph *g, string file_exit)
{

    int i = -1;
    size_t size, vertex_1, vertex_2;

    do
    {
        system("clear||cls");

        cout << "\n\t  Menu de Operações do Grafo\n\n\n";
        cout << "  1) Fecho Transitivo Direto de um vértice" << endl;
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
            // floyd_shortest_path(g, vertex_1, vertex_2);
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
            // properties_graph(g);
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
            this_thread::sleep_for(chrono::seconds(3));
            break;
        }
        default:
        {
            cout << "\n  Opção inválida! Tente novamente." << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
        }
        output_buffer << "\n  -------------------------------------------------------------\n"
                      << endl;
        cout << output_buffer.str();
        this_thread::sleep_for(chrono::seconds(2));
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

void transitive_direct(Graph *g, size_t vertex)
{
    // Cria um vetor de nós visitados com o tamanho igual ao número de nós no grafo,
    // inicializando todos os elementos como NULL.
    vector<Node *> visited(g->get_num_nodes(), NULL);

    // Chama a função dfs (Busca em Profundidade) para marcar no vetor os nós visitados a partir do vértice vertex.
    g->dfs_transitive(vertex, visited, true);

    // Escreve no buffer.
    output_buffer << "  Fecho Transitivo Direto para o vértice " << vertex << ": ";

    // Faz a escrita no buffer dos IDs dos nós visitados.
    int size = visited.size();

    for (int v = 0; v < size; v++)
        if (visited[v])
            output_buffer << visited[v]->_id << " ";

    // Conclui a escrita no buffer e exibe no terminal ao usuário.
    output_buffer << "\n";
}

void transitive_indirect(Graph *g, size_t vertex)
{
    // Cria um vetor de nós visitados com o tamanho igual ao número de nós no grafo,
    // inicializando todos os elementos como NULL.
    vector<Node *> visited(g->get_num_nodes(), NULL);

    // Chama a função dfs (Busca em Profundidade) para marcar no vetor os nós visitados a partir do vértice vertex.
    g->dfs_transitive(vertex, visited, false);

    // Escreve no buffer.
    output_buffer << "  Fecho Transitivo Indireto para o vértice " << vertex << ": ";

    // Faz a escrita no buffer dos IDs dos nós visitados.
    for (int v = visited.size() - 1; v >= 0; v--)
        if (visited[v])
            output_buffer << visited[v]->_id << " ";

    // Conclui a escrita no buffer e exibe no terminal ao usuário.
    output_buffer << "\n";
}

void dijkstra_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2)
{
    vector<size_t> distance(g->get_num_nodes());
    vector<int> parents(g->get_num_nodes(), -1);
    vector<size_t> node_at_index(g->get_num_nodes());
    g->dijkstra(vertex_1, distance, parents);

    vector<size_t> path(g->get_num_nodes());
    for (int v = vertex_2; v != vertex_1; v = parents[v]){
        path.push_back(v);
    }
        
    path.push_back(vertex_1);

    reverse(path.begin(), path.end());

    for(size_t i = 0; i<path.size(); i++){
        output_buffer << path[i] << " ";
    }

    output_buffer << "   Caminho Mínimo (Dijkstra) entre " << vertex_1 << " e " << vertex_2 << ": ...\n";
    cout << output_buffer.str();
}

void floyd_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2)
{
    // Implementação
    output_buffer << "  Caminho Mínimo (Floyd) entre " << vertex_1 << " e " << vertex_2 << ": ...\n";
    cout << output_buffer.str();
}

void prim_minimum_generating_tree(Graph *g, size_t *vertices, size_t size)
{
    // Verifica se o grafo existe e se o subconjunto de vértices não está vazio.
    if (!g || size == 0)
    {
        cout << "Grafo ou subconjunto de vértices inválido." << endl;
        this_thread::sleep_for(chrono::seconds(3));

        return;
    }

    output_buffer << "  Árvore Geradora Mínima (Prim) para os vértices: ";
    for (size_t i = 0; i < size; ++i)
        output_buffer << vertices[i] << " ";

    output_buffer << "\n";
    cout << output_buffer.str();
}

void kruskal_minimum_generating_tree(Graph *g, size_t *vertices, size_t size)
{
    output_buffer << "  Árvore Geradora Mínima (Kruskal) para os vértices: ";
    for (size_t i = 0; i < size; ++i)
    {
        output_buffer << vertices[i] << " ";
    }
    output_buffer << "\n";
    cout << output_buffer.str();
}

void deep_walking(Graph *g, size_t vertex)
{
    // Verifica se o grafo está vazio.
    if (g->get_num_nodes() == 0)
    {
        cout << "  O Grafo está vazio." << endl;
        return;
    }

    // Inicializa o vetor de arestas de retorno e a string da árvore.
    vector<pair<size_t, size_t>> return_edges;
    string tree;

    // Chama a função DFS.
    g->dfs(g, vertex, return_edges, tree);

    // Imprime a árvore de caminhamento em profundidade.
    output_buffer << "  Caminhamento em profundidade a partir do vértice " << vertex << ": " << tree << endl;

    // Imprime as arestas de retorno.
    if (return_edges.empty())
        output_buffer << "\n  Arestas de retorno: Nenhuma" << endl;
    else
    {
        output_buffer << "\n  Arestas de retorno:" << endl;
        for (auto &edge : return_edges)
            output_buffer << "  (" << edge.first << ", " << edge.second << ")" << endl;
    }
}

void properties_graph(Graph *g)
{
}

void articulation_vertices(Graph *g)
{
    g->dfs_articulation();

    output_buffer << "  Vértices de Articulação do Grafo: ...\n";
    cout << output_buffer.str();
}

void save_exit(Graph *g, string file_exit)
{
    ifstream check_file(file_exit);
    bool file_exists = check_file.good();

    ofstream output_file(file_exit, ios::out | ios::app);

    if (output_file.is_open())
    {

        if (!file_exists)
            g->print_graph(output_file);

        output_file << output_buffer.str();

        cout << "  Saída salva no arquivo: " << file_exit << endl;
        this_thread::sleep_for(chrono::seconds(3));

        output_file.close();
    }

    else
        cout << "  Erro ao abrir o arquivo para salvar a saída." << endl;
}