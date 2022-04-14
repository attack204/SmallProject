#include<bits/stdc++.h> 
#define Pair pair<int, int>
#define MP(x, y) make_pair(x, y)
#define fi first
#define se second
#define pb push_back 
//#define int long long 
#define ll long long 
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
inline LL read() {
    char c = getchar(); LL x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

using namespace std;

const int prime[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

inline ll qmul(ll a, ll b, ll mod) {
	return (a * b - (ll)((long double)a * b / mod) * mod + mod) % mod;
}

inline ll qpow(ll a, ll b, ll mod) {
	ll ans = 1 % mod, x = a % mod;
	while (b) {
		if (b & 1) ans = qmul(ans, x, mod);
		x = qmul(x, x, mod), b >>= 1;
	}
	return ans;
}

ll maxp;

inline int miller_rabin(ll x) {
	if (x < 2) return 0;
	for (int i = 0; i < 11; ++i)
		if (x == prime[i]) return 1;
	for (int i = 0; i < 11; ++i) {
		ll d = x - 1;
		int r = 0, flag = 0;
		while (d % 2 == 0) d /= 2, ++r;
		ll a = qpow(prime[i], d, x);
		if (a == 1) continue;
		for (int j = 0; j < r; ++j) {
			if (a == x - 1) {
				flag = 1;
				break;
			}
			a = qmul(a, a, x);
		}
		if (!flag) return 0;
	}
	return 1;
}

inline ll f(ll x, ll c, ll mod) {
	return (qmul(x, x, mod) + c) % mod;
}

inline ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

inline ll getd(ll x) {
	ll c = rand() % x, s = 0, t = 0, val = 1;
	for (int goal = 1; ; goal *= 2, s = t, val = 1) {
		for (int step = 1; step <= goal; ++step) {
			t = f(t, c, x);
			val = qmul(val, abs(s - t), x);
			if (step % 127 == 0) {
				ll d = gcd(val, x);
				if (d > 1) return d;
			}
		}
		ll d = gcd(val, x);
		if (d > 1) return d;
	}
}

void pollard_rho(ll x) {
	if (x < maxp || x < 2) return;
	if (miller_rabin(x)) {
		if (x > maxp) maxp = x;
		return;
	}
	ll p = x;
	while (p == x) p = getd(x);
	while (x % p == 0) x /= p;
	pollard_rho(x), pollard_rho(p);
}

int main() {
  //  freopen("a.in", "r", stdin);

	ll t = read();
	while (t--) {
		ll x = read();
		maxp = 0;
		pollard_rho(x);
        ll a1 = 0;
        while(x % maxp == 0) a1++, x /= maxp;
        maxp = 0;
        pollard_rho(x);
        ll a2 = 0;
        while(x % maxp == 0) a2++, x /= maxp;
     //   printf("%d %d %d %d\n", pre,  a1, maxp, a2);
        puts((a1 >= 2 && a2 == 0 && x == 1) || (a1 >= 2 && a2 >= 2 && x == 1)  ? "yes" : "no");
	}
	return 0;
}
