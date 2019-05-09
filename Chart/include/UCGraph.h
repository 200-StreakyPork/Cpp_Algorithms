//
//@Author StreakyPork
//@create 2019/5/8.
//
#include "vector"
#include "Point.h"
using namespace std;

#ifndef ALGORITHMS_UCGRAPH_H
#define ALGORITHMS_UCGRAPH_H

class UCGraph{
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
    explicit UCGraph(int n);
    UCGraph(int n, const vector<tuple<int, int>> edges);
    UCGraph(int n, int m, const vector<tuple<int, int>> edges);
    bool isValid(const int v1, const int v2);
    int Articulation_Point_DFS(int v1, vector<int>& articulation_points);
    void Articulation_Point(vector<int>& articulation_points);
    void Print();
};

#endif //ALGORITHMS_UCGRAPH_H
