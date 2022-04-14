//CF 10D

#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 505;
int a[maxn], b[maxn], dp[maxn], n, m, step[maxn];
void print(int x) {
    if(x == 0) return;
    print(step[x]);
    printf("%d ", b[x]);
}

int main()
{
    freopen("a.in", "r", stdin);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) scanf("%d", &b[i]);

    for(int i = 1; i <= n; i++) {
        int pos = 0;
        for(int j = 1; j <= m; j++) {
            if(a[i] == b[j]) {
                dp[j] = dp[pos] + 1;
                step[j] = pos;
            }
            if(a[i] > b[j] && dp[pos] < dp[j]) {
                pos = j;
            }
        }
    }

    int ans = 0, ans2 = 0;
    for(int i = 1; i <= m; i++) {
        if(dp[i] > ans2) {
            ans2 = dp[i], ans = i;
        }
    }
    printf("%d\n", ans2);
    print(ans);
    return 0;
}
