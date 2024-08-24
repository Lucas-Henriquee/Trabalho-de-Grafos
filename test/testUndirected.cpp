#include <gtest/gtest.h>
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

class GraphOperationsUndirectedTest : public ::testing::Test
{
protected:
    Graph *graph;

    GraphOperationsUndirectedTest()
    {
        ifstream file("./instances_example/5nU.dat");
        if (!file.good())
        {
            cerr << "Erro ao abrir o arquivo 5nU.dat" << endl;
            graph = nullptr;
            return;
        }

        graph = new Graph(file, false, true, false);
    }

    ~GraphOperationsUndirectedTest() override
    {
        if (graph != nullptr)
        {
            delete graph;
            graph = nullptr;
        }
    }
};

TEST_F(GraphOperationsUndirectedTest, DijkstraShortestPath)
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

TEST_F(GraphOperationsUndirectedTest, FloydShortestPath)
{
    size_t vertex_1 = 1;
    size_t vertex_2 = 4;

    size_t n = graph->get_num_nodes();
    vector<vector<float>> distance(n, vector<float>(n));
    vector<vector<int>> parents(n, vector<int>(n));
    vector<size_t> node_at_index(n);
    vector<size_t> path;

    graph->floyd(distance, parents, node_at_index);

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

TEST_F(GraphOperationsUndirectedTest, PrimMinimumGeneratingTree)
{
    size_t size = 5;
    size_t sub_vertices[] = {1, 2, 3, 4, 5};

    vector<size_t> parent(size);
    vector<float> key(size);
    vector<bool> mst_set(size);

    graph->prim(sub_vertices, size, parent, key, mst_set);

    vector<float> expected_key = {0.0, 3.0, 2.0, 7.0, 4.0};
    vector<bool> expected_mst_set = {true, true, true, true, false};

    float vt_agm = 0;
    float expected_vt_agm = 16.0;

    for (size_t i = 1; i < size; i++)
        vt_agm += key[i];

    EXPECT_EQ(key, expected_key) << "As chaves calculadas para a árvore geradora mínima não são as esperadas.";
    EXPECT_EQ(mst_set, expected_mst_set) << "Os vértices da árvore geradora mínima não são os esperados.";
    EXPECT_FLOAT_EQ(vt_agm, expected_vt_agm) << "O valor total da árvore geradora mínima não é o esperado.";
}

TEST_F(GraphOperationsUndirectedTest, KruskalMinimumGeneratingTree)
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

TEST_F(GraphOperationsUndirectedTest, DeepWalking)
{
    vector<pair<size_t, size_t>> return_edges;
    vector<pair<size_t, size_t>> expected_edges = {{3, 1}};

    map<size_t, vector<size_t>> adj_list;
    map<size_t, vector<size_t>> expected_adj_list = {{1, {2, 3}}, {2, {1, 3}}, {3, {1, 4, 2}}, {4, {3, 5}}, {5, {4}}};

    graph->dfs_call(1, return_edges, adj_list);

    EXPECT_EQ(return_edges, expected_edges) << "As arestas retornadas pelo DFS não correspondem às esperadas.";
    EXPECT_EQ(adj_list, expected_adj_list) << "A lista de adjacência gerada pelo DFS não corresponde à esperada.";
}

TEST_F(GraphOperationsUndirectedTest, PropertiesGraph)
{
    float radius, diameter;
    float expected_radius = 11.0;
    float expected_diameter = 16.0;

    vector<size_t> center;
    vector<size_t> expected_center = {3};

    vector<size_t> periphery;
    vector<size_t> expected_periphery = {1, 5};

    graph->compute_graph_properties(radius, diameter, center, periphery);

    EXPECT_FLOAT_EQ(radius, expected_radius) << "O raio calculado do grafo não é o esperado.";
    EXPECT_FLOAT_EQ(diameter, expected_diameter) << "O diâmetro calculado do grafo não é o esperado.";
    EXPECT_EQ(center, expected_center) << "O(s) centro(s) calculado(s) do grafo não é(são) o(s) esperado(s).";
    EXPECT_EQ(periphery, expected_periphery) << "A(s) periferia(s) calculada(s) do grafo não é(são) a(s) esperada(s).";
}

TEST_F(GraphOperationsUndirectedTest, ArticulationVertices)
{
    vector<bool> visited(graph->get_num_nodes(), false);
    vector<int> disc_time(graph->get_num_nodes(), -1);
    vector<int> low_time(graph->get_num_nodes(), -1);
    vector<size_t> parent(graph->get_num_nodes(), static_cast<size_t>(-1));
    vector<bool> art_point(graph->get_num_nodes(), false);

    int time = 0;

    for (size_t i = 0; i < graph->get_num_nodes(); ++i)
        if (!visited[i])
            graph->dfs_articulation(i, visited, disc_time, low_time, parent, art_point, time);

    vector<size_t> articulation_points;
    for (size_t i = 0; i < graph->get_num_nodes(); ++i)
        if (art_point[i])
            articulation_points.push_back(i + 1);

    vector<size_t> expected_art_points = {3, 4};

    EXPECT_EQ(articulation_points, expected_art_points) << "Os vértices de articulação calculados não são os esperados.";
}