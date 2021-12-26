#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int dir[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

// #define CUST_PAIR
// #define BST
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
#define scan7(a, b, c, l1, r1, l2, r2) scanf("%d%d%d%d%d%d%d\n", &a, &b, &c, &l1, &r1, &l2, &r2)
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

typedef vector<int> vi;
using ll = long long;
using ul = unsigned long;
using ull = unsigned long long;

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

void calc(int& x, int& y, int cnt, int a, int b) {
	x += cnt * b;
	y -= cnt * a;
}

int main() {
    int n, a, b, c, lx, rx, ly, ry, lx1, rx1, lx2, rx2;
    scan(n);
    for (int i = 1, gcd, x, y; i <= n; ++i) {
    	scan7(a, b, c, lx, rx, ly, ry);
    	if (!a && !b && !c) {
    		cout << "Case " << i << ": " << ((rx - lx + 1) * (ry - ly + 1)) << endl; 
    		continue;
    	}

    	if (!a && !b) {
    		cout << "Case " << i << ": " << 0 << endl; 
    		continue;
    	}

    	if (!a) {
    		cout << "Case " << i << ": " << ((c % b || ly > c / b || ry < c / b) ? 
    		    				  0 : rx - lx + 1) << endl;
    		continue;
    	}

    	if (!b) {
    		cout << "Case " << i << ": " << ((c % a || lx > c / a || rx < c / a) ? 
    		    				  0 : ry - ly + 1) << endl;
    		continue;
    	}

    	x = 1, y = 0, gcd = Gcd_Ext(a, b, x, y);
        if (a < 0) x = -x;
        if (b < 0) y = -y;
    	a /= gcd, b /= gcd, x *= -c / gcd, y *= -c / gcd;
    	int sign_a = a > 0 ? 1 : -1, sign_b = b > 0 ? 1 : -1;
    	calc(x, y, (lx - x) / b, a, b);
    	if (x < lx) calc(x, y, sign_b, a, b);
    	if (x > rx) {
    		cout << "Case " << i << ": " << 0 << endl;
    		continue;
    	}
    	lx1 = x;
	calc(x, y, (rx - x) / b, a, b);
	if (x > rx) calc(x, y, -sign_b, a, b);
	rx1 = x;

	calc(x, y, (y - ly) / a, a, b);
    	if (y < ly) calc(x, y, -sign_a, a, b);
    	if (y > ry) {
    		cout << "Case " << i << ": " << 0 << endl;
    		continue;
    	}
    	lx2 = x;
	calc(x, y, (y - ry) / a, a, b);
	if (y > ry) calc(x, y, sign_a, a, b);
	rx2 = x;

	if (rx2 < lx2) swap(rx2, lx2);
	lx = max(lx1, lx2), rx = min(rx1, rx2);
	if (lx > rx) {
		cout << "Case " << i << ": " << 0 << endl;
    		continue;
	}
	cout << "Case " << i << ": " << (rx - lx) / abs(b) + 1 << endl;
    }
    return 0;
}
