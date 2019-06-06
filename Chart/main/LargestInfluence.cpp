//
//@Author StreakyPork
//@create 2019/5/23.
//最大影响力
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
    int color;
    int influence;
    int belong;
}Point;

static vector<Point> points;
static vector<vector<int>> edges;
static vector<vector<int>> edges_t;
static stack<int> nodeStack;
int connectedPieceIndex;
vector<vector<int>> connectedPiece;
vector<int> result;
int maxInfluence = 0;

static void MyPrint() {
    cout << "各点所属连通片：" << endl;
    for(int i=0; i<points.size(); i++) {
        cout << i << ": " << points[i].belong << endl;
    }
    cout << "各点影响力：" << endl;
    for(int i=0; i<points.size(); i++) {
        cout << i << ": " << points[i].influence << endl;
    }
}

void ClearPoints_All() {
    for(int i=0; i<points.size(); i++) {
        points[i].color = WHITE;
        points[i].influence = 0;
    }
}

void ClearPoints() {
    for(int i=0; i<points.size(); i++) {
        points[i].color = WHITE;
    }
}

void PrintLargest() {
    cout << maxInfluence << endl;
    sort(result.begin(), result.end());
    for(int i=0; i<result.size(); i++){
        cout << result[i] << " ";
    }
}

void FindLargest() {
    for(int i=0; i<connectedPiece.size(); i++) {
        int influence = points[connectedPiece[i][0]].influence;
        if(influence > maxInfluence) {
            maxInfluence = influence;
            result.clear();
            result.insert(result.end(), connectedPiece[i].begin(), connectedPiece[i].end());
        }
        else if(influence == maxInfluence) {
            result.insert(result.end(), connectedPiece[i].begin(), connectedPiece[i].end());
        }
    }
}

void AlterInfluence(int belong, int influence) {
    for(int i=0; i<connectedPiece[belong].size(); i++) {
        int index = connectedPiece[belong][i];
        points[index].influence = influence;
    }
}

void LargestInfluence(int v) {
    points[v].color = GRAY;
    if(points[v].influence < connectedPiece[points[v].belong].size() - 1){ // 影响力小于连通片点数
        AlterInfluence(points[v].belong, connectedPiece[points[v].belong].size() - 1);
    }
    for(int i=0; i<edges[v].size(); i++) {
        int child = edges[v][i];
        if(points[child].color==WHITE) {
            LargestInfluence(child);
            if(points[child].belong != points[v].belong) { // 不同连通片
                AlterInfluence(points[v].belong, points[v].influence + points[child].influence + 1);
            }
        }
        else {

        }
    }
    points[v].color = BLACK;
}

void InfluenceWrapper() {
    for(int i=0; i<points.size(); i++) {
        if(points[i].color==WHITE) {
            ClearPoints_All();
            LargestInfluence(i); // 遍历
            FindLargest();
        }
    }
}

void DFS_Second(int v){
    points[v].belong = connectedPieceIndex;
    connectedPiece[connectedPieceIndex].push_back(v);
    points[v].color = GRAY;
    for(int i=0; i<edges_t[v].size(); i++) {
        int child = edges_t[v][i];
        if(points[child].color==WHITE) {
            DFS_Second(child);
        }
        else {
        }
    }
    points[v].color = BLACK;
}

void Transposition() {
    // 添加转置的边
    for(int i=0; i<edges.size(); i++) {
        int v1 = i;
        for(int j=0; j<edges[i].size(); j++) {
            int v2 = edges[i][j];
            edges_t[v2].push_back(v1);
        }
    }
}

void DFS_First(int v){
    points[v].color = GRAY;
    for(int i=0; i<edges[v].size(); i++) {
        int child = edges[v][i];
        if(points[child].color==WHITE) {
            DFS_First(child);
        }
        else {
        }
    }
    points[v].color = BLACK;
    nodeStack.push(v);
}

void DFS_First_Wrapper() {
    for(int i=0; i<points.size(); i++) {
        if(points[i].color==WHITE) {
            DFS_First(i);
        }
    }
}

void SCC() {
    DFS_First_Wrapper(); // 第一次DFS寻找尽头
    Transposition(); // 转置图
    ClearPoints(); // 清空点的颜色
    while(!nodeStack.empty()){
        int v = nodeStack.top();
        nodeStack.pop();
        if(points[v].color==WHITE){ // 新的连通片
            vector<int> onePiece;
            connectedPiece.push_back(onePiece);
            DFS_Second(v);
            connectedPieceIndex++;
        }
    }
    ClearPoints();
}
/*
int main() {
    connectedPieceIndex = 0;
    while(!cin.eof()){
        // 原图的点
        Point point;
        point.color = WHITE;
        point.belong = 0;
        point.influence = 0;
        points.push_back(point);
        // 原图的边
        vector<int> pointEdge;
        string s;
        getline(cin,s);
        stringstream input(s);
        string res;
        while (input>>res){
            pointEdge.push_back(stoi(res.c_str()));
        }
        edges.push_back(pointEdge);
        // 转置的边
        vector<int> pointEdge_t;
        edges_t.push_back(pointEdge_t);
    }


    SCC();
    //MyPrint();
    InfluenceWrapper();
    PrintLargest();
}
 */