#include "include/Graph.hpp"
#include "include/GraphOperations.hpp"
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
        {
            bool directed = 0;
            bool weight_nodes = (string(argv[5]) == "1");

            g = new Graph(file);
            
            print_start();
        }

        else
            cout << "Erro ao abrir o arquivo" << endl;

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