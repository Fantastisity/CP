#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
using ll = long long;
using ul = unsigned long;
using u128 = __uint128_t;
using ull = unsigned long long;

const int dir[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

// #define CUST_PAIR
// #define BST
#define mp make_pair
#define mt make_tuple
#define nl puts("")
#define pb push_back
#define fst(v) (*v.cbegin())
#define lst(v) (*v.crbegin())
#define tint(s, i) (s[i] - '0')
#define cint(i) (i + '0')
#define tchar(s, i) (s[i] - 'a')
#define FA(i, v) for (auto& i : (v))
#define F(i, a, b) for (int i = a; i < b; ++i)
#define FE(i, a, b) for (int i = a; i <= b; ++i)
#define FG(i, a, b) for (int i = a; i > b; --i)
#define FGE(i, a, b) for (int i = a; i >= b; --i)
#define tr(it, x, ed) for (auto it = (x).begin(), ed = (x).end(); it != ed; ++it)
#define eq(a, b) (!(a ^ b))
#define sz(x) ((int)((x).size()))
#define lbit(x) ((x & (-x))) // get lowest bit
#define all(c) (c).begin(),(c).end()
#define rall(c) (c).rbegin(),(c).rend()
#define mid(l, r) (l + ((r - l) >> 1))
#define lft(l) (l << 1)
#define rht(r) ((r << 1) + 1)
#define has(v, ele) (v.find(ele) != v.end())
template<typename... args>
void dbg(args... arg) {
	__attribute__((unused)) auto _ = {((void)(cout << arg << "  "), 0)...};
	nl;
}
#define chq printf("%s\n", "current line is ok...")
#define scan(d) scanf("%d", &d)
#define scanu(d) scanf("%llu", &d)
#define scans(s) scanf("%s", s)
#define initd(d) memset(d, 0, sizeof(d))
#define loc(v, ele) lower_bound(v.cbegin(), v.cend(), ele) - v.cbegin()

const int MAXN = 10000;
const int MOD = 1000000007;

#ifdef CUST_PAIR
template <typename T>
inline void hash_combine(std::size_t &seed, const T &val) {
    seed ^= hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
// auxiliary generic functions to create a hash value using a seed
template <typename T> inline void hash_val(size_t &seed, const T &val) {
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template <typename... Types>
inline size_t hash_val(const Types &... args) {
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};

struct pair_comp {
    inline bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
        return a.first < b.first && a.second < b.second;
    }
};
#endif

#ifdef BST
typedef struct treenode {
	struct treenode* left;
	struct treenode* right;
	int val;
} node;

node nd[SIZE];
queue<node*> q;

void init() {
	F(i, 0, SIZE) q.push(&nd[i]);
}

node* newnode(int val = -1) {
	node* cur = q.front(); q.pop();
	cur->left = cur->right = nullptr;
	cur->val = val;
	return cur;
}
#endif

ull binp(ull& x, ull& y, ull& mod) {
	x %= mod;
	ull res = 1;
	while (y) {
		if (y & 1) res = (u128)res * x % mod;
		x = (u128)x * x % mod;
		y >>= 1;
	}
	return res;
}

bool check_comp(ull& n, ull& a, ull& d, int& s) {
	/*
		Miller-Rabin
		suppose n is odd, then n - 1 = 2^s * d with d being odd.
		given 1 < a < n, by FLT,
			a^(n - 1) = a^(2^s * d) = 1 (mod n) => a^(2^s * d) - 1 = 0 (mod n)
							    => (a^(2^(s - 1) * d) + 1) * (a^(2^(s - 1) * d) - 1) = 0 (mod n)
							    => (a^(2^(s - 1) * d) + 1) * (a^(2^(s - 2) * d) + 1) ... (a^d + 1) * (a^d - 1) = 0 (mod n)
		∴ two possible solutions exist
			(1) a^d = 1 (mod n)
			(2) a^(2^r * d) = -1 (mod n) ∀r ∈ {0, s - 1}. However, since a, n > 0, ∴ -1 needs to plus n to get the positive remainder before -1
	*/
	ull x = binp(a, d, n);
	if (x == 1 || x == n - 1) return 0; // case when n is even
	F(i, 1, s) {			    // solution (2)
		x = (u128)x * x % n;
		if (x == n - 1) return 0;
	}
	return 1;
}

bool MR(ull& n) {
	if (n < 2) return 0;
	int r = 0;
	ull d = n - 1;
	while (!(d & 1)) d >>= 1, ++r;	   // retrieve odd d
	for (ull a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {	// first 12 prime bases are enough for checking the primality of any 64-bit integer
		if (n == a) return 1;
		if (check_comp(n, a, d, r)) return 0;
	}
	return 1;
}

int main() {
    int n; ull q; scan(n);
    while (n--) scanu(q), cout << (MR(q) ? "YES" : "NO"), nl;
    return 0;
}
