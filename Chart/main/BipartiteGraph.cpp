//
//@Author StreakyPork
//@create 2019/5/23.
//二部图
//
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#define WHITE 1
#define GRAY 2
#define BLACK 3
#define RED 4
#define BLUE 5

static vector<vector<int>> edges;
static vector<int> points;

static void MyPrint() {
    for(int i=0; i<points.size(); i++) {
        if (points[i] == RED)
        cout << i << endl;
    }
}

static bool Bipartite_DFS(int v) {
    for(int i=0; i<edges[v].size(); i++) {
        int child = edges[v][i];
        if(points[child]==WHITE) { // 子节点是白色
            if(points[v]==RED)
                points[child] = BLUE;
            else
                points[child] = RED;
            if(!Bipartite_DFS(child)) { // 递归中出错
                return false;
            }
        }
        else { // 子节点已经被染色
            if(points[child]==points[v]) { // 染色相同
                return false;
            }
        }
    }
    return true;
}

static void Bipartite() {
    points[0] = RED;
    Bipartite_DFS(0);
    MyPrint();
}
/*
int main() {
    string s;
    vector<string> p;
    while(!cin.eof()){
        getline(cin,s);
        p.push_back(s);
    }

    // 初始化点和边
    for(int i=0; i<p.size(); i++) {
        points.push_back(WHITE);
        vector<int> pointEdge;
        edges.push_back(pointEdge);
    }

    // 给边赋值
    for(int i=0; i<p.size(); i++) {
        stringstream input(p[i]);
        string res;
        int tag = 0;
        int pointIndex;
        while (input>>res) {
            tag++;
            if(tag==1) {
                pointIndex = atoi(res.c_str());
            }
            else {
                edges[pointIndex].push_back(atoi(res.c_str()));
            }
        }
    }

    Bipartite();
}
*/
