#include <gtest/gtest.h>
#include "../include/GraphOperations.hpp"
#include "../include/Graph.hpp"
#include "../include/defines.hpp"

using namespace std;

class GraphTest : public ::testing::Test {
protected:
    Graph *graph;

    // Construtor: Inicializa o grafo
    GraphTest() {
        ifstream file("./instances_example/5nD.dat");
        if (!file.good()) {
            cerr << "Erro ao abrir o arquivo 5nD.dat" << endl;
            graph = nullptr;
            return;
        }

        graph = new Graph(file, false, true, false);
    }

    // Destrutor: Deleta o grafo
    ~GraphTest() override {
        if (graph != nullptr) {
            delete graph;
            graph = nullptr;
        }
    }
};

TEST_F(GraphTest, AddNode) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste AddNode";
}

TEST_F(GraphTest, AddEdge) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste AddEdge";
}

TEST_F(GraphTest, RemoveNode) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste RemoveNode";
}

TEST_F(GraphTest, RemoveEdge) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste RemoveEdge";
}

TEST_F(GraphTest, GraphConstructor) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste GraphConstructor";
}

TEST_F(GraphTest, GraphDestructor) {
    // TODO: Implementar o teste
    FAIL() << "Implementar o teste GraphDestructor";
}
