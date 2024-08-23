#include <gtest/gtest.h>
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

class GraphTest : public ::testing::Test
{
protected:
    Graph *graph;

    GraphTest()
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

    ~GraphTest() override
    {
        if (graph != nullptr)
        {
            delete graph;
            graph = nullptr;
        }
    }
};

TEST_F(GraphTest, TestGraphCreation)
{
    EXPECT_EQ(graph->get_num_nodes(), 5) << "Número de nós esperado: 5, obtido: " << graph->get_num_nodes();
    EXPECT_EQ(graph->get_num_edges(), 5) << "Número de arestas esperado: 5, obtido: " << graph->get_num_edges();
}

TEST_F(GraphTest, TestAddNode)
{
    graph->add_node(6, 1.0);
    Node *node = graph->find_node(6);
    
    ASSERT_NE(node, nullptr) << "O nó 6 não foi encontrado após ser adicionado.";

    EXPECT_EQ(node->_id, 6) << "ID do nó esperado: 6, obtido: " << node->_id;
    EXPECT_FLOAT_EQ(node->_weight, 1.0) << "Peso do nó esperado: 1.0, obtido: " << node->_weight;
}

TEST_F(GraphTest, TestRemoveNode)
{
    graph->remove_node(6);
    EXPECT_EQ(graph->find_node(6), nullptr) << "O nó 6 ainda existe no grafo após a remoção.";
}

TEST_F(GraphTest, TestAddEdge)
{
    graph->add_edge(5, 3, 1.0);
    Edge *edge = graph->find_edge(5, 3);

    ASSERT_NE(edge, nullptr) << "A aresta entre 5 e 3 não foi encontrada após ser adicionada.";

    EXPECT_FLOAT_EQ(edge->_weight, 1.0) << "Peso da aresta esperado: 1.0, obtido: " << edge->_weight;
}

TEST_F(GraphTest, TestRemoveEdge)
{
    graph->remove_edge(5, 3);
    EXPECT_EQ(graph->find_edge(5, 3), nullptr) << "A aresta entre 5 e 3 ainda existe após a remoção.";
}

TEST_F(GraphTest, TestConected)
{
    EXPECT_EQ(graph->conected(1, 2), 1) << "Os nós 1 e 2 deveriam estar conectados.";
    EXPECT_EQ(graph->conected(1, 4), 0) << "Os nós 1 e 4 não deveriam estar conectados.";
}