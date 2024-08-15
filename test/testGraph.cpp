#define CATCH_CONFIG_MAI
#include <catch2/catch.hpp>
#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

struct GraphTest
{
    Graph *graph;

    // Construtor: Inicializa o grafo
    GraphTest()
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
    ~GraphTest()
    {
        if (graph != NULL)
        {
            delete graph;
            graph = NULL;
        }
    }
};

TEST_CASE_METHOD(GraphTest, "AddNode", "[Graph]")
{
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphTest, "AddEdge", "[Graph]")
{
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphTest, "RemoveNode", "[Graph]")
{
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphTest, "RemoveEdge", "[Graph]")
{
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphTest, "GraphConstructor", "[Graph]")
{
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphTest, "GraphDestructor", "[Graph]")
{
    // TODO: Implementar o teste
}
