#include "include/Graph.hpp"
#include "include/GraphPartitioning.hpp"
#include "include/defines.hpp"

int main(int argc, char *argv[])
{

    /*
    argv[1] arquivo de entrada
    argv[2] arquivo de saída
    argv[3] Guloso (0), Guloso Randomizado (1), Guloso Randomizado Reativo (2)
    */

    if (argc != 0)
    {
        string filename = argv[1];

        ifstream file(filename);

        Graph *g = NULL;

        if (file.is_open())
            g = new Graph(file);

        else
            cout << "Erro ao abrir o arquivo" << endl;

        file.close();

        string file_exit = argv[2];
        char algorithm = string(argv[3])[0];

        //g->print_graph();

        if (g != NULL)
        {
            select_algorithm(g, algorithm);
            delete g;
        }
    }

    return 0;
}