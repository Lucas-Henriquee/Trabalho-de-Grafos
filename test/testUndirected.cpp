#include <gtest/gtest.h>
#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

class GraphOperationsUndirectedTest : public ::testing::Test {
protected:
    Graph *graph;

    // Construtor: Inicializa o grafo
    GraphOperationsUndirectedTest() {
        ifstream file("./instances_example/5nU.dat");
        if (!file.good()) {
            cerr << "Erro ao abrir o arquivo 5nU.dat" << endl;
            graph = nullptr;
            return;
        }

        graph = new Graph(file, false, true, false);
    }

    // Destrutor: Deleta o grafo
    ~GraphOperationsUndirectedTest() override {
        if (graph != nullptr) {
            delete graph;
            graph = nullptr;
        }
    }
};

TEST_F(GraphOperationsUndirectedTest, UndirectedDijkstraShortestPath) {
    // TODO: Implementar o teste
}

TEST_F(GraphOperationsUndirectedTest, UndirectedFloydShortestPath) {
    // TODO: Implementar o teste
}

TEST_F(GraphOperationsUndirectedTest, UndirectedPrimMinimumGeneratingTree) {
    // TODO: Implementar o teste
}

TEST_F(GraphOperationsUndirectedTest, UndirectedKruskalMinimumGeneratingTree) {
    // TODO: Implementar o teste
}

TEST_F(GraphOperationsUndirectedTest, UndirectedDeepWalking) {
    // TODO: Implementar o teste
}

TEST_F(GraphOperationsUndirectedTest, UndirectedPropertiesGraph) {
    // TODO: Implementar o teste
}
