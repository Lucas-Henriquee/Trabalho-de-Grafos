#include "include/Graph.hpp"
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

        if (file.is_open()){
            Graph *a = new Graph(file);
            a->print_graph();
        }
        else
            cout << "Erro ao abri o arquivo" << endl;
        // menu();
        file.close();
    }
    return 0;
}
