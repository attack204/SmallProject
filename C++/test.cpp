#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN = 4e5 + 10, INF = 1e9;
int numR, N, num;
queue<int> q;
int solution(char *s) {
    //cout << numR << '\n' << N;
    N = strlen(s);
    for(int i = 0; i < N; i++) numR += s[i] == 'R';
    if(numR == N) return 0;
    long long lR = 0, rR = 0, lW = 0, sumW = 0;
    for(int i = numR; i < N; i++) rR += (s[i] == 'R') * i;
    for(int i = 0; i < numR; i++) sumW += (s[i] == 'W') * i;
    long long ans = INF;
    //puts("G");
    for(int i = 0; i < N - numR + 1; i++) {
        //[i, i + numR - 1]
        long long now = rR - (sumW - lW) + lW - lR;
        if(now < ans) ans = now;
        if(i == N - numR) break;
        //cout << numR << '\n';
        //printf("%d %d %lld %lld %lld %lld\n", i, i + numR - 1, lR, rR, lW, sumW - lW);
        if(s[i + numR] == 'R') {
            rR -= i + numR;
        } else {
            q.push(i + numR);
            sumW += i + numR;
        }
        if(s[i] == 'R') {
            lR += i;
            num++;
            lW += q.front(); q.pop();
        } else {
            sumW -= i;
            if(num != 0) {
                lW -= i;
                lW += q.front(); q.pop(); 
            }
           
            //W
        }
    }
    return ans == INF ? 0 : ans;
}
int main() {
    //freopen("a.out", "w", stdout);
    //char s[] = "WRRWWR";
    char s[] = "WWRWWWRWR";
    //puts("G");
    cout << solution(s);
}