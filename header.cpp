#include <iostream>
#include <vector>
#include "header.h"

//Node class constructor
Node::Node(std::string name, double pp_weight){
    city_name = name;
    weight = pp_weight;
    next = NULL;
}

//LinkedList class constructor
LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
    degree = 0;

    parent = "";
    sd = __DBL_MAX__;
    visited = false;
}

//Graph class constructor
Graph::Graph(){
    nodes = 0;
    edges = 0;
	visited_nodes = 0;
}

//Graph class destructor
Graph::~Graph(){
    Node* temp;
    Node* temp1;

    for (int i = 0; i < graph_array.size(); i++){
        temp = graph_array.at(i)->head;
        temp1 = temp;

        while (temp != NULL){
            temp = temp->next;
            delete temp1;
            temp1 = temp; 
        }

        graph_array.at(i)->head = NULL;
        graph_array.at(i)->tail = NULL;

        delete graph_array.at(i);
    }

    graph_array.erase(graph_array.begin(), graph_array.end());
	graph_array.shrink_to_fit();
}

//Inserts a node to a graph
void Graph::insert(std::string name){
    bool failure = false;

    for (int i = 0; i < graph_array.size(); i++){
        if(graph_array.at(i)->head->city_name == name){
            std::cout << "failure" << std::endl;
            failure = true;
            break;
        }
    }

    if (failure == false){
        LinkedList* ll = new LinkedList;
        Node* n = new Node(name, 0);

        ll->head = n;
        ll->tail = n;

        graph_array.push_back(ll);
        std::cout << "success" << std::endl;
        nodes++; 
    }
}

//Assigns a weight (distance) to the edge connecting two nodes (cities)
void Graph::set_distance(std::string name1, std::string name2, double d){
    bool found1 = false;
    bool found2 = false;
    Node* name1_ll_head;
    Node* name2_ll_head;

    Node* temp;
    Node* temp1;

    bool name1_modify = false;
    bool name2_modify = false;

    int i1;
    int i2;

    for (i1 = 0; i1 < graph_array.size(); i1++){
        if (name1 == graph_array.at(i1)->head->city_name){
            found1 = true;
            name1_ll_head = graph_array.at(i1)->head;
            break;
        }
    }

    for (i2 = 0; i2 < graph_array.size(); i2++){
        if (name2 == graph_array.at(i2)->head->city_name){
            found2 = true;
            name2_ll_head = graph_array.at(i2)->head;
            break;
        }
    }

    if ((name1 == name2) || (d <= 0) || (found1 == false)  || (found2 == false)){
        std::cout << "failure" << std::endl;
    }

    else{
        //First
        temp = name1_ll_head;
        Node* temp2;
        Node* temp3;

        while(temp != NULL){
            if (temp->city_name == name2){
                name1_modify = true;
                break;
            }
            temp = temp->next;
        }

        if (name1_modify == true){
            //Modify
            temp->weight = d;
        }
        else {
            temp2 = new Node(name2, d);
            graph_array.at(i1)->tail->next = temp2;
            graph_array.at(i1)->tail = temp2;
            //Increment edges here because we added a node to the linked list   
            edges++;                                 
            graph_array.at(i1)->degree++;
        }

        //Second
        temp1 = name2_ll_head;
        while(temp1 != NULL){
            if (temp1->city_name == name1){
                name2_modify = true;
                break;
            }
            temp1 = temp1->next;
        }

        if (name2_modify == true){
            //Modify
            temp1->weight = d;
        }
        else {
            temp3 = new Node(name1, d);
            graph_array.at(i2)->tail->next = temp3;
            graph_array.at(i2)->tail = temp3;
            graph_array.at(i2)->degree++;
        }

        //Printing
        std::cout << "success" << std::endl;
    }
}

//Searches for a given city in the graph
void Graph::search(std::string name){
    bool found = false;

    for (int i = 0; i < graph_array.size(); i++){
        if (name == graph_array.at(i)->head->city_name){
            found = true;
            break;
        }
    }

    if (found == false){
        std::cout << "not found" << std::endl;
    }
    else{
        std::cout << "found " << name << std::endl;
    }
}

//Prints the number of nodes in the graph
void Graph::graph_nodes(){
    std::cout << "number of nodes " << nodes << std::endl;
}

//Prints the number of edges (roads) in the graph
void Graph::graph_edges(){
    std::cout << "number of edges " << edges << std::endl;
}

//Prints the degree of a given city
void Graph::find_degree(std::string name){
    bool found = false;

    for (int i = 0; i < graph_array.size(); i++){
        if (name == graph_array.at(i)->head->city_name){
            found = true;
            std::cout << "degree of " << name << " " << graph_array.at(i)->degree << std::endl;
            break;
        }
    }

    if (found == false){
        std::cout << "failure" << std::endl;
    }
}

//Prints the distance between two nodes that are directly connected to each other with an edge
void Graph::direct_distance(std::string name1, std::string name2){

    if (name1 == name2){
        std::cout << "failure" << std::endl;
        return;
    }
    
    bool found = false;
    bool found1 = false;

    Node* name1_ll_head;

    for (int i = 0; i < graph_array.size(); i++){
        if (name1 == graph_array.at(i)->head->city_name){
            found = true;
            name1_ll_head = graph_array.at(i)->head;
            break;
        }
    }

    if (found == false){
        std::cout << "failure" << std::endl;
        return;
    }

    while (name1_ll_head != NULL){
        if (name1_ll_head->city_name == name2){
            std::cout << "direct distance " << name1 << " to " << name2 << " " << name1_ll_head->weight << std::endl; 
            found1 = true;
            break;
        }
        name1_ll_head = name1_ll_head->next;
    }

    if (found1 == false){
        std::cout << "failure" << std::endl;
    }
}

//Finds the shortest distance between any two given nodes in a graph
void Graph::shortest_distance(std::string name1, std::string name2){
    bool found = false;
    bool found1 = false;
    Node* name1_ll_head;
    Node* temp;

    //Please note that the for loops and while loops below are numbered to easily refer to them in the time complexity analysis in the design document
    //for loop 1 
    for (int i = 0; i < graph_array.size(); i++){
        if (name1 == graph_array.at(i)->head->city_name){
            found = true;
            graph_array.at(i)->sd = 0;
            name1_ll_head = graph_array.at(i)->head;
            break;
        }
    }

    //trying to find name2
    if ((name1 == name2) || (found == false)){
        std::cout << "failure" << std::endl;
        return;
    }

    //while loop 1
    while (visited_nodes != nodes){
        //Find the node with the minimum shortest distance
        double minimum = __DBL_MAX__;
        Node* min_node_head_next;
        Node* min_node_head;
        LinkedList* min_ll;

        double sd_min_node;

        std::string name3;

        //for loop 2
        for (int i = 0; i < graph_array.size(); i++){
            if ((graph_array.at(i)->sd < minimum) && (graph_array.at(i)->visited == false)){
                minimum = graph_array.at(i)->sd;
                min_node_head_next = graph_array.at(i)->head->next;
                min_node_head = graph_array.at(i)->head;
                sd_min_node = graph_array.at(i)->sd;
                min_ll = graph_array.at(i);
            }
        }

        //while loop 2
        while(min_node_head_next != NULL){
            name3 = min_node_head_next->city_name;
            //for loop 3
            for(int i = 0; i < graph_array.size(); i++){
                if (graph_array.at(i)->head->city_name == name3){
                    //Edge relaxation
                    if ((graph_array.at(i)->visited == false) && (graph_array.at(i)->sd > min_node_head_next->weight + sd_min_node)){
                        graph_array.at(i)->sd = min_node_head_next->weight + sd_min_node;
                        graph_array.at(i)->parent = min_node_head->city_name;
                    }
                    break;
                }
            }
            min_node_head_next = min_node_head_next->next;
        }
        min_ll->visited = true;
        visited_nodes++;
    }

    //for loop 4
    for (int i = 0; i < graph_array.size(); i++){
        if (name2 == graph_array.at(i)->head->city_name){
            if (graph_array.at(i)->sd == __DBL_MAX__){
                std::cout << "failure" << std::endl;
            }
            else{
                std::cout << "shortest distance " << name1 << " to " << name2 << " " << graph_array.at(i)->sd << std::endl;
            }
            found1 = true;
            break;
        }
    }

    if (found1 == false){
        std::cout << "failure" << std::endl;
        return;
    }
}

//Prints the pathway between two nodes such that the sum of the distances of its constituent edges is minimized
void Graph::print_pathway(std::string name1, std::string name2){
    bool found;
    bool found1;
    std::vector<std::string> names;
    std::string temp = name2;
    LinkedList* ll;

    //Please note that the for loops and while loops below are numbered to easily refer to them in the time complexity analysis in the design document
    //for loop 1
    for (int i = 0; i < graph_array.size(); i++){
        if (name1 == graph_array.at(i)->head->city_name){
            found = true;
            break;
        }
    }

    if ((name1 == name2) || (found == false)){
        std::cout << "failure" << std::endl;
        return;
    }

    //for loop 2
    for (int i = 0; i < graph_array.size(); i++){
        if (name2 == graph_array.at(i)->head->city_name){
            ll = graph_array.at(i);
            names.push_back(name2);
            found1 = true;
            break;
        }
    }

    if (found1 == false){
        std::cout << "failure" << std::endl;
        return;
    }

    //while loop 1
    while(temp != name1){
        if (ll->sd == __DBL_MAX__){
            std::cout << "failure" << std::endl;
            return;
        }
        else{
            names.push_back(ll->parent);
            temp = ll->parent;
        }

        //for loop 3
        for (int i = 0; i < graph_array.size(); i++){
            if (graph_array.at(i)->head->city_name == temp){
                ll = graph_array.at(i);
                break;
            }
        }
    }

    //for loop 4
    for (int i = names.size() - 1; i >= 1; i--){
        std::cout << names.at(i) << " ";
    }

    std::cout << names.at(0) << std::endl;
    return;
}

//Deletes all the nodes and edges from the graph
void Graph::clear_graph(){
    nodes = 0;
    edges = 0;
	std::cout << "success" << std::endl;
}