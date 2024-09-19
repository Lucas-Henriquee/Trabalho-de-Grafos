#include "../include/Graph.hpp"
#include "../include/GraphPartitioning.hpp"
#include "../include/SubGraph.hpp"
#include "../include/defines.hpp"

typedef struct
{
    int subgraph;
    float gap_alteration;
    Node* node;
} GapAlteration;


void select_algorithm(Graph *g, char algorithm)
{
    switch (algorithm)
    {
    case '0':
        greedy_partitioning(g);
        break;
    case '1':
        randomized_greedy_partitioning(g);
        break;
    case '2':
        reactive_randomized_greedy_partitioning(g);
        break;
    default:
        cout << "Algoritmo inválido" << endl;
        break;
    }
}

void greedy_partitioning(Graph *g)
{
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

    SubGraph* *subgraphs = new SubGraph*[g->get_num_subgraphs()];
    int subgraph = 0;
    for (Node* aux_node = g->get_first_node(); aux_node != NULL; aux_node = aux_node->_next_node)
    {
        // Starting a n subgraphs with one node
        if(aux_node->_weight >= min_weight + subgraph * max_gap_for_subgraph)
        {
            SubGraph* sub_g = new SubGraph();
            subgraph++;
            sub_g->add_node(aux_node->_id, aux_node->_weight);
            subgraphs[subgraph] = sub_g;
        }
    }

    // Adding a new node to each subgraph
    for(size_t i = 0; i < g->get_num_subgraphs(); i++)
    {
        Node* aux_node_s = subgraphs[i]->get_first_node();
        float min_gap = abs(aux_node_s->_first_edge->_target->_weight - aux_node_s->_weight);
        Edge* edge_min_gap = aux_node_s->_first_edge;
        for(Edge* aux_edge = g->find_node(aux_node_s->_id)->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
        {
            if(min_gap > abs(aux_edge->_target->_weight - aux_node_s->_weight))
            {
                min_gap = abs(aux_edge->_target->_weight - aux_node_s->_weight);
                edge_min_gap = aux_edge;
            }
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
        subgraphs[gap_alterations[0].subgraph]->add_node(gap_alterations[0].node->_id, gap_alterations[0].node->_weight);
        for(Edge* aux_edge = g->find_node(gap_alterations[0].node->_id)->_first_edge; aux_edge != NULL; aux_edge = aux_edge->_next_edge)
            if(subgraphs[gap_alterations[0].subgraph]->find_node(aux_edge->_target->_id) != NULL)
                subgraphs[gap_alterations[0].subgraph]->add_edge(gap_alterations[0].node->_id, aux_edge->_target->_id);
    }while(n < g->get_num_nodes());
    float gap_total = 0;
    for (size_t i = 0; i < g->get_num_subgraphs(); i++)
        gap_total += subgraphs[i]->get_gap();
    cout << "Gap total: " << gap_total << endl;
}

void randomized_greedy_partitioning(Graph *g)
{
}

void reactive_randomized_greedy_partitioning(Graph *g)
{
}
