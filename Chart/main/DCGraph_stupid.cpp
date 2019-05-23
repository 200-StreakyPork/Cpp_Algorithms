//
//@Author StreakyPork
//@create 2019/5/19.
//
/*
#include<iostream>
using namespace std;

#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct Vertex{
    int data;
    int needTime;
    int est;
    int eft;
    int color;
    Vertex * CritDeq;
}Vertex;

typedef struct Edge{
    Vertex * dest;
    Edge * next;
}Edge;

void CritPath(Vertex* v);
void getData();
Edge** edge;
Vertex** vex;
int n;

void getData(){
    cin >> n;
    edge = new Edge* [n];
    vex = new Vertex* [n];
    for (int i=0; i<n; i++){
        Vertex* v = new Vertex;
        cin >> v->data >> v->needTime;
        v->color = WHITE;
        vex[i] = v;
    }

    for (int i=0; i<n; i++)
        edge[i] = NULL;
    int v, u;
    while (!cin.eof()){
        cin >> v >> u;
        Edge* e = new Edge;
        e->dest = vex[v-1];
        e->next = edge[u-1];
        edge[u-1] = e;
    }
}

void CritPath(Vertex* v){
    v->color = GRAY;
    v->est = 0;
    v->CritDeq = NULL;
    Edge * e = edge[v->data - 1];
    while (e != NULL){
        Vertex* w = e->dest;
        if (w->color == WHITE){
            CritPath(e->dest);
            if (w->eft >= v->est){
                v->est = w->eft;
                v->CritDeq = w;
            }
        }
        else{
            if (w->eft >= v->est){
                v->est = w->eft;
                v->CritDeq = w;
            }
        }
        e = e->next;
    }
    v->eft = v->est + v->needTime;
    v->color = BLACK;

}

void Critical_Path() {
    for (int i = 0; i < n; i++){
        if (vex[i]->color == WHITE)
            CritPath(vex[i]);
    }
}
int main(){
    getData();
    Critical_Path();
    int leastTime = 0;
    for (int i = 0; i < n; i++){
        if (vex[i]->eft > leastTime)
            leastTime = vex[i]->eft;
    }
    cout << leastTime;
}
 */
