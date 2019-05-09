//
//@Author StreakyPork
//@create 2019/5/9.
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
    Point* critical_dependence;
    int start_time;
    int finish_time;
    int need_time;
public:
    Point(const int id){
        Point::id = id;
        color = "white";
        start_time = 0;
        finish_time = 0;
        need_time = 0;
        parent = NULL;
        critical_dependence = NULL;
    }
    Point(const int id, const int need_time){
        Point::id = id;
        color = "white";
        start_time = 0;
        finish_time = 0;
        Point::need_time = need_time;
        parent = NULL;
        critical_dependence = NULL;
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
    int getStartTime() const {
        return start_time;
    }
    void setStartTime(const int startTime) {
        Point::start_time = startTime;
    }
    int getFinishTime() const {
        return finish_time;
    }
    void setFinishTime(const int finishTime) {
        Point::finish_time = finishTime;
    }
    int getNeedTime() const {
        return need_time;
    }
    void setNeedTime(const int needTime){
        need_time = needTime;
    }
    Point* getParent() const{
        return parent;
    }
    void setParent(Point* parent){
        Point::parent = parent;
    }
    Point* getCritDep() const{
        return critical_dependence;
    }
    void setCritDep(Point* critical_dependence){
        Point::critical_dependence = critical_dependence;
    }
};

/*
 * 有向连通图
 */
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
    explicit DCGraph(int n){
        vex_ = n;
        edge_ = 0;
        adjacency_matrix = new int*[vex_];
        for(int i=0; i<vex_; i++){
            Point point(i+1);
            points.push_back(point);
        }
        for(int i=0; i<vex_; i++){
            adjacency_matrix[i] = new int[vex_];
            for(int j=0; j<vex_; j++){
                adjacency_matrix[i][j] = 0;
            }
        }
        //初始化计时器
        time = 0;
    }
    DCGraph(int n, const vector<tuple<int, int>> points){
        vex_ = n;
        edge_ = 0;
        adjacency_matrix = new int*[vex_];
        //初始化点集
        for(int i=0; i<vex_; i++){
            Point point(i+1);
            DCGraph::points.push_back(point);
        }
        for(int i=0; i<vex_; i++){
            int id = get<0>(points[i]);
            int need_time = get<1>(points[i]);
            DCGraph::points[id-1].setNeedTime(need_time);
        }
        //初始化邻接矩阵
        for(int i=0; i<vex_; i++){
            adjacency_matrix[i] = new int[vex_];
            for(int j=0; j<vex_; j++){
                adjacency_matrix[i][j] = 0;
            }
        }
        //初始化计时器
        time = 0;
    }
    DCGraph(int n, const vector<tuple<int, int>> points, const vector<tuple<int, int>> edges){
        vex_ = n;
        edge_ = edges.size();
        adjacency_matrix = new int*[vex_];
        //初始化点集
        for(int i=0; i<vex_; i++){
            Point point(i+1);
            DCGraph::points.push_back(point);
        }
        for(int i=0; i<vex_; i++){
            int id = get<0>(points[i]);
            int need_time = get<1>(points[i]);
            DCGraph::points[id-1].setNeedTime(need_time);
        }
        //初始化邻接矩阵
        for(int i=0; i<vex_; i++){
            adjacency_matrix[i] = new int[vex_];
            for(int j=0; j<vex_; j++){
                adjacency_matrix[i][j] = 0;
            }
        }
        for(auto t: edges){
            adjacency_matrix[get<0>(t)-1][get<1>(t)-1] = 1;
        }
        //初始化计时器
        time = 0;
    }

    /**
     * 判断v1是否连通至v2
     * @param v1 点1
     * @param v2 点2
     * @return 连通的布尔值
     */
    bool isValid(const int v1, const int v2){
        return adjacency_matrix[v1][v2]!=0;
    }

    /*
     * 清空有向图
     */
    void clear_DCGraph(){
        time = 0;
        for(int i=0; i<vex_; i++){
            points[i].setColor("white");
            points[i].setStartTime(0);
            points[i].setFinishTime(0);
            points[i].setNeedTime(0);
            points[i].setParent(NULL);
            points[i].setCritDep(NULL);
        }
    }

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

    /**
     * 利用DFS寻找关键路径
     * @param v 开始节点
     */
    void Critical_Path_DFS(int v){
        points[v].setColor("grey");
        points[v].setStartTime(0); points[v].setCritDep(NULL);
        for(int i=0; i<vex_; i++){
            if(isValid(v,i) && v!=i){
                if(points[i].getColor()=="white"){
                    Critical_Path_DFS(i);
                    if(points[i].getFinishTime() >= points[v].getStartTime()){
                        points[v].setStartTime(points[i].getFinishTime());
                        points[v].setCritDep(&points[i]);
                    }
                }
                else{
                    if(points[i].getFinishTime() >= points[v].getStartTime()){
                        points[v].setStartTime(points[i].getFinishTime());
                        points[v].setCritDep(&points[i]);
                    }
                }
            }
        }
        points[v].setFinishTime(points[v].getStartTime()+points[v].getNeedTime());
        points[v].setColor("black");
    }

    /**
     * 寻找关键路径
     * @param v
     */
    void Critical_Path(){
        for(int i=0; i<vex_; i++){
            if(points[i].getColor()=="white"){
                Critical_Path_DFS(i);
            }
        }
        int max = 0;
        for(int i=0; i<vex_; i++){
            if(points[i].getFinishTime() >= max)
                max = points[i].getFinishTime();
        }
        cout << max << endl;
    }
};
/*
int main(){
    int n = 9;
    vector<tuple<int, int>> points = {
            make_tuple(1,10),make_tuple(2,6),make_tuple(3,5),make_tuple(4,1),make_tuple(5,2),
            make_tuple(6,3),make_tuple(7,4),make_tuple(8,9),make_tuple(9,1)
    };
    vector<tuple<int, int>> edges = {
            make_tuple(1,9),
            make_tuple(2,1),make_tuple(2,8),
            make_tuple(3,5),make_tuple(3,6),make_tuple(3,7),
            make_tuple(4,2),make_tuple(4,3),
            make_tuple(5,9),
            make_tuple(6,9),
            make_tuple(7,9),
            make_tuple(8,9),
    };
    DCGraph dcGraph(n,points,edges);
    dcGraph.Critical_Path();
}
 */