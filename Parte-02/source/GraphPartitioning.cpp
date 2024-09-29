#include "../include/Graph.hpp"
#include "../include/GraphPartitioning.hpp"
#include "../include/SubGraph.hpp"
#include "../include/defines.hpp"

ostringstream output_buffer;

typedef struct
{
    int subgraph;
    float gap_alteration = 0;
    Node *node;
} GapAlteration;

void print_execution_time(clock_t start, clock_t end)
{
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    output_buffer << "Tempo de execução: " << fixed << time_taken << setprecision(5) << "s" << endl;
}

vector<SubGraph*> constructive_phase(Graph *g, float alpha)
{
    vector<SubGraph *> subgraphs;
    float min_weight = g->get_first_node()->_weight;
    float max_weight = g->get_first_node()->_weight;

    for (Node* aux_node = g->get_first_node(); aux_node != NULL; aux_node = aux_node->_next_node)
    {
        if (min_weight > aux_node->_weight)
            min_weight = aux_node->_weight;
        if (max_weight < aux_node->_weight)
            max_weight = aux_node->_weight;
    }
    float max_gap_for_subgraph = (max_weight - min_weight)/(g->get_num_subgraphs() - 1);
    int subgraph = 0;
    for (Node* aux_node = g->get_first_node(); aux_node != NULL; aux_node = aux_node->_next_node)
    {
        // Starting n subgraphs with one node
        if(aux_node->_weight >= min_weight + subgraph * max_gap_for_subgraph)
        {
            SubGraph* sub_g = new SubGraph();
            subgraph++;
            sub_g->add_node(aux_node->_id, aux_node->_weight);
            subgraphs.push_back(sub_g);
        }
    }

    // Adding a new node to each subgraph
    for(size_t i = 0; i < g->get_num_subgraphs(); i++)
    {
        Node* aux_node_s = subgraphs[i]->get_first_node();
        Edge* aux_edge = g->find_node(aux_node_s->_id)->_first_edge;
        float min_gap = abs(aux_node_s->_weight - aux_edge->_target->_weight);
        Edge* edge_min_gap = aux_edge;
        for(; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
            if(min_gap > abs(aux_edge->_target->_weight - aux_node_s->_weight))
            {
                min_gap = abs(aux_edge->_target->_weight - aux_node_s->_weight);
                edge_min_gap = aux_edge;
            }
        subgraphs[i]->add_node(edge_min_gap->_target->_id, edge_min_gap->_target->_weight);
        subgraphs[i]->add_edge(aux_node_s->_id, edge_min_gap->_target->_id);
    }
    
    // Adding the remaining nodes to the subgraphs
    size_t n = 0;
    while (n < g->get_num_nodes() - 1)
    {
        n = 0;
        vector<GapAlteration> gap_alterations;
        auto cmp = [](GapAlteration a, GapAlteration b) { return a.gap_alteration < b.gap_alteration; };
        for(size_t i = 0; i < g->get_num_subgraphs(); i++)
        {
            vector<bool> in_gap_alterations(g->get_num_nodes(), false);       
            n += subgraphs[i]->get_num_nodes();
            for (Node *aux_node = subgraphs[i]->get_first_node(); aux_node != NULL; aux_node = aux_node->_next_node)
                for (Edge* aux_edge = g->find_node(aux_node->_id)->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
                {
                    bool in_any_subgraph = false;
                    for (size_t j = 0; j < g->get_num_subgraphs(); j++)
                        if(subgraphs[j]->find_node(aux_edge->_target->_id) != NULL)
                        {
                            in_any_subgraph = true;
                            break;
                        }
                    if(in_any_subgraph)
                        continue;
                    if(!in_gap_alterations[aux_edge->_target->_id - 1])
                    {
                        in_gap_alterations[aux_edge->_target->_id - 1] = true;
                        GapAlteration gap_alteration_node;
                        gap_alteration_node.subgraph = i;
                        gap_alteration_node.node = aux_edge->_target;
                        if(aux_edge->_target->_weight <= subgraphs[i]->get_min_weight())
                            gap_alteration_node.gap_alteration = abs(subgraphs[i]->get_min_weight() - aux_edge->_target->_weight);
                        if(aux_edge->_target->_weight > subgraphs[i]->get_max_weight())
                            gap_alteration_node.gap_alteration = abs(subgraphs[i]->get_max_weight() - aux_edge->_target->_weight);
                        gap_alterations.push_back(gap_alteration_node);
                    }
                }
        }
        sort(gap_alterations.begin(), gap_alterations.end(), cmp);
        size_t position = 0;
        if(alpha != 0)
            position = rand() % int(ceil(alpha * gap_alterations.size()));
        subgraphs[gap_alterations[position].subgraph]->add_node(gap_alterations[position].node->_id, gap_alterations[position].node->_weight);
        for(Edge* aux_edge = g->find_node(gap_alterations[position].node->_id)->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
            if(subgraphs[gap_alterations[position].subgraph]->find_node(aux_edge->_target->_id) != NULL)
                subgraphs[gap_alterations[position].subgraph]->add_edge(gap_alterations[position].node->_id, aux_edge->_target->_id);
    }
    return subgraphs;
}

void local_search(Graph *g, vector<SubGraph *> &subgraphs)
{
    while(true)
    {
        vector<GapAlteration> gap_alterations;
        auto cmp = [](GapAlteration a, GapAlteration b) { return a.gap_alteration < b.gap_alteration; };
        for(size_t i = 0; i < subgraphs.size(); i++)
        {
            SubGraph* aux_subgraph = new SubGraph();
            for(Node* aux_node = subgraphs[i]->get_first_node(); aux_node != NULL; aux_node = aux_node->_next_node)
                aux_subgraph->add_node(aux_node->_id, aux_node->_weight);
            for(Edge* aux_edge = g->find_node(aux_subgraph->get_first_node()->_id)->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
                if(subgraphs[i]->find_node(aux_edge->_target->_id) != NULL)
                    aux_subgraph->add_edge(aux_subgraph->get_first_node()->_id, aux_edge->_target->_id);
            if(aux_subgraph->get_num_nodes() <= 2)
                continue;
            if(!aux_subgraph->is_connected_subgraph())
                continue;
            for(Node* aux_node = subgraphs[i]->get_first_node(); aux_node != NULL; aux_node = aux_node->_next_node)
            {
                for(Edge* aux_edge = g->find_node(aux_node->_id)->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
                {
                    for (size_t j = 0; j < subgraphs.size(); j++)
                    {
                        if(i == j)
                            continue;
                        if(subgraphs[i]->get_num_nodes() <=2)
                            break;
                        if(subgraphs[j]->find_node(aux_edge->_target->_id) != NULL)
                        {
                            GapAlteration gap_alteration;
                            gap_alteration.subgraph = j;
                            gap_alteration.node = aux_node;
                            float actualsubgraph_gap = aux_subgraph->get_gap();
                            float othersubgraph_gap = subgraphs[j]->get_gap();
                            aux_subgraph->remove_node(aux_node->_id);
                            subgraphs[j]->add_node(aux_node->_id, aux_node->_weight);
                            float actualsubgraph_gap_after = aux_subgraph->get_gap();
                            float othersubgraph_gap_after = subgraphs[j]->get_gap();
                            float gap_alteration_value = actualsubgraph_gap_after - actualsubgraph_gap + othersubgraph_gap_after - othersubgraph_gap;
                            if(gap_alteration_value < 0 && aux_subgraph->is_connected_subgraph() && aux_subgraph->get_num_nodes() >= 2)
                            {
                                gap_alteration.gap_alteration = gap_alteration_value;
                                gap_alterations.push_back(gap_alteration);
                            }
                            subgraphs[j]->remove_node(aux_node->_id);
                            aux_subgraph->add_node(aux_node->_id, aux_node->_weight);
                            for(Edge* aux_edge_2 = g->find_node(aux_node->_id)->_first_edge; aux_edge_2 != NULL; aux_edge_2 = aux_edge_2->_next_edge)
                                if(aux_subgraph->find_node(aux_edge_2->_target->_id) != NULL)
                                    aux_subgraph->add_edge(aux_node->_id, aux_edge_2->_target->_id);
                        }
                    }
                }
            }
        }
        if(gap_alterations.size() > 0)
        {
            size_t to_remove = 0;
            sort(gap_alterations.begin(), gap_alterations.end(), cmp);
            for(size_t i = 0; i < subgraphs.size(); i++)
                if(subgraphs[i]->find_node(gap_alterations[0].node->_id) != NULL)
                {
                    to_remove = i;
                    break;
                }
            subgraphs[gap_alterations[0].subgraph]->add_node(gap_alterations[0].node->_id, gap_alterations[0].node->_weight);
            for(Edge* aux_edge = g->find_node(gap_alterations[0].node->_id)->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
                if(subgraphs[gap_alterations[0].subgraph]->find_node(aux_edge->_target->_id) != NULL)
                    subgraphs[gap_alterations[0].subgraph]->add_edge(gap_alterations[0].node->_id, aux_edge->_target->_id);
            subgraphs[to_remove]->remove_node(gap_alterations[0].node->_id);
        }
        else
            break;
    }
}

float greedy(Graph *g, vector<SubGraph *> &subgraphs)
{
    subgraphs = constructive_phase(g, 0);
    float gap_total = 0;
    for(size_t i = 0; i < subgraphs.size(); i++)
        if(!subgraphs[i]->is_connected_subgraph())
            return -1;
    for (size_t i = 0; i < subgraphs.size(); i++)
        gap_total += subgraphs[i]->get_gap();
    return gap_total;
}

float randomized_greedy(Graph *g, vector<SubGraph *> &subgraphs, float alpha)
{
    float best_gap = FLT_MAX;
    for(size_t n = 0; n < 10; n++)
    {
        subgraphs = constructive_phase(g, alpha);     
        local_search(g, subgraphs);
        bool connected = true;
        for(size_t i = 0; i < subgraphs.size(); i++)
            if(!subgraphs[i]->is_connected_subgraph())
                connected = false;
        float gap_total = 0;
        for (size_t i = 0; i < subgraphs.size(); i++)
            gap_total += subgraphs[i]->get_gap();
        if(!connected)
        {
            n--;
            continue;
        }
        if(gap_total < best_gap)
            best_gap = gap_total;
    }
    return best_gap;
}

float reactive_randomized_greedy(Graph *g, vector<SubGraph *> &subgraphs, vector<float> alphas)
{
    float best_gap = FLT_MAX;
    vector<float> probs;
    vector<float> total_gap_alpha;
    vector<size_t> n(alphas.size(), 0);
    for(size_t i = 0; i <= alphas.size(); i++)
    {
        probs.push_back(1/alphas.size());
        total_gap_alpha.push_back(0);
    }
    for(size_t i = 0; i < 100; i++)
    {
        float chance = (rand() % 100)/100;
        float accumuled_chance = 0;
        float alpha;
        for (size_t j = 0; j < probs.size(); i++)
        {
            if(accumuled_chance >= chance)
            {
                alpha = alphas[j];
                break;
            }
            accumuled_chance += probs[j];
        }
        bool connected = true;
        for(size_t i = 0; i < subgraphs.size(); i++)
            if(!subgraphs[i]->is_connected_subgraph())
                connected = false;
        subgraphs = constructive_phase(g, alpha);
        local_search(g, subgraphs);
        float gap_total = 0;
        for (size_t i = 0; i < subgraphs.size(); i++)
            gap_total += subgraphs[i]->get_gap();
        total_gap_alpha[find(alphas.begin(), alphas.end(), alpha) - alphas.begin()] += gap_total;
        n[find(alphas.begin(), alphas.end(), alpha) - alphas.begin()] += 1;
        if(!connected)
        {
            i--;
            continue;
        }
        if(gap_total < best_gap)
            best_gap = gap_total; 
        if(i % 10 == 0)
        {
            vector<float> mean_gap;
            vector<float> q;
            float sum_q = 0;
            for(size_t j = 0; j < alphas.size(); j++)
            {
                mean_gap.push_back(total_gap_alpha[j]/n[j]);
                q.push_back(best_gap/mean_gap[j]);
                sum_q += q[j];
            }
            for(size_t j = 0; j < alphas.size(); j++)
                probs[j] = q[j]/sum_q;
        }
    }
    return best_gap;
}


void select_algorithm(Graph *g, char algorithm, string filename, string file_exit)
{
    output_buffer << "-------------------------------------------------------------\n\n";
    output_buffer << "Instância: " << filename << endl;
    output_buffer << "Número de subgrafos: " << g->get_num_subgraphs() << endl;

    switch (algorithm)
    {
    case '0':
        output_buffer << "Tipo de algoritmo: Greedy Partitioning\n\n";
        greedy_partitioning(g);
        break;

    case '1':
        output_buffer << "Tipo de algoritmo: Randomized Greedy Partitioning\n\n";
        output_buffer << "Alphas: 0.05, 0.2, 0.3, 0.45, 0.5\n\n";
        {
            float alphas[] = {0.05, 0.2, 0.3, 0.45, 0.5};
            for (size_t i = 0; i < 5; i++)
                randomized_greedy_partitioning(g, alphas[i]);
        }
        break;

    case '2':
        output_buffer << "Tipo de algoritmo: Reactive Randomized Greedy Partitioning\n\n";
        output_buffer << "Alphas: 0.05, 0.2, 0.3, 0.45, 0.5\n\n";
        {
            float alphas[] = {0.05, 0.2, 0.3, 0.45, 0.5};
            vector<float> alphas_vector;
            for (size_t i = 0; i < 5; i++)
                alphas_vector.push_back(alphas[i]);
            reactive_randomized_greedy_partitioning(g, alphas_vector);
        }
        break;

    default:
        cout << "Algoritmo inválido" << endl;
        break;
    }

    cout << output_buffer.str();
    print_greedy(file_exit);
}

void greedy_partitioning(Graph *g)
{
    clock_t start = clock();
    vector<SubGraph *> subgraphs;
    float gap = greedy(g, subgraphs);
    if (gap == -1)
    {
        cout << "Partição inválida" << endl;
        return;
    }
    output_buffer << "GAP total: " << gap << endl;
    cout << "Número de subgrafos: " << subgraphs.size() << endl;
    clock_t end = clock();
    print_execution_time(start, end);
}

void randomized_greedy_partitioning(Graph *g, float alpha)
{
    clock_t start = clock();
    srand(time(NULL));
    vector<SubGraph *> subgraphs;
    float gap = randomized_greedy(g, subgraphs, alpha);
    if (gap == -1)
    {
        cout << "Partição inválida" << endl;
        return;
    }
    output_buffer << "GAP total: " << gap << endl;
    clock_t end = clock();
    print_execution_time(start, end);
    
}

void reactive_randomized_greedy_partitioning(Graph *g, vector<float> alphas)
{
    clock_t start = clock();
    srand(time(NULL));
    vector<SubGraph *> subgraphs;
    float gap = reactive_randomized_greedy(g, subgraphs, alphas);
    if (gap == -1)
    {
        cout << "Partição inválida" << endl;
        return;
    }
    output_buffer << "GAP total: " << gap << endl;
    clock_t end = clock();
    print_execution_time(start, end);
}

void print_greedy(string file_exit)
{
    ifstream check_file(file_exit);
    bool file_exists = check_file.good();

    // Abrindo o arquivo de saída.
    ofstream output_file(file_exit, ios::out | ios::app);

    // Verificando se o arquivo foi aberto.
    if (output_file.is_open())
    {

        // Caso o arquivo não exista, escrevendo o grafo no arquivo.
        if (!file_exists)
        {
            output_file << "O Minimum Gap Graph Partitioning Problem (MGGPP):\n\n" << endl;
        }

        // Escrevendo a saída no arquivo.
        output_buffer << "\n";
        output_file << output_buffer.str();
        output_buffer.str("");
        output_buffer.clear();
        cout << "Saída salva no arquivo: " << file_exit << endl;

        // Fechando o arquivo.
        output_file.close();
    }

    // Caso contrário.
    else
        cout << "Erro ao abrir o arquivo para salvar a saída." << endl;
}