#include <iostream>
#include <string>
#include "header.h"

int main(){

	std::string line;
	Graph graph;

	while(getline(std::cin, line)){
        if (line.substr(0, 1) == "i"){
            std::string name = line.substr(2);
            graph.insert(name);
        }

        else if (line.substr(0, 2) == "s "){
            std::string name = line.substr(2);
            graph.search(name);
        }

        else if (line.substr(0, 2) == "d "){
            int pos = (line.substr(2)).find(";");
            std::string name1 = line.substr(2, pos);
            std::string name2 = line.substr(pos+3);
            graph.direct_distance(name1, name2);
        }

        else if (line.substr(0, 4) == "setd"){
            int pos = (line.substr(5)).find(";");
            std::string name1 = line.substr(5, pos);
            std::string line1 = line.substr(pos+6);
            pos = line1.find(";");
            std::string name2 = line1.substr(0, pos);
            double x = std::stod(line1.substr(pos+1));

            graph.set_distance(name1, name2, x);
        }

        else if (line.substr(0, 6) == "degree"){
            std::string name = line.substr(7);
            graph.find_degree(name);
        }

        else if (line.substr(0, 11) == "graph_nodes"){
            graph.graph_nodes();
        }

        else if (line.substr(0, 11) == "graph_edges"){
            graph.graph_edges();
        }

        else if (line.substr(0, 10) == "shortest_d"){
            int pos = (line.substr(11)).find(";");
            std::string name1 = line.substr(11, pos);
            std::string name2 = line.substr(pos+12);
            graph.shortest_distance(name1, name2);
        }

        else if (line.substr(0, 5) == "clear"){
            graph.clear_graph();
        }

        else if (line.substr(0, 10) == "print_path"){
            int pos = (line.substr(11)).find(";");
            std::string name1 = line.substr(11, pos);
            std::string name2 = line.substr(pos+12);
            graph.print_pathway(name1, name2);
        }
	}
	return 0;
}