//
//@Author  dell 
//@create 2019/5/7 ${Time}.
//

#ifndef ALGORITHMS_EWDIGRAPH_H
#define ALGORITHMS_EWDIGRAPH_H
#pragma once
#include <memory>
#include  <iostream>
#include  <vector>
#include  <queue>
#include  <deque>
#include  <tuple>
#include  <map>
#include  <stack>

using namespace std;

class EWDigraph //图用邻接表方式表示
{
private:
    //图中顶点数
    int vex_;
    //图的边数
    int edge_;
    //当前顶点是否在队列中，可以变成局部变量，但是可能会增加内存分配和释放的次数
    map<char, bool> mapIsInQue_;
    //顶点V到出发点S的最短距离
    map<char, double> mapDistance_;
    //顶点V到出发点S的最短路径
    map<char, char> mapPath_;
    //图的邻接表Map
    map<char, vector<pair<char, double>>> ewd_;
public:

    //构造函数，传入顶点数，边数和<顶点1，顶点2，边权值>元组的数组
    EWDigraph(const int vex, const int edge, const vector<tuple<char, char, double>>& );
    //打印邻接表
    void Print();
    //计算出发点start到图中所有点的最短距离
    void Dijkstra(const char start);
    //计算出发点start到终点end的最短距离并且打印最短路径
    void Dijkstra(const char start, const char end);
    //获取当前图中的所有顶点
    //函数最后的const是向编译器承诺函数返回值不会被修改
    vector<char> GetNodes() const;
    //检查输入的顶点是否在顶点列表中
    bool IsValidVex(const char vex) const;
    //从出发点start开始对图进行广度优先遍历 Breadth First Search Traversal
    void BFST(const char start);
    //从出发点start开始对图进行深度优先遍历 Depth First Search Traversal
    void DFST(const char start);

private:
    //初始化 mapIsInQue_, mapDistance_, mapPath_
    void InitVecs();
    //打印出发点start到图中所有点的最短距离和最短路径
    void PrintDij(const char start);
    //打印出发点start到终点end的最短距离和最短路径
    void PrintDij(const char start, const char end);
};

#endif //ALGORITHMS_EWDIGRAPH_H
