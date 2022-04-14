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
const int MAXN = 1e6 + 10, mod = 1e9 + 7, INF = 1e9 + 10;
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
int N, X;
int check(int step, vector<int> v) {
    for(int i = 1; i <= 2 * X; i++) {
        if(i & 1) {

        } else {
            
        }
    }
}
signed main() {
    N = read(); X = read();
    vector<int> v;
    for(int i = 1; i <= N; i++) {
        int x = read();
        v.emplace_back(x);
    }
    int l = 1, r = N, ans = N;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid, v)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    cout << ans;
    return 0;
}
