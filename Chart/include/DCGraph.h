//
//@Author StreakyPork
//@create 2019/5/8.
//
#include "vector"
#include "Point.h"
using namespace std;

#ifndef ALGORITHMS_DCGRAPH_H
#define ALGORITHMS_DCGRAPH_H

class DCGraph{
private:
    //图中顶点数
    int vex_;
    //图中边数
    int edge_;
    //邻接矩阵
    int** adjacency_matrix;
    //点集
    vector<Point> points;
    //计时器
    int time;
public:
    explicit DCGraph(int n);
    DCGraph(int n, const vector<tuple<int, int>> points);
    DCGraph(int n, const vector<tuple<int, int>> points, vector<tuple<int, int>> edges);
    bool isValid(const int v1, const int v2);
    void DFS(int v);
    void DFS_Wrapper();
    void DFS_Clock(int v);
    void DFS_Clock_Wrapper();
    void BFS(int v);
    void BFS_Wrapper();
    void Topo_Order(int v);
    void Topo_Wrapper();
    void clear_DCGraph();
    void Print();
};

#endif //ALGORITHMS_DCGRAPH_H
