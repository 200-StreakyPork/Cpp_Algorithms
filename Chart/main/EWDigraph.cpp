//
//@Author  dell 
//@create 2019/5/7 ${Time}.
//

#include "..\include\EWDigraph.h"
#include "stdio.h"
using namespace std;

void EWDigraph::Print() {

}

void EWDigraph::BFST(const char start){
    //也可以使用queue, 区别是不能push_front
    std::deque<char> q;
    map<char, bool> vVisited;
    for (auto i : GetNodes()) {
        //所有顶点标记为未访问
        vVisited[i] = false;
    }
    //出发点入队列、
    q.push_front(start);
    cout << "BFST(" << start << "):"<<endl;
    while (!q.empty()){
        //读取队列头
        char node = q.front();
        q.pop_front();
        if (!vVisited[node]){
            //将队列头设置为已访问
            vVisited[node] = true;
            //打印顶点
            cout << node << "-";
        }
        for (auto j : ewd_[node]){
            //把队列头指向的所有未访问的顶点压入队尾
            if (!vVisited[j.first]){
                q.push_back(j.first);
            }
        }
        if (q.empty()){
            //检查图中是否还有顶点未访问。如果是，则将该顶点入队列
            for (auto i : GetNodes()){
                if (!vVisited[i]){
                    q.push_back(i);
                    break;
                }
            }
        }
    }
    cout << "end";
    cout << endl;
}
