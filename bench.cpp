#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "graph.hpp"

void testWS(){
    std::fstream fin("TEST/WS.txt");
    int n = 0;
    fin >> n;

    Graph<int> g(n);
    for(int i = 0; i < n; i++){
        int v = 0;
        fin >> v;
        v--;
        int u = 0;
        std::vector<neibVert> neib;
        do{
            fin >> u;
            if(u >= 0){
                neib.push_back({u - 1, 0});
            }

        }while(u != -1);
        g.SetNeibor(v, neib);
    }

    int start, end;
    fin >> start >> end;
    std::vector<int> res = g.WS(start - 1);
    int p = res[end - 1];
    if(p == -1){
        std::cerr << "Error not found" << std::endl;
        return;
    }
    std::cout << end << " ";
    while(p != start - 1){
        std::cout << p + 1 << " ";
        p = res[p];
    }
    std::cout << start << std::endl;

}

void testDIJK(){
    std::fstream fin("TEST/DIJK.txt");
    int n = 0;
    fin >> n;

    Graph<int> g(n);
    for(int i = 0; i < n; i++){
        int v = 0;
        fin >> v;
        v--;
        int u = 0;
        int w;
        std::vector<neibVert> neib;
        do{
            fin >> u;
            fin >> w;
            if(u >= 0){
                neib.push_back({u - 1, w});
            }

        }while(u != -1);
        g.SetNeibor(v, neib);
    }

    int start, end;
    fin >> start >> end;
    std::vector<int> res = g.Dijkstra(start - 1);
    int p = res[end - 1];
    if(p == -1){
        std::cerr << "Error not found" << std::endl;
        return;
    }
    std::cout << end << " ";
    while(p != start - 1){
        std::cout << p + 1 << " ";
        p = res[p];
    }
    std::cout << start << std::endl;

}

int main(){
    std::cout << "TEST WS -------------------\n";
    testWS();
    std::cout << "TEST DIJK------------------\n";
    testDIJK();
}