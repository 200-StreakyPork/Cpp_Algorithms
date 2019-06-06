//
//@Author StreakyPork
//@create 2019/6/5.
//最小点覆盖
//
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <algorithm>
using namespace std;

#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct Point{
    int in; //在点覆盖中,并且以点p为根的子树中所连接的边都被覆盖的情况下点覆盖集中所包含最少点的个数。
    int out; //不在点覆盖中,并且以点p为根的子树中所连接的边都被覆盖的情况下点覆盖集中所包含最少点的个数。
    int color;
}Point;

vector<Point> points;
vector<vector<int>> edges;

void MyPrint() {
    for(int i=0; i<points.size(); i++) {
        cout << "点" << i << ": ";
        for(int j=0; j<edges[i].size(); j++) {
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }
}

void FindSmallest() {
    cout << min(points[0].in, points[0].out);
}

void DP(int v) {
    points[v].color = GRAY;
    for(int i=0; i<edges[v].size(); i++) {
        int child = edges[v][i];
        if(points[child].color==WHITE) {
            DP(child);
            points[v].in += min(points[child].in, points[child].out);
            points[v].out += points[child].in;
        }
        else {
            points[v].in += min(points[child].in, points[child].out);
            points[v].out += points[child].in;
        }
    }
    points[v].color = BLACK;
}

int main() {
    while(!cin.eof()){
        // 初始化点
        Point p;
        p.in = 1;
        p.out = 0;
        p.color = WHITE;
        points.push_back(p);
        //初始化边
        vector<int> pointEdge;
        string s;
        getline(cin,s);
        stringstream input(s);
        string res;
        int tag = 0;
        while (input>>res) {
            if(tag!=0) {
                pointEdge.push_back(stoi(res.c_str()));
            }
            else {
                tag++;
            }
        }
        edges.push_back(pointEdge);
    }
    DP(0);
    FindSmallest();
    //MyPrint();
}

