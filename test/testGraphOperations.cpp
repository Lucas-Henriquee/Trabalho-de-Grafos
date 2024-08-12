#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

class GraphOperationsTest
{
protected:
    Graph *graph;

    // Inicializando o grafo
    void SetUp()
    {
        ifstream file("./instances_example/5nD.dat");
        if (!file.good()) {
            cerr << "Erro ao abrir o arquivo 5nD.dat" << endl;
            return;
        }

        cerr << "passou por aqui" << endl;

        graph = new Graph(file, false, true, false);

        cerr << "aaaaaaaaaaaaaaa" << endl;
        REQUIRE(graph != nullptr);
    }

    // Deletando o grafo
    void TearDown()
    {
        if (graph != nullptr)
        {
            delete graph;
            graph = nullptr;
        }
    }
};

TEST_CASE_METHOD(GraphOperationsTest, "DirectTransitiveClosure", "[GraphOperations]")
{
    cerr << "passou por aqui 2" << endl;
    SetUp();

    REQUIRE(graph != nullptr);

    vector<bool> visited(graph->get_num_nodes() + 1, false);

    cerr << "passou por aqui 3" << endl;
    graph->dfs_transitive(1, visited, false);

    // Valor esperado
    vector<int> expected = {2, 3, 4, 5};

    // Comparar o resultado com o valor esperado

    vector<int> visited_ids;
    for (size_t i = 1; i < visited.size(); i++)
        if (visited[i])
            visited_ids.push_back(i);

    REQUIRE(visited_ids == expected);

    TearDown();
}

TEST_CASE_METHOD(GraphOperationsTest, "IndirectTransitiveClosure", "[GraphOperations]")
{
    SetUp();
    REQUIRE(graph != nullptr);

    vector<bool> visited(graph->get_num_nodes() + 1, false);

    cerr << "passou por aqui 2" << endl;
    graph->dfs_transitive(1, visited, true);

    // Adicionar lógica para testar o fecho transitivo indireto
    // Valor esperado
    vector<int> expected = {};

    // Comparar o resultado com o valor esperado
    vector<int> visited_ids;
    for (size_t i = 1; i < visited.size(); i++)
        if (visited[i])
            visited_ids.push_back(i);

    REQUIRE(visited_ids == expected);
    TearDown();
}

TEST_CASE_METHOD(GraphOperationsTest, "DijkstraShortestPath", "[GraphOperations]")
{
    SetUp();
    REQUIRE(graph != nullptr);

    // Verificar se os nós existem no grafo
    REQUIRE(graph->find_node(1) != nullptr);

    vector<size_t> node_by_index(graph->get_num_nodes() + 1, 0);

    for (size_t i = 1; i <= graph->get_num_nodes(); i++)
        node_by_index[i] = i;

    vector<float> distances(graph->get_num_nodes() + 1, FLT_MAX);
    vector<int> parents(graph->get_num_nodes() + 1, -1);
    graph->dijkstra(1, distances, parents, node_by_index);

    // Valores esperados
    REQUIRE(distances[1] == 0.0f);
    REQUIRE(distances[2] == 10.0f);
    REQUIRE(distances[3] == 30.0f);

    REQUIRE(parents[1] == -1);
    REQUIRE(parents[2] == 1);
    REQUIRE(parents[3] == 2);
}

TEST_CASE_METHOD(GraphOperationsTest, "FloydShortestPath", "[GraphOperations]")
{
    SetUp();
    REQUIRE(graph != nullptr);

    // Verificar se os nós existem no grafo
    REQUIRE(graph->find_node(1) != nullptr);

    // Inicializar node_by_index com os IDs dos nós
    vector<size_t> node_by_index(graph->get_num_nodes() + 1, 0);
    for (size_t i = 1; i <= graph->get_num_nodes(); i++)
        node_by_index[i] = i;

    // Inicializar as matrizes de distâncias e pais
    vector<vector<float>> distances(graph->get_num_nodes() + 1, vector<float>(graph->get_num_nodes() + 1, FLT_MAX));
    vector<vector<int>> parents(graph->get_num_nodes() + 1, vector<int>(graph->get_num_nodes() + 1, -1));

    // Chamar a função floyd
    graph->floyd(distances, parents, node_by_index);

    // Valores esperados
    REQUIRE(distances[1][1] == 0.0f);
    REQUIRE(distances[1][2] == 10.0f);
    REQUIRE(distances[1][3] == 30.0f);

    REQUIRE(parents[1][1] == -1);
    REQUIRE(parents[1][2] == 1);
    REQUIRE(parents[1][3] == 2);

    TearDown();
}

TEST_CASE_METHOD(GraphOperationsTest, "PrimMinimumGeneratingTree", "[GraphOperations]")
{
    // TODO:Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "KruskalMinimumGeneratingTree", "[GraphOperations]")
{
    // TODO:Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "DeepWalking", "[GraphOperations]")
{
    SetUp();
    REQUIRE(graph != nullptr);

    // Vetor para armazenar as arestas de retorno.
    vector<pair<size_t, size_t>> return_edges;

    // Mapa para armazenar a lista de adjacência.
    map<size_t, vector<size_t>> adj_list;

    graph->dfs_call(1, return_edges, adj_list);

    map<size_t, vector<size_t>> expected_adj_list = {
        {1, {2, 3}},
        {2, {1, 4}},
        {3, {1, 5}},
        {4, {2}},
        {5, {3}}};
        
    REQUIRE(expected_adj_list.size() == adj_list.size());
    REQUIRE(expected_adj_list == adj_list);

    TearDown();
}

TEST_CASE_METHOD(GraphOperationsTest, "PropertiesGraph", "[GraphOperations]")
{
    SetUp();
    REQUIRE(graph != nullptr);

    // Variáveis para armazenar o raio e o diâmetro.
    float radius;
    float expected_radius = 0;
    float diameter;
    float expected_diameter = 16;

    // Vetores para armazenar o centro e a periferia.
    vector<size_t> center;
    vector<size_t> expected_center = {16};
    vector<size_t> periphery;
    vector<size_t> expected_periphery = {1};

    // Chamando a função que calcula as propriedades do grafo.
    graph->compute_graph_properties(radius, diameter, center, periphery);

    REQUIRE(radius == expected_radius);
    REQUIRE(diameter == expected_diameter);
    REQUIRE(center == expected_center);
    REQUIRE(periphery == expected_periphery);

    TearDown();
}

TEST_CASE_METHOD(GraphOperationsTest, "ArticulationVertices", "[GraphOperations]")
{
    // TODO:Implementar o teste
}
