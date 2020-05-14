#include <iostream>
#include <vector>

//This class represents the nodes in a linked list data structure. These nodes are the cities represented in a graph.
class Node {
    public:
        Node* next;
        std::string city_name;
        double weight;

        Node(std::string name, double pp_weight);
};

//This class represents a linked list data structure. Linked lists are needed to represent adjacency lists, which define a graph.
class LinkedList{
    public:
        Node* head;
        Node* tail;
        int degree;

        //Dijsktra's algorithm variables
        std::string parent;
        double sd;
        bool visited;

        LinkedList();
};

//This class represents a graph data structure
class Graph{
    public:
        std::vector< LinkedList* > graph_array;
        int nodes;
        int edges;
		int visited_nodes;

        Graph();
        ~Graph();
        void insert(std::string name);
        void set_distance(std::string name1, std::string name2, double d);
        void search(std::string name);
        void graph_nodes();
        void graph_edges();
        void find_degree(std::string name);
        void direct_distance(std::string name1, std::string name2);
        void shortest_distance(std::string name1, std::string name2);
        void print_pathway(std::string name1, std::string name2);
        void clear_graph();
};

