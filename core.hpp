#ifndef _CORE_HPP
#define _CORE_HPP

#include <vector>
#include <queue>
#include <iostream>
#include <Magick++.h>


struct Point {
    int x;
    int y;
    bool operator == (const Point& b){
        return ((*this).x == b.x) && ((*this).y == b.y);
    }
    friend std::ostream& operator<< (std::ostream &out, const Point &point);

};

std::ostream& operator<< (std::ostream &out, const Point &point)
{
    // Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
    out << point.x << ", " << point.y;
 
    return out;
}


#include "graph.hpp"
#include "dotgraph.hpp"

class TypeField{
private:
    int ** plot;
    int ** bplot;
    int rift;
    Graph<Point> f;
    int size;
    int weidth;
    int height;
public:
    TypeField(int _weidth, int _height) {
        plot = new int* [_weidth];
        bplot = new int* [_weidth];
        for(int i = 0; i < _weidth; i++){
            plot[i] = new int [_height];
            bplot[i] = new int [_height];
        }

        weidth = _weidth;
        height = _height;
    }

    void CreateGraph(){
        int startx = -1, starty = -1;
        for(int i = 0 ; i < weidth && startx == -1; i++){
            for(int j = 0; j < height; j ++){
                if(plot[i][j] != -1){
                    startx = i;
                    starty = j;
                    break;
                }
            }
        }
        std::queue<Point> qu;

        qu.push({startx, starty});
        while(!qu.empty()){
            Point p = qu.front();
            qu.pop();
            std::vector<neibVert> neibor;
            if(p.x - 1 >= 0 && bplot[p.x - 1][p.y] == -1 && plot[p.x - 1][p.y] <= rift){
                qu.push({p.x - 1, p.y});
                bplot[p.x - 1][p.y] = -2;
            } else if(p.x - 1 >= 0 && bplot[p.x - 1][p.y] >= 0){
                neibor.push_back({bplot[p.x - 1][p.y], plot[p.x - 1][p.y]});
            }
            if(p.x + 1 < weidth && bplot[p.x + 1][p.y] == -1 && plot[p.x + 1][p.y] <= rift){
                qu.push({p.x + 1, p.y});
                bplot[p.x + 1][p.y] = -2;
            } else if(p.x + 1 < weidth && bplot[p.x + 1][p.y] >= 0){
                neibor.push_back({bplot[p.x + 1][p.y], plot[p.x + 1][p.y]});
            }

            if(p.y - 1 >= 0 && bplot[p.x][p.y - 1] == -1 && plot[p.x][p.y - 1] <= rift){
                qu.push({p.x, p.y - 1});
                bplot[p.x][p.y - 1] = -2;
            } else if(p.y - 1 >= 0 && bplot[p.x][p.y - 1] >= 0 ){
                neibor.push_back({bplot[p.x][p.y - 1], plot[p.x][p.y - 1]});
            }
            if(p.y + 1 < height && bplot[p.x][p.y + 1] == -1 && plot[p.x][p.y + 1] <= rift){
                qu.push({p.x, p.y + 1});
                bplot[p.x][p.y + 1] = -2;
            } else if(p.y + 1 < height && bplot[p.x][p.y + 1] >= 0){
                neibor.push_back({bplot[p.x][p.y + 1], plot[p.x][p.y + 1]});
            }
            bplot[p.x][p.y] = f.addNode(p, neibor);
        }

    }

    void GenerateField(Magick::Image & img, int _rift){
        rift = _rift;

        if(weidth != img.columns()){
            throw "Error size";
        }
        if(height != img.rows()){
            throw "Error size(height)";
        }
        for(int i = 0; i < weidth; i++){
            for(int j = 0; j < height; j++){
                bplot[i][j] = -1;
                Magick::Color col = img.pixelColor(i,j);
                plot[i][j] = 196605 - ( col.quantumRed() + col.quantumGreen() + col.quantumBlue());
            }
        }
    }

    std::vector<Point> search(Point p1, Point p2){

        //f.DEBUG_INFO();

        int index1 = f.searchNode(p1);
        if(index1 == -1){
            throw "Point not found";
        }
        int index2 = f.searchNode(p2);
        if(index2 == -1){
            throw "Point 2 not found";
        }
        std::vector<int> dist = f.WS(index1);
        std::vector<Point> res;
        int p = index2;
        while(p != index1){
            res.push_back(f.Get(p));
            p = dist[p];
        }
        res.push_back(f.Get(index1));

        return res;
    }
    std::vector<Point> Dsearch(Point p1, Point p2){

        f.DEBUG_INFO();

        int index1 = f.searchNode(p1);
        if(index1 == -1){
            throw "Point not found";
        }
        int index2 = f.searchNode(p2);
        if(index2 == -1){
            throw "Point 2 not found";
        }
        std::vector<int> path = f.Dijkstra(index1);
        std::vector<Point> res;
        int p = index2;
        while(p != index1){
            res.push_back(f.Get(p));
            p = path[p];
        }
        res.push_back(f.Get(index1));

        return res;
    }

    void Visualization(){
        DOT_TYPE obj("myvizgraph");
        obj.createGraph(f);
        obj.~DOT_TYPE();
    }
    ~TypeField(){
        for(int i = 0; i < weidth; i++){
            delete bplot[i];
            delete plot[i];
        }
        delete plot;
        delete bplot;
    }
};

#endif