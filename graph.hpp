#ifndef _GRAPH_HPP
#define _GRAPH_HPP
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct neibVert {
    int numb;
    int weight;
};

template<typename Tnode>
class Graph{
    private:
    std::vector < std::vector < neibVert > > list;
    std::vector < Tnode> nodelist;

    public:
    Graph(){}
    Graph(int _size): nodelist(_size), list(_size){}

    std::vector < neibVert> neib(int index) {
        if(list.size() <= index) {
            return std::vector<neibVert> ();
        } 
        return list[index];
    }

    Tnode Get(int index) {
        if(nodelist.size() <= index) {
            return Tnode ();
        }
        return nodelist[index];
    }

    int searchNode(Tnode  serch) {
        for(int i = 0; i < nodelist.size(); i++) {
            if(nodelist[i] == serch) {
                return i;
            }
        }
        return -1;
    }

    void Set(int index, Tnode & set){
        if(nodelist.size() <= index){
            return;
        }
        nodelist[index] = set;
    }

    void SetNeibor(int index, std::vector<neibVert> neibo){
        list[index] = neibo;
    }

    int addNode(Tnode & data, std::vector<neibVert> neibor){
        nodelist.push_back(data);
        for (int i = 0; i < neibor.size(); i++){
            if(list.size() <= neibor[i].numb){
                throw "Error neibor list";
            }
            list[neibor[i].numb].push_back({nodelist.size() - 1, neibor[i].weight});
        }
        list.push_back(neibor);

        return nodelist.size() - 1;
    }

    std::vector<int> WS(int start){
        std::queue<int> qu;
        std::vector<int> step(nodelist.size(), -1);
        if(nodelist.size() <= start){
            return std::vector<int> ();
        }
        step[start] = start;
        qu.push(start);
        while(!qu.empty()){
            int p = qu.front();
            qu.pop();
            for(int i = 0; i < list[p].size(); i++){
                if(step[list[p][i].numb] == -1){
                    step[list[p][i].numb] = p;
                    qu.push(list[p][i].numb);
                }
            }
        }

        return step;
    }

    std::vector<int> Dijkstra(int n){
        int len = nodelist.size();
        std::vector<bool> u(len, false);
        std::vector<int>  d(len, std::numeric_limits<int>::max());
        std::vector<int>  p(len, -1);
        d[n] = 0;
        p[n] = n;
        for(int i = 0; i < len; i++){
            int v = -1;
            for(int j = 0; j < len; j++){
                if(u[j]){
                    continue;
                }
                if(v == -1 || d[j] < d[v]){
                    v = j;
                }
            }
            if (d[v] == std::numeric_limits<int>::max())
			    break;
            u[v] = true;
            int dlen = list[v].size();
            for(int j = 0; j < dlen; j++){
                if(d[ list[v][j].numb ] > d[v] + list[v][j].weight){
                    d[ list[v][j].numb ] = d[v] + list[v][j].weight;
                    p[ list[v][j].numb ] = v;
                }
            }
        }

        return p;

    }

    int size(){
        return nodelist.size();
    }

    void DEBUG_INFO(){
        for(int i = 0; i < list.size(); i++){
            std::cout << i << ": " ;
            for(int j = 0; j < list[i].size(); j++){
                std::cout << list[i][j].numb << "(" << nodelist[list[i][j].numb] << ") ," ;
            }
            std::cout << std::endl;
        }
    }


};
#endif