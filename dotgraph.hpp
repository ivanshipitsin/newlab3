#ifndef DOTGRAPH_HPP
#define DOTGRAPH_HPP
#include <fstream>
#include "graph.hpp"

struct Point;

class DOT_TYPE {
    private:
    std::fstream file;
    public:

    DOT_TYPE(std::string filename) : file(filename + ".dot" , std::ios_base::out) {}
    
    ~DOT_TYPE() {
        file.close();
    }

    void createGraph(Graph<Point> & g) {
        file << "graph graphname " << " {" << std::endl;
        int len = g.size();
        for(int i = 0; i < len; i++){
            file << "\t" << i << " [label=\"" << i << " (" << g.Get(i).x << "," << g.Get(i).y << ")\"];" << std::endl;
        }

        std::vector<bool> pip(len, true);
        for(int i = 0; i < len; i++){
            std::vector<neibVert> neib = g.neib(i);
            for(int j = 0; j < neib.size(); j++){
                if(pip[neib[j].numb])
                    file << "\t" << i << "--" << neib[j].numb << " [label=" << neib[j].weight << "]" << std::endl;
            }
            pip[i] = false;
        }



        file << "}";
    }
};
#endif