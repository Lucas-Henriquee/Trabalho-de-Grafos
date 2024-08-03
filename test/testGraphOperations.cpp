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

    void SetUp()
    {
        ifstream file("./instances_example/5nD.dat");
        REQUIRE(file.good());
        
        graph = new Graph(file, false, true, false);
        REQUIRE(graph != nullptr);

        cout << "Graph initialized successfully" << endl;
    }

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
    SetUp();
    REQUIRE(graph != nullptr);

    vector<Node *> visited;
    graph->dfs_transitive(1, visited, false);

    // Valor esperado
    vector<int> expected = {2, 3, 4, 5};

    // Comparar o resultado com o valor esperado
    vector<int> visited_ids;
    for (auto node : visited)
    {
        if (node != nullptr)
        {
            visited_ids.push_back(node->_id);
        }
        else
        {
            cout << "Null node encountered in visited list" << endl;
        }
    }

    REQUIRE(visited_ids == expected);
    TearDown();
}

TEST_CASE_METHOD(GraphOperationsTest, "IndirectTransitiveClosure", "[GraphOperations]")
{
    SetUp();
    REQUIRE(graph != nullptr);

    vector<Node *> visited;
    graph->dfs_transitive(1, visited, true);

    // Adicionar lógica para testar o fecho transitivo indireto
    // Valor esperado
    vector<int> expected = {2, 3, 4, 5};

    // Comparar o resultado com o valor esperado
    vector<int> visited_ids;
    for (auto node : visited)
    {
        if (node != nullptr)
        {
            visited_ids.push_back(node->_id);
        }
        else
        {
            cout << "Null node encountered in visited list" << endl;
        }
    }

    REQUIRE(visited_ids == expected);
    TearDown();
}

TEST_CASE_METHOD(GraphOperationsTest, "DijkstraShortestPath", "[GraphOperations]")
{
    SetUp();
    REQUIRE(graph != nullptr);

    vector<size_t> node_by_index(graph->get_num_nodes() + 1, 0);
    Node *current_node = graph->get_first_node();

    while (current_node != nullptr)
    {
        node_by_index[current_node->_id] = current_node->_id;
        current_node = graph->get_next_node(current_node);
    }

    vector<float> distances;
    vector<int> parents;
    graph->dijkstra(1, distances, parents, node_by_index);

    // Valores esperados
    vector<float> expected_distances = {0, 3, 5, 12, 16};
    vector<int> expected_parents = {-1, 1, 1, 3, 4};

    REQUIRE(distances == expected_distances);
    REQUIRE(parents == expected_parents);
    TearDown();
}
