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
 * ͼ�еĵ�
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
 * ������ͨͼ
 */
class UCGraph{
private:
    //ͼ�ж�����
    int vex_;
    //ͼ�б���
    int edge_;
    //�ڽӾ���
    int** adjacency_matrix;
    //�㼯
    vector<Point> points;
    //��ʱ��
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
     * �ж������Ƿ���ͨ
     * @param v1 ��1
     * @param v2 ��2
     * @return ��ͨ�Ĳ���ֵ
     */
    bool isValid(const int v1, const int v2){
        return adjacency_matrix[v1][v2]!=0;
    }

    /*
     * �������ͼ
     */
    void clear_UCGraph(){
        time = 0;
        for(int i=0; i<vex_; i++){
            points[i].setColor("white");
            points[i].setDiscoverTime(0);
            points[i].setFinishTime(0);
            points[i].setBack(0);
            points[i].setParent(NULL);
        }
    }

    /**
     * ����DFSѰ�Ҹ��
     * @param v1 ���
     * @return Back��¼
     */
    int Articulation_Point_DFS(int v1, vector<int>& articulation_points){
        int children = 0; //��¼�����ĸ����������жϸ��ڵ�
        points[v1].setColor("grey");
        time++;
        points[v1].setDiscoverTime(time);
        points[v1].setBack(time);
        for(int i=0; i<vex_; i++){
            if(isValid(v1,i) && v1!=i) { //�ҵ��ھ�
                if(points[i].getColor()=="white"){ //��ɫ�ڵ㣬�ݹ�
                    points[i].setParent(&points[v1]); //��Ǹ��ڵ�
                    children++; // ��������+1
                    points[i].setBack(Articulation_Point_DFS(i, articulation_points));
                    time++;
                    if(points[i].getBack()>=points[v1].getDiscoverTime() && points[v1].getDiscoverTime()!=1) //�ҵ����
                        articulation_points.push_back(v1);
                    points[v1].setBack(min(points[v1].getBack(),points[i].getBack())); //����Back��¼
                }
                else{ //��ɫ�ڵ㲻���ܴ��ڵݹ�����У�ֻ���ڻ���ʱ����
                    if(points[i].getColor()=="grey" && points[v1].getParent()->getID()!= i){ //��ɫ�ڵ���û�и��ӹ�ϵ
                        points[v1].setBack(min(points[v1].getBack(),points[i].getDiscoverTime())); //����Back��¼
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
     * Ѱ�Ҹ��
     * @param articulation_points ���ļ���
     */
    void Articulation_Point(vector<int>& articulation_points){
        for(int i=0; i<vex_; i++){
            if(points[i].getColor()=="white"){
                Articulation_Point_DFS(i, articulation_points);
            }
        }
        sort(articulation_points.begin(), articulation_points.end());
        clear_UCGraph();
    }

    void Bridge_DFS(int v, vector<tuple<int, int>>& bridges){
        points[v].setColor("grey");
        time = time + 1;
        points[v].setDiscoverTime(time);
        points[v].setBack(time);
        //cout << "��ʱ��" << time << "��ǰ�ڵ�:" << v << endl;
        for(int i=0; i<vex_; i++){
            if(isValid(v, i) && v!=i){ //�ɴ��Լ��
                if(points[i].getColor()=="white"){
                    points[i].setParent(&points[v]);
                    Bridge_DFS(i, bridges);
                    time++;
                    points[v].setBack(min(points[v].getBack(),points[i].getBack()));
                    if(points[i].getBack()>points[v].getDiscoverTime()){
                        bridges.push_back(make_tuple(v,i));
                        //cout << v << "-" << i << endl;
                    }
                }
                else{
                    if(points[i].getColor()=="grey" && points[v].getParent()->getID()!=i){
                        points[v].setBack(min(points[v].getBack(),points[i].getDiscoverTime()));
                    }
                }
            }
        }
        points[v].setColor("black");
    }

    void Bridge(vector<tuple<int, int>>& bridges){
        for(int i=0; i<vex_; i++){
            if(points[i].getColor()=="white"){
                Bridge_DFS(0, bridges);
            }
        }
        sort(bridges.begin(), bridges.end());
        clear_UCGraph();
    }

    /**
     * ��ӡ�ڽӾ���
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
/*
int main(){
    int n = 5;
    //cin >> n;
    vector<tuple<int, int>> edges = {
            make_tuple(0,1),make_tuple(0,2),
            make_tuple(1,2),make_tuple(1,3),
            make_tuple(2,4)
    };
    UCGraph ucGraph(n,edges);

    vector<int> a_points;
    ucGraph.Articulation_Point(a_points);
    for(auto a: a_points){
        cout << a << endl;
    }

    vector<tuple<int, int>> bridges;
    ucGraph.Bridge(bridges);
    for(auto b: bridges){
        cout << get<0>(b) << " " << get<1>(b) << endl;
    }
}
 */