#include <gtest/gtest.h>
#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

class GraphOperationsTest : public ::testing::Test {
protected:
    Graph *graph;

    // Construtor: Inicializa o grafo
    GraphOperationsTest() {
        ifstream file("./instances_example/5nD.dat");
        if (!file.good()) {
            cerr << "Erro ao abrir o arquivo 5nD.dat" << endl;
            graph = nullptr;
            return;
        }

        graph = new Graph(file, false, true, false);
    }

    // Destrutor: Deleta o grafo
    ~GraphOperationsTest() override {
        if (graph != nullptr) {
            delete graph;
            graph = nullptr;
        }
    }
};

TEST_F(GraphOperationsTest, DirectTransitiveClosure) {
    ASSERT_NE(graph, nullptr);

    vector<bool> visited(graph->get_num_nodes() + 1, false);
    graph->dfs_transitive(1, visited, true);

    vector<int> expected = {2, 3, 4, 5};
    vector<int> visited_ids;
    for (size_t i = 1; i < visited.size(); i++) {
        if (visited[i]) {
            visited_ids.push_back(i);
        }
    }

    EXPECT_EQ(visited_ids, expected);
}

TEST_F(GraphOperationsTest, IndirectTransitiveClosure) {
    ASSERT_NE(graph, nullptr);

    vector<bool> visited(graph->get_num_nodes() + 1, false);
    graph->dfs_transitive(2, visited, false);

    vector<int> expected_visited = {1};

    vector<int> actual_visited;
    for (int v = visited.size() - 1; v >= 0; v--) {
        if (visited[v]) {
            actual_visited.push_back(v);
        }
    }

    EXPECT_EQ(actual_visited, expected_visited);
}

TEST_F(GraphOperationsTest, DijkstraShortestPath) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste DijkstraShortestPath";
}

TEST_F(GraphOperationsTest, FloydShortestPath) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste FloydShortestPath";
}

TEST_F(GraphOperationsTest, PrimMinimumGeneratingTree) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste PrimMinimumGeneratingTree";
}

TEST_F(GraphOperationsTest, KruskalMinimumGeneratingTree) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste KruskalMinimumGeneratingTree";
}

TEST_F(GraphOperationsTest, DeepWalking) {
    vector<pair<size_t, size_t>> return_edges;
    vector<pair<size_t, size_t>> expected_edges = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};

    map<size_t, vector<size_t>> adj_list;
    map<size_t, vector<size_t>> expected_adj_list = {{1, {2}}, {2, {3}}, {3, {4}}, {4, {5}}, {5, {}}};

    graph->dfs_call(1, return_edges, adj_list);

    EXPECT_EQ(return_edges, expected_edges);
    EXPECT_EQ(adj_list, expected_adj_list);
}

TEST_F(GraphOperationsTest, PropertiesGraph) {
    float radius, diameter;
    float expected_radius = 0.0;
    float expected_diameter = 16.0;

    vector<size_t> center;
    vector<size_t> expected_center = {5};

    vector<size_t> periphery;
    vector<size_t> expected_periphery = {1};

    graph->compute_graph_properties(radius, diameter, center, periphery);

    EXPECT_FLOAT_EQ(radius, expected_radius);
    EXPECT_FLOAT_EQ(diameter, expected_diameter);
    EXPECT_EQ(center, expected_center);
    EXPECT_EQ(periphery, expected_periphery);
}