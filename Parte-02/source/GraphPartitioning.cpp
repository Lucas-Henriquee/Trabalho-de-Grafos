#include "../include/Graph.hpp"
#include "../include/GraphPartitioning.hpp"
#include "../include/SubGraph.hpp"
#include "../include/defines.hpp"

typedef struct
{
    int subgraph;
    float gap_alteration = 0;
    Node *node;
} GapAlteration;

float greedy(Graph *g, vector<SubGraph *> &subgraphs, float alpha)
{
    float min_weight = g->get_first_node()->_weight;
    float max_weight = g->get_first_node()->_weight;
    srand(time(NULL));

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
    size_t n;
    do{
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
            position = rand() % (int)(ceil(alpha * gap_alterations.size()));
        subgraphs[gap_alterations[position].subgraph]->add_node(gap_alterations[position].node->_id, gap_alterations[position].node->_weight);
        for(Edge* aux_edge = g->find_node(gap_alterations[position].node->_id)->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
            if(subgraphs[gap_alterations[position].subgraph]->find_node(aux_edge->_target->_id) != NULL)
                subgraphs[gap_alterations[position].subgraph]->add_edge(gap_alterations[position].node->_id, aux_edge->_target->_id);
    }while(n < g->get_num_nodes() - 1);
    float gap_total = 0;
    for (size_t i = 0; i < g->get_num_subgraphs(); i++)
    {
        if (!subgraphs[i]->is_connected_subgraph())
            return -1;
        gap_total += subgraphs[i]->get_gap();
    }
    return gap_total;
}


void select_algorithm(Graph *g, char algorithm)
{
    vector<float> alphas;
    switch (algorithm)
    {
    case '0':
        greedy_partitioning(g);
        break;
    case '1':
        cout << "Digite o alpha: ";
        float alpha;
        do
            cin >> alpha;
        while (alpha < 0 || alpha > 1);
        randomized_greedy_partitioning(g, alpha);
        break;
    case '2':
        cout << "Digite o número de alphas: ";
        size_t n;
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            cout << "Digite o alpha " << i + 1 << ": ";
            float alpha;
            do
                cin >> alpha;
            while (alpha < 0 || alpha > 1);
            alphas.push_back(alpha);
        }
        reactive_randomized_greedy_partitioning(g, alphas);
        break;
    default:
        cout << "Algoritmo inválido" << endl;
        break;
    }
}

void greedy_partitioning(Graph *g)
{
    float alpha = 0;
    vector<SubGraph *> subgraphs;
    float gap = greedy(g, subgraphs, alpha);
    if (gap == -1)
    {
        cout << "Partição inválida" << endl;
        return;
    }
    cout << "GAP total: " << gap << endl;
}

void randomized_greedy_partitioning(Graph *g, float alpha)
{
    vector<float> gaps;
    for(int i = 0; i < 10; i++)
    {
        vector<SubGraph *> subgraphs;
        sleep(1);
        float gap = greedy(g, subgraphs, alpha);
        if (gap == -1)
        {
            cout << "Partição inválida" << endl;
            return;
        }
        cout << "GAP total: " << gap << endl;
        gaps.push_back(gap);
    }
    float mean_gap = 0;
    for (size_t i = 0; i < gaps.size(); i++)
        mean_gap += gaps[i];
    mean_gap /= gaps.size();
    cout << "Média dos GAPs: " << mean_gap << endl;
}

void reactive_randomized_greedy_partitioning(Graph *g, vector<float> alphas)
{
    vector<float> mean_gaps;
    for (size_t i = 0; i < alphas.size(); i++)
    {
        vector<float> gaps;
        for (int j = 0; j < 10; j++)
        {
            vector<SubGraph *> subgraphs;
            sleep(1);
            float gap = greedy(g, subgraphs, alphas[i]);
            if (gap == -1)
            {
                cout << "Partição inválida" << endl;
                return;
            }
            cout << "GAP total com alpha " << alphas[1] <<": " << gap << endl;
            gaps.push_back(gap);
        }
        float mean_gap = 0;
        for (size_t i = 0; i < gaps.size(); i++)
            mean_gap += gaps[i];
        mean_gap /= gaps.size();
        cout << "Média dos GAPs com alpha " << alphas[i] << ": " << mean_gap << endl;
        mean_gaps.push_back(mean_gap);
    }
    float best_alpha = alphas[0];
    for (size_t i = 0; i < mean_gaps.size(); i++)
        if (mean_gaps[i] < mean_gaps[i - 1])
            best_alpha = alphas[i]; 
    cout << "Melhor alpha: " << best_alpha << endl;
}
