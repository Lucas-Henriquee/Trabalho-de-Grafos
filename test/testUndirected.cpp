#define CATCH_CONFIG_MAI
#include <catch2/catch.hpp>
#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

struct GraphOperationsTest {
    Graph *graph;

    // Construtor: Inicializa o grafo
    GraphOperationsTest() {
        ifstream file("./instances_example/5nU.dat");
        if (!file.good()) {
            cerr << "Erro ao abrir o arquivo 5nU.dat" << endl;
            graph = NULL;
            return;
        }

        graph = new Graph(file, false, true, false);
    }

    // Destrutor: Deleta o grafo
    ~GraphOperationsTest() {
        if (graph != NULL) {
            delete graph;
            graph = NULL;
        }
    }
};


TEST_CASE_METHOD(GraphOperationsTest, "UndirectedDijkstraShortestPath", "[GraphOperations]") {
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "UndirectedFloydShortestPath", "[GraphOperations]") {
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "UndirectedPrimMinimumGeneratingTree", "[GraphOperations]") {
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "UndirectedKruskalMinimumGeneratingTree", "[GraphOperations]") {
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "UndirectedDeepWalking", "[GraphOperations]") {
    // TODO: Implementar o teste
}

TEST_CASE_METHOD(GraphOperationsTest, "UndirectedPropertiesGraph", "[GraphOperations]") {
    // TODO: Implementar o teste
}
