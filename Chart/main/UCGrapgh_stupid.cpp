//
//@Author StreakyPork
//@create 2019/5/19.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct Vertex{
    int data;
    int color;
    int discoverTime;
    int finishTime;
    int back;
}Vertex;

typedef struct Edge{
    Vertex* startVex;
    Vertex* endVex;
    Edge* next;
    Edge* returnEdge;
    int TE;
}Edge;

void getData();
void clearGraph();
void Articulation_Point();
int Articulation_Point_DFS(Vertex*);
void Bridge();
void Bridge_DFS(Vertex*);

Edge** edge;
Vertex** vex;
int n;
int Time;
vector<int> articulation_points;
vector<tuple<int,int>> bridges;

int Articulation_Point_DFS(Vertex* v) {
    int children = 0; //记录子树的个数，用于判断根节点
    v->color = GRAY;
    Time++;
    v->discoverTime = Time;
    v->back = v->discoverTime;
    Edge* e = edge[v->data];
    while(e != NULL) {
        Vertex* w = e->endVex;
        if(w->color == WHITE){ //白色节点，递归
            e->TE = 1;
            e->returnEdge->TE = 1;
            children++; // 子树个数+1
            w->back = Articulation_Point_DFS(w);
            Time++;
            if(w->back >= v->discoverTime && v->discoverTime!=1)//找到割点
                articulation_points.push_back(v->data);
            v->back = min(v->back, w->back); //更新Back记录
        }
        else{ //黑色节点不可能存在递归过程中，只会在回溯时存在
            if(e->TE!=1){ //灰色节点且没有父子关系
                v->back = min(v->back, w->discoverTime); //更新Back记录
            }
        }
        e = e->next;
    }
    v->color = BLACK;
    if(children>1 && v->data==0){
        cout << v->data << endl;
    }
    return v->back;
}

/**
 * 寻找割点
 * @param articulation_points 割点的集合
 */
void Articulation_Point(){
    for(int i=0; i<n; i++){
        if(vex[i]->color == WHITE){
            Articulation_Point_DFS(vex[i]);
        }
    }
    clearGraph();
}

void Bridge_DFS(Vertex* v){
    v->color = GRAY;
    Time++;
    v->discoverTime = Time;
    v->back = v->discoverTime;
    Edge* e = edge[v->data];
    while(e != NULL) {
        Vertex* w = e->endVex;
        if(w->color == WHITE){ //白色节点，递归
            e->TE = 1;
            e->returnEdge->TE = 1;
            Bridge_DFS(w);
            Time++;
            v->back = min(v->back, w->back); //更新Back记录
            if(w->back > v->discoverTime) { //找到割点iu
                if (v->data < w->data)
                    bridges.push_back(make_tuple(v->data, w->data));
                else
                    bridges.push_back(make_tuple(w->data, v->data));
            }

        }
        else{ //黑色节点不可能存在递归过程中，只会在回溯时存在
            if(e->TE!=1){ //灰色节点且没有父子关系
                v->back = min(v->back, w->discoverTime); //更新Back记录
            }
        }
        e = e->next;
    }
    v->color = BLACK;
}

void Bridge(){
    for(int i=0; i<n; i++){
        if(vex[i]->color == WHITE){
            Bridge_DFS(vex[i]);
        }
    }
}

void clearGraph() {
    for(int i=0; i<n; i++) {
        vex[i]->color = WHITE;
        vex[i]->discoverTime = 0;
        vex[i]->finishTime = 0;
        vex[i]->back = 0;
    }
    Time = 0;
}

void Print() {
    sort(articulation_points.begin(), articulation_points.end());
    for(int i=0; i<articulation_points.size(); i++){
        cout << articulation_points[i] << endl;
    }
    sort(bridges.begin(), bridges.end());
    for(int i=0; i<bridges.size(); i++){
        cout << get<0>(bridges[i]) << " " << get<1>(bridges[i]) << endl;
    }
    /*
    cout << "边的信息:" << endl;
    for(int i=0; i<n; i++) {
        Vertex* v = vex[i];
        Edge* e = edge[v->data];
        while(e!=NULL){
            cout<<e->startVex->data<<"-"<<e->endVex->data<<endl;
            e = e->next;
        }
    }*/
}

void getData(){
    cin >> n;
    edge = new Edge* [n];
    vex = new Vertex* [n];
    // 初始化点集
    for (int i=0; i<n; i++){
        Vertex* v = new Vertex;
        v->data = i;
        v->color = WHITE;
        vex[i] = v;
    }
    // 初始化边
    for (int i=0; i<n; i++)
        edge[i] = NULL;
    int v, u;
    while (!cin.eof()){
        cin >> v >> u;
        Edge* e1 = new Edge;
        e1->startVex = vex[v];
        e1->endVex = vex[u];
        e1->next = edge[v];
        e1->TE = 0;
        edge[v] = e1;

        Edge* e2 = new Edge;
        e2->startVex = vex[u];
        e2->endVex = vex[v];
        e2->next = edge[u];
        e2->TE = 0;
        edge[u] = e2;

        e1->returnEdge = e2;
        e2->returnEdge = e1;
    }
    // 初始化计时器
    Time = 0;
}

int main(){
    getData();
    Articulation_Point();
    Bridge();
    Print();
}


