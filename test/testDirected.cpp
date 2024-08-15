#include <catch2/catch.hpp>
#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

struct GraphOperationsTest
{
    Graph *graph;

    // Construtor: Inicializa o grafo
    GraphOperationsTest()
    {
        ifstream file("./instances_example/5nD.dat");
        if (!file.good())
        {
            cerr << "Erro ao abrir o arquivo 5nD.dat" << endl;
            graph = NULL;
            return;
        }

        graph = new Graph(file, false, true, false);
    }

    // Destrutor: Deleta o grafo
    ~GraphOperationsTest()
    {
        if (graph != NULL)
        {
            delete graph;
            graph = NULL;
        }
    }
};

TEST_CASE_METHOD(GraphOperationsTest, "DirectTransitiveClosure", "[GraphOperations]")
{
    REQUIRE(graph != NULL);

    vector<bool> visited(graph->get_num_nodes() + 1, false);
    graph->dfs_transitive(1, visited, true);

    vector<int> expected = {2, 3, 4, 5};
    vector<int> visited_ids;
    for (size_t i = 1; i < visited.size(); i++)
        if (visited[i])
            visited_ids.push_back(i);

    REQUIRE(visited_ids == expected);
}

TEST_CASE_METHOD(GraphOperationsTest, "IndirectTransitiveClosure", "[GraphOperations]")
{
    // TODO: Rever esse teste aqui 

    REQUIRE(graph != NULL); 

    vector<bool> visited(graph->get_num_nodes() + 1, false);

    graph->dfs_transitive(2, visited, false);  

    vector<int> expected_visited = {1};

    vector<int> actual_visited;
    for (int v = visited.size() - 1; v >= 0; v--)
        if (visited[v])
            actual_visited.push_back(v);

    REQUIRE(actual_visited == expected_visited);
}

TEST_CASE_METHOD(GraphOperationsTest, "DijkstraShortestPath", "[GraphOperations]")
{
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "FloydShortestPath", "[GraphOperations]")
{
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "PrimMinimumGeneratingTree", "[GraphOperations]")
{
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "KruskalMinimumGeneratingTree", "[GraphOperations]")
{
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "DeepWalking", "[GraphOperations]")
{
    vector<pair<size_t, size_t>> return_edges;
    vector<pair<size_t, size_t>> expected_edges = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};

    map<size_t, vector<size_t>> adj_list;
    map<size_t, vector<size_t>> expected_adj_list = {{1, {2}}, {2, {3}}, {3, {4}}, {4, {5}}, {5, {}}};

    graph->dfs_call(1, return_edges, adj_list);

    REQUIRE(return_edges == expected_edges);
    REQUIRE(adj_list == expected_adj_list);
}

TEST_CASE_METHOD(GraphOperationsTest, "PropertiesGraph", "[GraphOperations]")
{
    float radius, diameter;
    float expected_radius = 0.0;
    float expected_diameter = 16.0;

    vector<size_t> center;
    vector<size_t> expected_center = {5};

    vector<size_t> periphery;
    vector<size_t> expected_periphery = {1};   

    graph->compute_graph_properties(radius, diameter, center, periphery);

    REQUIRE(radius == expected_radius);
    REQUIRE(diameter == expected_diameter);
    REQUIRE(center == expected_center);
    REQUIRE(periphery == expected_periphery);
}
