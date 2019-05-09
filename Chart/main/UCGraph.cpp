//
//@Author  dell 
//@create 2019/5/8 .
// Undirected connected graph
//
#include <tuple>
#include <iostream>
#include "algorithm"
#include "stdio.h"
#include "vector"
#include "string"
using namespace std;

/*
 * 图中的点
 */
class Point{
private:
    int id;
    string color;
    Point* parent;
    int discover_time;
    int finish_time;
    int back;
public:
    Point(const int id){
        Point::id = id;
        color = "white";
        discover_time = 0;
        finish_time = 0;
        back = 0;
        parent = NULL;
    }
    Point(const int id, const int discover_time){
        Point::id = id;
        Point::discover_time = discover_time;
        finish_time = 0;
        back = 0;
        color = "white";
        parent = NULL;
    }
    int getID() const {
        return id;
    }
    string getColor() const {
        return color;
    }
    void setColor(const string color){
        Point::color = color;
    }
    int getDiscoverTime() const {
        return discover_time;
    }
    void setDiscoverTime(const int discoverTime) {
        discover_time = discoverTime;
    }
    int getFinishTime() const {
        return finish_time;
    }
    void setFinishTime(const int finishTime) {
        finish_time = finishTime;
    }
    int getBack() const {
        return back;
    }
    void setBack(const int back) {
        Point::back = back;
    }
    Point* getParent() const{
        return parent;
    }
    void setParent(Point* parent){
        Point::parent = parent;
    }
};

/*
 * 无向连通图
 */
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
    explicit UCGraph(int n){
        vex_ = n;
        edge_ = 0;
        adjacency_matrix = new int*[vex_];
        for(int i=0; i<vex_; i++){
            Point point(i);
            points.push_back(point);
        }
        for(int i=0; i<vex_; i++){
            adjacency_matrix[i] = new int[vex_];
            for(int j=0; j<vex_; j++){
                adjacency_matrix[i][j] = 0;
            }
        }
        time = 0;
    }
    UCGraph(int n, const vector<tuple<int, int>> edges){
        vex_ = n;
        edge_ = edges.size();
        adjacency_matrix = new int*[vex_];
        for(int i=0; i<vex_; i++){
            Point point(i);
            points.push_back(point);
        }
        for(int i=0; i<vex_; i++){
            adjacency_matrix[i] = new int[vex_];
            for(int j=0; j<vex_; j++){
                adjacency_matrix[i][j] = 0;
            }
        }
        for(auto t: edges){
            adjacency_matrix[get<0>(t)][get<1>(t)] = 1;
            adjacency_matrix[get<1>(t)][get<0>(t)] = 1;
        }
        time = 0;
    }
    UCGraph(int n, int m, const vector<tuple<int, int>> edges){
        vex_ = n;
        edge_ = m;
        adjacency_matrix = new int*[vex_];
        for(int i=0; i<vex_; i++){
            Point point(i);
            points.push_back(point);
        }
        for(int i=0; i<vex_; i++){
            adjacency_matrix[i] = new int[vex_];
            for(int j=0; j<vex_; j++){
                adjacency_matrix[i][j] = 0;
            }
        }
        for(auto t: edges){
            adjacency_matrix[get<0>(t)][get<1>(t)] = 1;
            adjacency_matrix[get<1>(t)][get<0>(t)] = 1;
        }
        time = 0;
    }

    /**
     * 判断两点是否连通
     * @param v1 点1
     * @param v2 点2
     * @return 连通的布尔值
     */
    bool isValid(const int v1, const int v2){
        return adjacency_matrix[v1][v2]!=0;
    }

    /**
     * 基于DFS寻找割点
     * @param v1 起点
     * @return Back记录
     */
    int Articulation_Point_DFS(int v1, vector<int>& articulation_points){
        int children = 0; //记录子树的个数，用于判断根节点
        points[v1].setColor("grey");
        time++;
        points[v1].setDiscoverTime(time);
        points[v1].setBack(time);
        //cout << "时间是" << time <<" 当前点:" << v1 << " discoverTime:" << points[8].getDiscoverTime() << " back:" << points[8].getBack() << endl;
        for(int i=0; i<vex_; i++){
            if(isValid(v1,i) && v1!=i) { //找到邻居
                if(points[i].getColor()=="white"){ //白色节点，递归
                    points[i].setParent(&points[v1]); //标记父节点
                    children++; // 子树个数+1
                    points[i].setBack(Articulation_Point_DFS(i, articulation_points));
                    time++;
                    if(points[i].getBack()>=points[v1].getDiscoverTime() && points[v1].getDiscoverTime()!=1) //找到割点
                        articulation_points.push_back(v1);
                    points[v1].setBack(min(points[v1].getBack(),points[i].getBack())); //更新Back记录
                }
                else{ //黑色节点不可能存在递归过程中，只会在回溯时存在
                    if(points[i].getColor()=="grey" && points[v1].getParent()->getID()!= i){ //灰色节点且没有父子关系
                        points[v1].setBack(min(points[v1].getBack(),points[i].getDiscoverTime())); //更新Back记录
                    }
                }
            }
        }
        points[v1].setColor("black");
        if(children>1 && points[v1].getParent()==NULL){
            cout << v1 << endl;
        }
        return points[v1].getBack();
    }

    /**
     * 寻找割点
     * @param articulation_points 割点的集合
     */
    void Articulation_Point(vector<int>& articulation_points){
        Articulation_Point_DFS(0, articulation_points);
        sort(articulation_points.begin(), articulation_points.end());
    }
    。。3.3.。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。333333333333333333333333333333333333333333333333333333333333333

    /**
     * 打印邻接矩阵
     */
    void Print(){
        for(int i=0; i<vex_; i++){
            for (int j = 0; j < vex_; j++) {
                cout << adjacency_matrix[i][j] << " ";
            }
            cout<<endl;
        }
    }
};

int main(){
    int n = 10;
    //cin >> n;
    vector<tuple<int, int>> edges = {
            make_tuple(0,3),make_tuple(0,5),make_tuple(0,7),
            make_tuple(1,2),make_tuple(1,4),make_tuple(1,6),make_tuple(1,8),
            make_tuple(2,4),
            make_tuple(3,5),make_tuple(3,9),
            make_tuple(4,5),
            make_tuple(5,7),make_tuple(5,9),
            make_tuple(6,8)
    };
    UCGraph ucGraph(n,edges);
    //ucGraph.Print();
    vector<int> a_points;
    ucGraph.Articulation_Point(a_points);
    for(auto a: a_points){
        cout << a << endl;
    }
}
