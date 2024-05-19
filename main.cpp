#include "include/Graph.hpp"
#include <thread>
#include <chrono>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

void menu(string file_exit);
void transitive_direct(size_t vertex);
void transitive_indirect(size_t vertex);
void dijkstra_shortest_path(size_t vertex_1, size_t vertex_2);
void floyd_shortest_path(size_t vertex_1, size_t vertex_2);
void prim_minimum_generating_tree(size_t *vertices, size_t size);
void kruskal_minimum_generating_tree(size_t *vertices, size_t size);
void deep_walking(size_t vertex);
void properties_graph();
void articulation_vertices();
void save_exit(string file);

ostringstream output_buffer;

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
            bool weight_edges = (string(argv[4]) == "1");
            bool weight_nodes = (string(argv[5]) == "1");

            Graph *a = new Graph(file, directed, weight_edges, weight_nodes);
            a->print_graph();
        }
        else
            cout << "Erro ao abri o arquivo" << endl;

        file.close();

        string file_exit = argv[2];

        menu(file_exit);
    }

    return 0;
}

void menu(string file_exit)
{

    int i = -1;
    size_t size, vertex_1, vertex_2;

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

        system("clear||cls");

        switch (i)
        {
        case 1:
        {

            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            transitive_direct(vertex_1);
            break;
        }
        case 2:
        {
            cout << "\n  Digite o ID do vértice: ";
            cin >> vertex_1;
            transitive_indirect(vertex_1);
            break;
        }
        case 3:
        {
            cout << "\n  Digite os IDs dos vértices (origem destino): ";
            cin >> vertex_1 >> vertex_2;
            dijkstra_shortest_path(vertex_1, vertex_2);
            break;
        }
        case 4:
        {
            cout << "\n  Digite os IDs dos vértices (origem destino): ";
            cin >> vertex_1 >> vertex_2;
            floyd_shortest_path(vertex_1, vertex_2);
            break;
        }
        case 5:
        {
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
            cout << "Digite o ID do vértice: ";
            cin >> vertex_1;
            deep_walking(vertex_1);
            break;
        }
        case 8:
        {
            properties_graph();
            break;
        }
        case 9:
        {
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
                char option;
                cin >> option;

                if (option == 's')
                    save_exit(file_exit);

                output_buffer.str("");
                output_buffer.clear();
            }
        }
    } while (i != 0);

    return;
}

void transitive_direct(size_t vertex)
{
    // Implementação
    output_buffer << "Fecho Transitivo Direto para o vértice " << vertex << ": ...\n";
    cout << output_buffer.str();
}

void transitive_indirect(size_t vertex)
{
    // Implementação
    output_buffer << "Fecho Transitivo Indireto para o vértice " << vertex << ": ...\n";
    cout << output_buffer.str();
}

void dijkstra_shortest_path(size_t vertex_1, size_t vertex_2)
{
    // Implementação
    output_buffer << "Caminho Mínimo (Dijkstra) entre " << vertex_1 << " e " << vertex_2 << ": ...\n";
    cout << output_buffer.str();
}

void floyd_shortest_path(size_t vertex_1, size_t vertex_2)
{
    // Implementação
    output_buffer << "  Caminho Mínimo (Floyd) entre " << vertex_1 << " e " << vertex_2 << ": ...\n";
    cout << output_buffer.str();
}

void prim_minimum_generating_tree(size_t *vertices, size_t size)
{
    // Implementação
    output_buffer << "  Árvore Geradora Mínima (Prim) para os vértices: ";
    for (size_t i = 0; i < size; ++i)
    {
        output_buffer << vertices[i] << " ";
    }
    output_buffer << "\n";
    cout << output_buffer.str();
}

void kruskal_minimum_generating_tree(size_t *vertices, size_t size)
{
    // Implementação
    output_buffer << "  Árvore Geradora Mínima (Kruskal) para os vértices: ";
    for (size_t i = 0; i < size; ++i)
    {
        output_buffer << vertices[i] << " ";
    }
    output_buffer << "\n";
    cout << output_buffer.str();
}

void deep_walking(size_t vertex)
{
    // Implementação
    output_buffer << "  Caminhamento em Profundidade a partir do vértice " << vertex << ": ...\n";
    cout << output_buffer.str();
}

void properties_graph()
{
    // Implementação
    output_buffer << "  Propriedades do Grafo: Raio, Diâmetro, Centro, Periferia: ...\n";
    cout << output_buffer.str();
}

void articulation_vertices()
{
    // Implementação
    output_buffer << "  Vértices de Articulação do Grafo: ...\n";
    cout << output_buffer.str();
}

void save_exit(string file_exit)
{
    ofstream output_file(file_exit, ios::out | ios::app);

    if (output_file.is_open())
    {
        output_file << output_buffer.str();
        cout << "  Saída salva no arquivo: " << file_exit << endl;
        this_thread::sleep_for(chrono::seconds(2));
        output_file.close();
    }
    else
    {
        cout << "  Erro ao abrir o arquivo para salvar a saída." << endl;
    }
}