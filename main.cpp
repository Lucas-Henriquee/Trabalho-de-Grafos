#include "include/Graph.hpp"
#include <thread>
#include <chrono>
using namespace std;

void menu();
void transitive_direct(size_t vertex);
void transitive_indirect(size_t vertex);
void dijkstra_shortest_path(size_t vertex_1, size_t vertex_2);
void floyd_shortest_path(size_t vertex_1, size_t vertex_2);
void prim_minimum_generating_tree(size_t *vertices, size_t size);
void kruskal_minimum_generating_tree(size_t *vertices, size_t size);
void deep_walking(size_t vertex);
void properties_graph();
void articulation_vertices();
void save_exit();

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

        if (file.is_open())
        {
            bool directed = (string(argv[3]) == "1");
            bool weighted_edges = (string(argv[4]) == "1");
            bool weighted_nodes = (string(argv[5]) == "1");

            Graph *a = new Graph(file);
            a->print_graph();
        }
        else
            cout << "Error opening file" << endl;

        menu();

        file.close();
    }

    return 0;
}

void menu()
{

    int i = -1;
    size_t vertex_1, vertex_2;
    size_t size;

    do
    {
        system("clear||cls");
        cout << "\n\t  Menu de Operações do Grafo\n\n\n";
        cout << "  1) Fecho Transitivo Direto de um vértice" << endl;
        cout << "  2) Fecho Transitivo Indireto de um Vértice" << endl;
        cout << "  3) Caminho Mínimo entre Dois Vértices (Dijkstra)" << endl;
        cout << "  4) Caminho Mínimo entre Dois Vértices (Floyd)" << endl;
        cout << "  5) Árvore Geradora Mínima (Prim)" << endl;
        cout << "  6) Árvore Geradora Mínima (Kruskal)" << endl;
        cout << "  7) Caminhamento em Profundidade" << endl;
        cout << "  8) Propriedades do Grafo" << endl;
        cout << "  9) Vértices de Articulação" << endl;
        cout << "  0) Sair do Programa" << endl;
        cout << "\n\n  Escolha uma opção: ";

        cin >> i;

        switch (i)
        {
        case 1:
        {
            system("clear||cls");
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            transitive_direct(vertex_1);
            break;
        }
        case 2:
        {
            system("clear||cls");
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            transitive_indirect(vertex_1);
            break;
        }
        case 3:
        {
            system("clear||cls");
            cout << "\n  Digite os IDs dos vértices (origem destino): ";
            cin >> vertex_1 >> vertex_2;
            dijkstra_shortest_path(vertex_1, vertex_2);
            break;
        }
        case 4:
        {
            system("clear||cls");
            cout << "\n  Digite os IDs dos vértices (origem destino): ";
            cin >> vertex_1 >> vertex_2;
            floyd_shortest_path(vertex_1, vertex_2);
            break;
        }
        case 5:
        {
            system("clear||cls");
            cout << "\n  Digite o número de vértices no subconjunto: ";
            cin >> size;
            size_t *vertices = new size_t[size];
            cout << "\n  Digite os IDs dos vértices: ";
            for (size_t i = 0; i < size; ++i)
                cin >> vertices[i];
            prim_minimum_generating_tree(vertices, size);
            delete[] vertices;
            break;
        }
        case 6:
        {
            system("clear||cls");
            cout << "\n  Digite o número de vértices no subconjunto: ";
            cin >> size;
            size_t *vertices = new size_t[size];
            cout << "\n  Digite os IDs dos vértices: ";
            for (size_t i = 0; i < size; ++i)
            {
                cin >> vertices[i];
            }
            kruskal_minimum_generating_tree(vertices, size);
            delete[] vertices;
            break;
        }
        case 7:
        {
            system("clear||cls");
            cout << "Digite o ID do vértice: ";
            cin >> vertex_1;
            deep_walking(vertex_1);
            break;
        }
        case 8:
        {
            system("clear||cls");
            properties_graph();
            break;
        }
        case 9:
        {
            system("clear||cls");
            articulation_vertices();
            break;
        }
        case 0:
        {
            cout << "\n  Encerrando o programa..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
        default:
        {
            cout << "\n  Opção inválida! Tente novamente." << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }

            if (i != 0)
            {
                cout << "\n\n  Deseja salvar esses dados em um arquivo? (s/n): ";
                string option;
                cin >> option;
                if (option == "s")
                    save_exit();
            }
        }
    } while (i != 0);

    return;
}

void transitive_direct(size_t vertex)
{
}
void transitive_indirect(size_t vertex)
{
}
void dijkstra_shortest_path(size_t vertex_1, size_t vertex_2)
{
}
void floyd_shortest_path(size_t vertex_1, size_t vertex_2)
{
}
void prim_minimum_generating_tree(size_t *vertices, size_t size)
{
}
void kruskal_minimum_generating_tree(size_t *vertices, size_t size)
{
}
void deep_walking(size_t vertex)
{
}
void properties_graph()
{
}
void articulation_vertices()
{
}
void save_exit()
{
}