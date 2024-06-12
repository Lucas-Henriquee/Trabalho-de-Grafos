#include "include/Graph.hpp"
#include "include/GraphOperations.hpp"
#include "include/defines.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    /*
    argv[1] arquivo de entrada
    argv[2] arquivo de saida
    argv[3] Se é direcionado ou não
    argv[4] Se tem peso na aresta
    argv[5] Se tem peso nos nós
    */

    if (argc != 0)
    {
        string filename = argv[1];
        ifstream file(filename);

        Graph *g = NULL;

        if (file.is_open())
        {
            bool directed = (string(argv[3]) == "1");
            bool weight_edges = (string(argv[4]) == "1");
            bool weight_nodes = (string(argv[5]) == "1");

            g = new Graph(file, directed, weight_edges, weight_nodes);
            g->print_graph();
            this_thread::sleep_for(chrono::seconds(3));
        }
        else
            cout << "Erro ao abri o arquivo" << endl;

        file.close();

        string file_exit = argv[2];

        if (g != NULL)
        {
            menu(g, file_exit);
            delete g;
        }
    }

    return 0;
}