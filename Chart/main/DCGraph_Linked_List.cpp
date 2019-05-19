//
//@Author StreakyPork
//@create 2019/5/17.
//
#include <iostream>
#include <string>
#include <queue>
#include <tuple>
using namespace std;

typedef int Status;

typedef int EdgeWeight;
typedef struct EdgeNode
{
    int Adjacency_vex; //邻接点的位置
    struct EdgeNode* next; //指向下一条边
}EdgeNode;

typedef int VertexType; //顶点内容
typedef struct VertexNode
{
    VertexType data;
    EdgeNode* pFirstEdge; //指示第一条边
    string color;
    int startTime;
    int finishTime;
    struct VertexNode* criticalPath;
}VertexNode;

typedef vector<VertexNode> AdjList;//邻接表

typedef struct
{
    AdjList adjList; //邻接表
    int iVexNum; //顶点个数
    int iEdgeNum; //边数
}AdjListGraph;

int GetIndexByVertexVal( const AdjListGraph&, VertexType);
void createGraph(AdjListGraph&);
void MyPrint(const AdjListGraph&);
void Critical_Path(AdjListGraph&);
void Critical_Path_DFS(AdjListGraph&, int);
bool isValid(AdjListGraph&, int, int);

//由顶点值得到顶点索引
int GetIndexByVertexVal( const AdjListGraph& G, VertexType val )
{
    for ( int i = 0; i < G.iVexNum; ++i )
    {
        if ( val == G.adjList[i].data )
            return i;
    }
    return -1;
}

void createGraph(AdjListGraph &G, const vector<tuple<int,int>> &points, const vector<tuple<int,int>> &edges){
    G.iVexNum = points.size();
    G.iEdgeNum = edges.size();

    // 给点赋值
    for(int i=0; i<points.size(); i++){
        int vIndex = get<0>(points[i]) - 1;
        VertexNode *vertexNode = new VertexNode;
        vertexNode->data = get<1>(points[i]);
        vertexNode->pFirstEdge = NULL;
        vertexNode->color = "white";
        G.adjList.push_back(*vertexNode);
    }

    //创建边
    for(int i=0; i<G.iEdgeNum; i++){
        auto v1 = get<0>(edges[i]) - 1;
        auto v2 = get<1>(edges[i]) - 1;
        EdgeNode* pEdgeNode = new EdgeNode;
        pEdgeNode->Adjacency_vex = v2; // 指向节点
        pEdgeNode->next = G.adjList[v1].pFirstEdge;
        G.adjList[v1].pFirstEdge = pEdgeNode;
    }
}

bool isValid(AdjListGraph &G, int v1,int v2){
    EdgeNode* next = G.adjList[v1].pFirstEdge;
    while(next!=NULL){
        if(next->Adjacency_vex==v2){
            return true;
        }
        next = next->next;
    }
    delete next;
    return false;
}

void Critical_Path_DFS(AdjListGraph &G, int v){
    G.adjList[v].color = "grey";
    G.adjList[v].startTime = 0;
    G.adjList[v].criticalPath = NULL;
    for(int i=0; i<G.iVexNum; i++){
        if(isValid(G,v,i) && v!=i){
            if(G.adjList[i].color=="white"){
                Critical_Path_DFS(G,i);
                if(G.adjList[i].finishTime >= G.adjList[v].startTime){
                    G.adjList[v].startTime = G.adjList[i].finishTime;
                    G.adjList[v].criticalPath = &G.adjList[i];
                }
            }
            else{
                if(G.adjList[i].finishTime >= G.adjList[v].startTime){
                    G.adjList[v].startTime = G.adjList[i].finishTime;
                    G.adjList[v].criticalPath = &G.adjList[i];
                }
            }
        }
    }
    G.adjList[v].finishTime = G.adjList[v].startTime + G.adjList[v].data;
    G.adjList[v].color = "black";
}

void Critical_Path(AdjListGraph &G){
    for(int i=0; i<G.iVexNum; i++){
        if(G.adjList[i].color=="white"){
            Critical_Path_DFS(G,i);
        }
    }
    int max = 0;
    for(int i=0; i<G.iVexNum; i++){
        if(G.adjList[i].finishTime >= max)
            max = G.adjList[i].finishTime;
    }
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << max << endl;
}

void MyPrint(const AdjListGraph &G){
    cout << "节点数据:" << endl;
    for(int i=0; i<G.iVexNum; i++){
        cout << i << " ";
    }
    cout << endl;
    cout << "边的数据:" << endl;
    for(int i=0; i<G.iVexNum; i++){
        VertexNode vertexNode = G.adjList[i];
        EdgeNode *next = vertexNode.pFirstEdge;
        while(next!=NULL){
            cout << i << "-" << next->Adjacency_vex << " ";
            next = next->next;
        }
        cout << endl;
    }
}

void getData(vector<tuple<int,int>> &points, vector<tuple<int,int>> &edges){
    int n;
    cin >> n;
    int a,b;
    for(int i=0; i<n; i++){
        cin >> a >> b;
        points.push_back(make_tuple(a,b));
    }
    while(!cin.eof()){
        cin >> a >> b;
        edges.push_back(make_tuple(a,b));
    }
    /*
    points.push_back(make_tuple(1,10));points.push_back(make_tuple(2,6));points.push_back(make_tuple(3,5));
    points.push_back(make_tuple(4,1));points.push_back(make_tuple(5,2));points.push_back(make_tuple(6,3));
    points.push_back(make_tuple(7,4));points.push_back(make_tuple(8,9));points.push_back(make_tuple(9,1));

    edges.push_back(make_tuple(1,9));edges.push_back(make_tuple(2,1));edges.push_back(make_tuple(2,8));
    edges.push_back(make_tuple(3,5));edges.push_back(make_tuple(3,6));edges.push_back(make_tuple(3,7));
    edges.push_back(make_tuple(4,2));edges.push_back(make_tuple(4,3));edges.push_back(make_tuple(5,9));
    edges.push_back(make_tuple(6,9));edges.push_back(make_tuple(7,9));edges.push_back(make_tuple(8,9));
     */
}

int main() {
    AdjListGraph G;
    vector<tuple<int,int>> points;
    vector<tuple<int,int>> edges;

    getData(points,edges);
    createGraph(G,points,edges);
    vector<tuple<int,int>>().swap(points);
    vector<tuple<int,int>>().swap(edges);
    Critical_Path(G);
}