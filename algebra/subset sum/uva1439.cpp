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
#define scan2(a, b) scanf(" %c %c", &a, &b)
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

// dp: minimum number of layers that can be constructed given a set of vertices
int edges[101], dp[1 << 15], optimal_layer[1 << 15];
bool independent[1 << 15];

// layer construction function
int construct_layer(int mask) {
	if (~dp[mask]) return dp[mask];
	dp[mask] = 101;
	for (int s = mask, cnt; s; s = (s - 1) & mask) { // all possible combinations of vertices
		if (independent[s]) {
			cnt = construct_layer(mask ^ s) + 1; // number of layers can be formed
			if (dp[mask] > cnt) {
				dp[mask] = cnt;
				optimal_layer[mask] = s; // store optimal vertices in the current layer
			}
		}
	}
	return dp[mask];
}

int main() {
    /*
		intuition: given a set of edges, find ways to connect those edges such that it doesn't 
		have circles, and then determine min longest_connected_path(c), where c is a valid connection
		To solve the problem, we can construct a set of layers, in which each layer consists of
		independent vertices, so that the longest path would be (number of layers - 1). The layers
		would be assigned colors in a descending order from top to bottom.
    */
    int n, mask = 0, cnt = 0; scan(n);
    vector<vector<int>> e(n, vector<int>(2));
    for (char a, b; n; --n, ++cnt) {
    	scan2(a, b);
    	int x = a - 'L', y = b - 'L';
    	mask |= (edges[cnt] = (1 << x) | (1 << y));
    	e[cnt][0] = x, e[cnt][1] = y;
    }
    // pre-determine independent vertices
    for (int s = mask; s; s = (s - 1) & mask) {
    	independent[s] = 1;
    	for (int i = 0; i < cnt; ++i) {
    		if ((s | edges[i]) == s) {
    			independent[s] = 0;
    			break;
    		}
    	}
    }
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    construct_layer(mask);
    printf("%d\n", dp[mask] - 2); // minus 2 since it starts from 0
    int color[15] = {};
    for (int s = mask, c = 0; s; s ^= optimal_layer[s], ++c)
    	F(i, 0, 15) if ((optimal_layer[s] >> i) & 1) color[i] = c; // vertices in same layer have same color

    F(i, 0, cnt) {
    	int a = e[i][0], b = e[i][1];
    	if (color[a] < color[b]) printf("%c %c\n", b + 'L', a + 'L'); // print first the vertices with larger color
    	else printf("%c %c\n", a + 'L', b + 'L');
    }

    return 0;
}