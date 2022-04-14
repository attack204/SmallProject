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
vector<string> v;
int N = 2, M = 4;
//若先手必胜返回1，否则返回0
bool judge(vector<string> &cur) {
    bool flag = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(cur[i][j] == 'O') {
                flag = 1;
                break;
            }
        }
        if(flag == 1) break;
    }
    if(!flag) return 1;
    flag = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(cur[i][j] == 'O') {
                cur[i][j] = 'X';
                if(judge(cur) == 0) flag = 1; 
                cur[i][j] = 'O'; 
            }

            if(cur[i][j] == 'O' && j + 1 < M && cur[i][j + 1] == 'O') {
                cur[i][j] =  cur[i][j + 1] = 'X';
                if(judge(cur) == 0) flag = 1;
                cur[i][j] =  cur[i][j + 1] = 'O';
            }

        }
    }
    // for(int i = 0; i < N; i++, puts("")) 
    //     for(int j = 0; j < M; j++) 
    //         cout << cur[i][j] << ' ';
    // cout << flag << '\n';
    return flag;
}
signed main() {
    //freopen("a.out", "w", stdout);
    for(int i = 0; i < N; i++) {
        string s;
        cin >> s;
        v.emplace_back(s);
    }
    if(judge(v)) cout << 'L';
    else cout << 'V';
    return 0;
}
/*
XOOO   
OOOO  

XXOO
OOOO

OXOO
OOOO

OXXO
OOOO
*/