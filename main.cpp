#include "include/Graph.hpp"
#include <thread>
#include <chrono>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

void menu(Graph *g, string file_exit);
void transitive_direct(Graph *g, size_t vertex);
void transitive_indirect(Graph *g, size_t vertex);
void dijkstra_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2);
void floyd_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2);
void prim_minimum_generating_tree(Graph *g, size_t *vertices, size_t size);
void kruskal_minimum_generating_tree(Graph *g, size_t *vertices, size_t size);
void deep_walking(Graph *g, size_t vertex);
void properties_graph(Graph *g);
void articulation_vertices(Graph *g);
void save_exit(Graph *g, string file);

ostringstream output_buffer;

int main(int argc, char *argv[])
{

    /*
    argv[1] arquivo de entrada
    argv[2] arquivo de saida
    argv[3] Se é direcionado ou não
    argv[4] Se tem peso na aresta
    argv[5] Se tem peso nos nós
    */

    if (argc != 0)
    {
        string filename = argv[1];
        ifstream file(filename);

        Graph *g = NULL;

        if (file.is_open())
        {
            bool directed = (string(argv[3]) == "1");
            bool weight_edges = (string(argv[4]) == "1");
            bool weight_nodes = (string(argv[5]) == "1");

            g = new Graph(file, directed, weight_edges, weight_nodes);
            g->print_graph();
        }
        else
            cout << "Erro ao abri o arquivo" << endl;

        file.close();

        string file_exit = argv[2];

        if (g != NULL)
        {
            menu(g, file_exit);
            delete g;
        }
    }

    return 0;
}

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
            //dijkstra_shortest_path(g, vertex_1, vertex_2);
            break;
        }
        case 4:
        {
            cout << "\n  Digite os IDs dos vértices (origem destino): ";
            cin >> vertex_1 >> vertex_2;
            //floyd_shortest_path(g, vertex_1, vertex_2);
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
            //prim_minimum_generating_tree(g, vertices, size);
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
            //kruskal_minimum_generating_tree(g, vertices, size);
            delete[] vertices;
            break;
        }
        case 7:
        {
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            //deep_walking(g, vertex_1);
            break;
        }
        case 8:
        {
            properties_graph(g);
            break;
        }
        case 9:
        {
            //articulation_vertices(g);
            break;
        }
        case 0:
        {
            cout << "\n  Encerrando o programa..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
        default:
        {
            cout << "\n  Opção inválida! Tente novamente." << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }

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
    for (size_t v = 0; v < visited.size(); v++)
        if (visited[v])
            output_buffer << visited[v]->_id << " ";

    // Conclui a escrita no buffer e exibe no terminal ao usuário.
    output_buffer << "\n";
    cout << output_buffer.str();
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
    for (size_t v = visited.size() - 1; v >= 0; v--)
        if (visited[v])
            output_buffer << visited[v]->_id << " ";

    // Conclui a escrita no buffer e exibe no terminal ao usuário.
    output_buffer << "\n";
    cout << output_buffer.str();
}

void dijkstra_shortest_path(Graph *g, size_t vertex_1, size_t vertex_2)
{
    // Implementação
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
        this_thread::sleep_for(chrono::seconds(2));

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
    // Implementação
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
    // Implementação
    output_buffer << "  Caminhamento em Profundidade a partir do vértice " << vertex << ": ...\n";
    cout << output_buffer.str();
}

void properties_graph(Graph *g)
{
    // Pega o número de nós do grafo.
    size_t n = g->get_num_nodes();

    // Verifica se o grafo está vazio.
    if (n == 0)
    {
        output_buffer << "  O Grafo está vazio. \n";
        cout << output_buffer.str();
        this_thread::sleep_for(chrono::seconds(2));

        return;
    }

    // Inicializa a matriz de distâncias com infinito.
    vector<vector<float>> dist(n, vector<float>(n, numeric_limits<float>::infinity()));

    // Inicializa a matriz de distâncias com os pesos das arestas.
    for (Node *aux_node = g->get_first_node(); aux_node != NULL; aux_node = aux_node->_next_node)
    {
        // Define a distância de um nó para ele mesmo como 0.
        dist[aux_node->_id][aux_node->_id] = 0;

        // Preenche a matriz de distâncias com os pesos das arestas.
        for (Edge *edge = aux_node->_first_edge; edge != NULL; edge = edge->_next_edge)
            dist[aux_node->_id][edge->_target_id] = edge->_weight;
    }

    // Algoritmo de Floyd-Warshall para encontrar as distâncias mínimas entre todos os pares de nós.
    for (size_t k = 0; k < n; k++)
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < n; j++)
                if (dist[i][k] < numeric_limits<float>::infinity() && dist[k][j] < numeric_limits<float>::infinity())
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // Calcula o raio, diâmetro, centro e periferia.
    float radius = numeric_limits<float>::infinity();
    float diameter = 0;
    vector<float> eccentricities(n, 0);

    // Calcula as excentricidades de cada nó.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
            if (i != j)
                eccentricities[i] = max(eccentricities[i], dist[i][j]);

        // Atualiza o raio e o diâmetro do grafo.
        radius = min(radius, eccentricities[i]);
        diameter = max(diameter, eccentricities[i]);
    }

    // Encontra os nós no centro e na periferia do grafo.
    vector<size_t> center;
    vector<size_t> periphery;

    for (size_t i = 0; i < n; i++)
    {
        if (eccentricities[i] == radius)
            center.push_back(i);

        if (eccentricities[i] == diameter)
            periphery.push_back(i);
    }

    // Conclui a escrita no buffer e exibe no terminal ao usuário.
    output_buffer << "  Propriedades do Grafo:\n";
    output_buffer << "  Raio do grafo: " << radius << "\n";
    output_buffer << "  Diâmetro do grafo: " << diameter << "\n";

    output_buffer << "  Centro do grafo: ";
    for (size_t v : center)
        output_buffer << v << " ";

    output_buffer << "\n  Periferia do grafo: ";
    for (size_t v : periphery)
        output_buffer << v << " ";

    output_buffer << "\n";

    cout << output_buffer.str();
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
        this_thread::sleep_for(chrono::seconds(2));

        output_file.close();
    }

    else
        cout << "  Erro ao abrir o arquivo para salvar a saída." << endl;
}