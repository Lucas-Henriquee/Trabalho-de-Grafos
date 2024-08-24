#include <gtest/gtest.h>
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

class GraphOperationsDirectedTest : public ::testing::Test
{
protected:
    Graph *graph;

    GraphOperationsDirectedTest()
    {
        ifstream file("./instances_example/5nD.dat");
        if (!file.good())
        {
            cerr << "Erro ao abrir o arquivo 5nD.dat" << endl;
            graph = nullptr;
            return;
        }

        graph = new Graph(file, true, true, false);
    }

    ~GraphOperationsDirectedTest() override
    {
        if (graph != nullptr)
        {
            delete graph;
            graph = nullptr;
        }
    }
};

TEST_F(GraphOperationsDirectedTest, DirectTransitiveClosure)
{
    vector<bool> visited(graph->get_num_nodes() + 1, false);
    graph->dfs_transitive(1, visited, true);

    vector<int> expected = {2, 3, 4, 5};
    vector<int> visited_ids;

    for (size_t i = 1; i < visited.size(); i++)
        if (visited[i])
            visited_ids.push_back(i);

    EXPECT_EQ(visited_ids, expected) << "O fecho transitivo direto não está correto";
}

TEST_F(GraphOperationsDirectedTest, IndirectTransitiveClosure)
{
    vector<bool> visited(graph->get_num_nodes() + 1, false);
    graph->dfs_transitive(2, visited, false);

    vector<int> expected_visited = {1};
    vector<int> actual_visited;

    for (int v = visited.size() - 1; v >= 0; v--)
        if (visited[v])
            actual_visited.push_back(v);

    EXPECT_EQ(actual_visited, expected_visited) << "O fecho transitivo indireto não está correto";
}

TEST_F(GraphOperationsDirectedTest, DijkstraShortestPath)
{
    size_t vertex_1 = 1;
    size_t vertex_2 = 4;

    vector<float> distance(graph->get_num_nodes(), std::numeric_limits<float>::infinity());
    vector<int> parents(graph->get_num_nodes(), -1);
    vector<size_t> node_at_index(graph->get_num_nodes());
    vector<size_t> path;

    graph->dijkstra(vertex_1, distance, parents, node_at_index);

    if (find(node_at_index.begin(), node_at_index.end(), vertex_2) == node_at_index.end())
    {
        FAIL() << "Não há conexão entre os vértices " << vertex_1 << " e " << vertex_2 << ".";
        return;
    }

    for (int v = find(node_at_index.begin(), node_at_index.end(), vertex_2) - node_at_index.begin(); v != 0; v = parents[v])
        path.push_back(v);

    path.push_back(0);

    reverse(path.begin(), path.end());

    vector<size_t> path_nodes;
    for (size_t i = 0; i < path.size(); i++)
        path_nodes.push_back(node_at_index[path[i]]);

    vector<size_t> expected_path = {1, 3, 4};

    EXPECT_EQ(path_nodes, expected_path) << "O caminho mais curto calculado não é o esperado.";
}

TEST_F(GraphOperationsDirectedTest, FloydShortestPath)
{
    size_t vertex_1 = 1;
    size_t vertex_2 = 4;

    size_t n = graph->get_num_nodes();
    vector<vector<float>> distance(n, vector<float>(n));
    vector<vector<int>> parents(n, vector<int>(n));
    vector<size_t> node_at_index(n);
    vector<size_t> path;

    graph->floyd(vertex_1, distance, parents, node_at_index);

    if (find(node_at_index.begin(), node_at_index.end(), vertex_2) == node_at_index.end())
    {
        FAIL() << "Não há conexão entre os vértices " << vertex_1 << " e " << vertex_2 << ".";
        return;
    }

    size_t p_v1 = find(node_at_index.begin(), node_at_index.end(), vertex_1) - node_at_index.begin();
    size_t p_v2 = find(node_at_index.begin(), node_at_index.end(), vertex_2) - node_at_index.begin();

    for (; p_v2 != p_v1; p_v2 = parents[p_v1][p_v2])
        path.insert(path.begin(), node_at_index[p_v2]);

    path.insert(path.begin(), vertex_1);

    vector<size_t> expected_path = {1, 3, 4};

    EXPECT_EQ(path, expected_path) << "O caminho mais curto calculado não é o esperado.";
}

TEST_F(GraphOperationsDirectedTest, PrimMinimumGeneratingTree)
{
    size_t size = 5;
    size_t sub_vertices[] = {1, 2, 3, 4, 5};

    vector<size_t> parent(size);
    vector<float> key(size);
    vector<bool> mst_set(size);

    graph->prim(sub_vertices, size, parent, key, mst_set);

    float vt_agm = 0;
    float expected_vt_agm = 16.0;

    for (size_t i = 1; i < size; i++)
        vt_agm += key[i];

    EXPECT_FLOAT_EQ(vt_agm, expected_vt_agm) << "O valor total da árvore geradora mínima não é o esperado.";
}

TEST_F(GraphOperationsDirectedTest, KruskalMinimumGeneratingTree)
{
    vector<pair<float, pair<size_t, size_t>>> tree_edges;
    vector<pair<float, pair<size_t, size_t>>> edges;

    size_t size = 5;
    size_t sub_vertices[] = {1, 2, 3, 4, 5};

    float vt_agm = 0;
    float expected_vt_agm = 16.0;

    function<size_t(size_t, size_t *)> find_ds;

    find_ds = [&](size_t i, size_t *parent) -> size_t
    {
        if (parent[i] == i)
            return i;

        return parent[i] = find_ds(parent[i], parent);
    };

    graph->kruskal(edges, sub_vertices, size, find_ds, tree_edges);

    for (size_t i = 0; i < tree_edges.size(); i++)
        vt_agm += tree_edges[i].first;

    EXPECT_FLOAT_EQ(vt_agm, expected_vt_agm) << "O valor total da árvore geradora mínima não é o esperado.";
}

TEST_F(GraphOperationsDirectedTest, DeepWalking)
{
    vector<pair<size_t, size_t>> return_edges;
    vector<pair<size_t, size_t>> expected_edges = {{1, 3}};

    map<size_t, vector<size_t>> adj_list;
    map<size_t, vector<size_t>> expected_adj_list = {{1, {2, 3}}, {2, {3}}, {3, {4}}, {4, {5}}, {5, {}}};

    graph->dfs_call(1, return_edges, adj_list);

    EXPECT_EQ(return_edges, expected_edges) << "As arestas retornadas pelo DFS não correspondem às esperadas.";
    EXPECT_EQ(adj_list, expected_adj_list) << "A lista de adjacência gerada pelo DFS não corresponde à esperada.";
}

TEST_F(GraphOperationsDirectedTest, PropertiesGraph)
{
    float radius, diameter;
    float expected_radius = 0.0;
    float expected_diameter = 16.0;

    vector<size_t> center;
    vector<size_t> expected_center = {5};

    vector<size_t> periphery;
    vector<size_t> expected_periphery = {1};

    graph->compute_graph_properties(radius, diameter, center, periphery);

    EXPECT_FLOAT_EQ(radius, expected_radius) << "O raio calculado do grafo não é o esperado.";
    EXPECT_FLOAT_EQ(diameter, expected_diameter) << "O diâmetro calculado do grafo não é o esperado.";
    EXPECT_EQ(center, expected_center) << "O(s) centro(s) calculado(s) do grafo não é(são) o(s) esperado(s).";
    EXPECT_EQ(periphery, expected_periphery) << "A(s) periferia(s) calculada(s) do grafo não é(são) a(s) esperada(s).";
}