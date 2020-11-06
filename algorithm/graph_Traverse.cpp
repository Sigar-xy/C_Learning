#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<cstdlib>
using namespace std;
const int maxn = 1000;
int n, G[maxn][maxn];//n为节点数量， G为邻接矩阵存储方式
bool isvisit[maxn] = {false};//判断是否访问过
bool ispush[maxn] = {false};//BFS的判断是否如果队
vector<int> g_map[maxn];//邻接表方式
//邻接矩阵
void DFS(int node, int depth) {
    isvisit[node] = true;
    for(int i = 0; i < n; i++) {
        if(isvisit[i] == false && G[node][i] != -1) {
            DFS(i, depth + 1);
        }
    }
}
//邻接表
void DFS_(int node, int depth) {
    isvisit[node] = true;
    for(int i = 0; i < g_map[node].size(); i++) {
        int kid = g_map[node][i];
        if(isvisit[kid] == false) {
            DFS_(kid, depth + 1);
        }
    }
}
//邻接矩阵 广度优先搜索
void BFS(int node) {
    queue<int> q;
    q.push(node);
    ispush[node] = true;
    while(!q.empty()) {
        int front = q.front();
        q.pop();
        for(int i = 0; i < n; i++) {
            if(ispush[i] == false && G[node][i] != -1) {
                q.push(i);
                ispush[i] = true;
            }
        }

    }
}
//邻接表 广度优先搜索
void BFS_(int node) {
    queue<int> q;
    q.push(node);
    ispush[node] = true;
    while(!q.empty()) {
        int front = q.front();
        q.pop();
        for(int i = 0; i < g_map[front].size(); i++) {
            int j = g_map[front][i];
            if(ispush[j] == false) {
                q.push(j);
                ispush[j] = true;
            }
        }
    }
}
void visitG() {
    for(int i = 0; i < n; i++) {
        if(isvisit[i] == false) {
            //DFS(i, 1);
            BFS(i);
        }
    }
}
int main() {
    system("pause");
    return 0;
}