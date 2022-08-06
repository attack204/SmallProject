#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
using namespace std;
const int MAXN = 4e5 + 10, INF = 1e9 + 10;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int K, N, S, T;
int need[MAXN];
vector<int>ans[MAXN];
struct Edge {
    int u, v, f, nxt;
}E[MAXN];
int head[MAXN], cur[MAXN], num;
inline void add_edge(int x, int y, int f) {
    E[num] = (Edge){x, y, f, head[x]};
    head[x] = num++;
}
inline void AddEdge(int x, int y, int z) {
    add_edge(x, y, z);
    add_edge(y, x, 0);
}
int sum = 0, deep[MAXN];
bool BFS() {
    queue<int> q; q.push(S);
    memset(deep, 0, sizeof(deep)); deep[S] = 1;
    while(!q.empty()) {
        int p = q.front(); q.pop();
        for(int i = head[p]; i != -1; i = E[i].nxt) {
            int to = E[i].v;
            if(!deep[to] && E[i].f) {
                deep[to] = deep[p] + 1;
                q.push(to);
            }
        }
    }
    return deep[T] > 0;
}
int DFS(int x, int flow) {
    if(x == T) return flow;
    int ansflow = 0;
    for(int &i = cur[x]; i != -1; i = E[i].nxt) {
        int to = E[i].v;
        if(deep[to] == deep[x] + 1 && E[i].f) {
            int nowflow = DFS(to, min(flow, E[i].f));
            E[i].f -= nowflow; E[i ^ 1].f += nowflow;
            ansflow += nowflow; flow -= nowflow;
            if(flow <= 0) break;
        }
    }
    return ansflow;
}
int Dinic() {
    int ans = 0;
    while(BFS()) {
        memcpy(cur, head, sizeof(head));
        ans += DFS(S, INF);
    }
    return ans;
}
int solution(int A[], int B[], int N, int _S) {
    memset(head, -1, sizeof(head));
    K = _S; 
    S = 0; 
    T = N + K + 1;
    int sum = N;
    for(int i = 1; i <= K; i++) {
        AddEdge(N + i, T, 1);
    }
    for(int i = 1; i <= N; i++) {
        AddEdge(S, i, 1);
        AddEdge(i, N + A[i - 1], 1);
        AddEdge(i, N + B[i - 1], 1);
    }
    return Dinic() == N;
}
int main() {
    // int A[] = {1, 1, 3};
    // int B[] = {2, 2, 1};
    // int N = 3;
    // int S = 3;
    // cout << solution(A, B, N, S);

    // int A[] = {3, 2, 3, 1};
    // int B[] = {1, 3, 1, 2};
    // int N = 4;
    // int S = 3;
    // cout << solution(A, B, N, S);


    // int A[] = {2, 5, 6, 5};
    // int B[] = {5, 4, 2, 2};
    // int N = 4;
    // int S = 8;
    // cout << solution(A, B, N, S);

    int A[] = {1, 2, 1, 6, 8, 7, 8};
    int B[] = {2, 3, 4, 7, 7, 8, 7};
    int N = 7;
    int S = 10;
    cout << solution(A, B, N, S);
    return 0;
}