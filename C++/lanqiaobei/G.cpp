#include<bits/stdc++.h> 
#define Pair pair<int, int>
#define MP(x, y) make_pair(x, y)
#define fi first
#define se second
#define pb push_back 
//#define int long long 
#define LL long long 
#define ull unsigned long long 
#define Fin(x) {freopen(#x".in","r",stdin);}
#define Fout(x) {freopen(#x".out","w",stdout);}
using namespace std;
const int MAXN = 2e6 + 10, mod = 1e9 + 7, INF = 1e9 + 10;
const double eps = 1e-9;
template <typename A, typename B> inline bool chmin(A &a, B b){if(a > b) {a = b; return 1;} return 0;}
template <typename A, typename B> inline bool chmax(A &a, B b){if(a < b) {a = b; return 1;} return 0;}
template <typename A, typename B> inline LL add(A x, B y) {if(x + y < 0) return x + y + mod; return x + y >= mod ? x + y - mod : x + y;}
template <typename A, typename B> inline void add2(A &x, B y) {if(x + y < 0) x = x + y + mod; else x = (x + y >= mod ? x + y - mod : x + y);}
template <typename A, typename B> inline LL mul(A x, B y) {return 1ll * x * y % mod;}
template <typename A, typename B> inline void mul2(A &x, B y) {x = (1ll * x * y % mod + mod) % mod;}
template <typename A> inline void debug(A a){cout << a << '\n';}
template <typename A> inline LL sqr(A x){return 1ll * x * x;}
template <typename A, typename B> inline LL fp(A a, B p, int md = mod) {int b = 1;while(p) {if(p & 1) b = mul(b, a);a = mul(a, a); p >>= 1;}return b;}
template <typename A> A inv(A x) {return fp(x, mod - 2);}
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, K;
int a[MAXN];
int Tree[MAXN];
#define lb(x) (x & (-x))
#define MAX (1000000)
int query(int x) {
    int ans = 0;
    while(x) {
        ans = max(ans, Tree[x]);
        x -= lb(x);
    }
    return x;
}
void insert(int x, int v) {
    while(x <= MAX) {
        Tree[x] = max(Tree[x], v);
        x += lb(x);
    }
}
int f[MAXN], ff[MAXN], g[MAXN], gg[MAXN], b[MAXN];
signed main() {
    freopen("a.in", "r", stdin);
    N = read(); K = read();
    for(int i = 1; i <= N; i++) {
        cin >> a[i];
        if(a[i] <= K) {
           f[i] = 1 + query(a[i]);
           ff[i] = max(ff[i - 1], f[i]);
           insert(a[i], f[i]);
        }
    }
    memset(Tree, 0, sizeof(Tree));
    set<int> s;
    for(int i = N; i >= 1; i--) {
        if(a[i] >= K) {
            if(b[a[i]]) {
                b[a[i]]++; 
                g[i] = b[a[i]];
            }
            else {
                auto pos = s.lower_bound(a[i]);
                if(pos == s.end()) {
                    g[i] = b[a[i]] = 1;
                } else {
                    g[i] = b[a[i]] = b[*pos] + 1;
                }
            }
            gg[i] = max(gg[i + 1], g[i]);
            s.insert(a[i]);
        }
    }
    int ans = 0;
    for(int i = 1; i <= N - K + 1; i++) {
        ans = max(ans, ff[i - 1] + K + gg[i + K]);
    }
    cout << ans;
    return 0;
}
