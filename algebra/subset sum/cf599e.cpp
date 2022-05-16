#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
using ll = long long;
using ul = unsigned long;
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
#define cbit(x, i) ((x) ^ (i))
#define isBitSet(x, i) ((x >> i) & 1)
template<typename... args>
void dbg(args... arg) {
	__attribute__((unused)) auto _ = {((void)(cout << arg << "  "), 0)...};
	nl;
}
#define chq printf("%s\n", "current line is ok...")
#define scan(d) scanf("%d", &d)
#define scan2(a, b) scanf("%d%d", &a, &b)
#define scan3(a, b, c) scanf("%d%d%d", &a, &b, &c)
#define scans(s) scanf("%s", s)
#define initd(d) memset(d, 0, sizeof(d))
#define loc(v, ele) lower_bound(v.cbegin(), v.cend(), ele) - v.cbegin()
#define qnav do { \
	freopen("/home/drac/Documents/CP/input.txt", "r", stdin); \
    setbuf(stdout, NULL); \
    freopen("/home/drac/Documents/CP/output.txt", "w", stdout); \
} while (0)

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

ull binp(ull x, ull y) {
	x %= MOD;
	ull res = 1;
	while (y) {
		if (y & 1) res = res * x % MOD;
		x = x * x % MOD;
		y >>= 1;
	}
	return res;
}

int Gcd_Ext(int a, int b, int& x, int& y) {
	int x1 = 0, y1 = 1, q;
	while (b) {
		q = a / b;
		tie(x, x1) = mt(x1, x - q * x1);
		tie(y, y1) = mt(y1, y - q * y1);
		tie(a, b) = mt(b, a - q * b);
	}
	return a;
}

ll dp[14][1 << 14];
int n, m, q, a[101], b[101], c[101];
bool edge[14][14];
/*
	dp(root, root's subtree nodes) = Σ dp(child, child's subtree nodes) * dp(root, subtree nodes excluding child) 
	final answer is dp(0, (1 << n) - 1)

	should ignore the following cases
	 1) if lca(a, b) = c but c and one of (a, b) do not belong to the same subtree, or if
	 	c is the root, but (a, b) belongs to one of its subtrees
	 2) for an edge (u, v) where u ≠ v ≠ root, such that u and v are not in the same subtree
	 3) there exists more than one node in a subtree that connects with root

	since we are to traverse all subtrees, we can choose a particular node and traverse only the
	subtrees containing that node, thereby eliminating unnecessary repetitions
*/
ll solve(int root, int mask) {
	if (dp[root][mask]) return dp[root][mask];
	int t = 0, submask = cbit(mask, 1 << root);
	for (; t < n; ++t) if (isBitSet(submask, t)) break; // select a particular node
	for (int s = submask; s; s = submask & (s - 1)) {
		if (!isBitSet(s, t)) continue; // traverse only the subtrees containing the node
		bool flg = 0;
		if (q) { // case 1
			for (int i = 0; i < q && !flg; ++i) 
				if ((c[i] == root && isBitSet(s, a[i]) && isBitSet(s, b[i])) || 
					(isBitSet(s, c[i]) && (!isBitSet(s, a[i]) || !isBitSet(s, b[i])))) 
					flg = 1;
			if (flg) continue;
		}
		int cnt = 0, new_root = 0;
		if (m) {
			flg = 0;
			for (int i = 0; i < n && !flg; ++i) {
				if (i == root) continue;
				for (int j = 0; j < n; ++j) {
					if (j == root || !edge[i][j]) continue;
					if (isBitSet(s, i) ^ isBitSet(s, j)) { // case 2
						flg = 1;
						break;
					}
				}
			}
			if (flg) continue;
			for (int i = 0; i < n && cnt < 2; ++i) 
				if (edge[i][root] && isBitSet(s, i)) 
					++cnt, new_root = i; // case 3
			if (cnt > 1) continue;
		}
		if (cnt) // if only one node connecting with root, then it must be the root of current subtree
			dp[root][mask] += solve(new_root, s) * solve(root, cbit(mask, s));
		else // if no nodes connecting with root, then use nodes the current subtree as new roots
			for (new_root = 0; new_root < n; ++new_root) 
				if (isBitSet(s, new_root)) 
					dp[root][mask] += solve(new_root, s) * solve(root, cbit(mask, s));
	}
	return dp[root][mask];
}

int main() {
    //qnav;
    int mask;
    scan3(n, m, q);
    mask = (1 << n) - 1;
    for (int i = 0, u, v; i < m; ++i) {
    	scan2(u, v);
    	edge[u - 1][v - 1] = edge[v - 1][u - 1] = 1;
    }
    for (int i = 0, x, y, z; i < q; ++i) {
    	scan3(x, y, z);
    	a[i] = --x, b[i] = --y, c[i] = --z;
    }
    for (int i = 0; i < n; ++i) dp[i][1 << i] = 1; // corner cases, where the tree contains a single node
    printf("%lld", solve(0, mask));
    return 0;
}