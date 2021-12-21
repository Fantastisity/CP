#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define fst(v) (*v.cbegin())
#define lst(v) (*v.crbegin())
#define tint(s, i) (s[i] - '0')
#define cint(i) (i + '0')
#define tchar(s, i) (s[i] - 'a')
#define FA(i, v) for (auto& i : (v))
#define F(i, a, b) for (int i = a; i < (int)b; ++i)
#define FE(i, a, b) for (int i = a; i <= (int)b; ++i)
#define FG(i, a, b) for (int i = a; i > b; --i)
#define FGE(i, a, b) for (int i = a; i >= b; --i)
#define tr(it, x) for (auto it = (x).begin(), ed = (x).end(); it != ed; ++it)
#define eq(a, b) (!(a ^ b))
#define sz(x) ((int)((x).size()))
#define lbit(x) ((x)&((x)^((x)-1))) // get lowest bit
#define all(c) (c).begin(),(c).end()
#define rall(c) (c).rbegin(),(c).rend()
#define mid(l, r) (l + ((r - l) >> 1))
#define lft(l) (l << 1)
#define rht(r) ((r << 1) + 1)
#define has(v, ele) (v.count(ele) > 0)
#define dbgd(d, e) printf("(%d,%d) ", d, e)
#define dbgc(c) printf("%s\n", c)
#define dbg printf("%s\n", "No Solution Possible")
#define loc(v, ele) lower_bound(v.cbegin(), v.cend(), ele) - v.cbegin()

const int SIZE = 10000;
const int MOD = 1000000007;

static const auto _ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return nullptr;
}();

typedef vector<int> vi;
typedef pair<pair<int, int>, int> ppp;
using ll = long long;
using ul = unsigned long;
using ull = unsigned long long;

struct pair_comp {
    inline bool operator() (const ppp& a, const ppp& b) const {
        return a.second > b.second;
    }
};

template <typename T>
inline void hash_combine(size_t &seed, const T &val) {
    seed ^= hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T> inline void hash_val(size_t &seed, const T &val) {
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template <typename... Types>
inline std::size_t hash_val(const Types &... args) {
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};

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

unordered_map<pair<int, int>, vector<vector<pair<int, int>>>, pair_hash> um;
int dist[10][10][4];
vector<pair<int, int>> pred;
pair<int, int> cur;
int dir[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
enum direction {
	N, S, W, E
};
pair<int, int> res;
vector<vector<pair<int, int>>> uu(4, vector<pair<int, int>>());
void convert(const char* c, char prev) {
	while (*c != '\0') {
		switch(prev) {
			case 'N':{
				if (*c == 'F') res = mp(E, N);
				else if (*c == 'L') res = mp(S, W);
				else if (*c == 'R') res = mp(N, E);
				uu[N].push_back(res);
				break;
			}
			case 'S': {
				if (*c == 'F') res = mp(W, S);
				else if (*c == 'L') res = mp(N, E);
				else if (*c == 'R') res = mp(S, W);
				uu[S].push_back(res);
				break;
			}
			case 'W': {
				if (*c == 'F') res = mp(S, W);
				else if (*c == 'L') res = mp(W, S);
				else if (*c == 'R') res = mp(E, N);
				uu[W].push_back(res);
				break;
			}
			case 'E': {
				if (*c == 'F') res = mp(N, E);
				else if (*c == 'L') res = mp(E, N);
				else if (*c == 'R') res = mp(W, S);
				uu[E].push_back(res);
				break;
			}
		}
		++c;
	}
	um[cur] = uu;
}

pair<int, int> start, dest;
int xx = 0;

void print_path() {
	F(i, 0, pred.size()) {
		dbgd(pred[i].first, pred[i].second);
		if (eq(i, 9)) puts("");
	}
	
}

void bfs() {
	queue<ppp> pq;
	pq.push(mp(start, xx));
	dist[start.first][start.second][xx] = 1;
	while (!pq.empty()) {
		ppp now = pq.front(); pq.pop();
		pred.push_back(mp(now.first.first, now.first.second));
		if (now.first == dest) {
			print_path();
			return;
		}	
		if (um[now.first][now.second].size() > 0) {
			FA(i, um[now.first][now.second]) {
				int x = dir[i.first][0] + now.first.first,
					y = dir[i.first][1] + now.first.second;
				if (!dist[x][y][i.second]) {
					dist[x][y][i.second] = 1;
					pq.push(mp(mp(x, y), i.second));
				}
			}
		}
	}
	dbg;
}


void solve() {
    char title[11];
    char sd[5];
    while (scanf("%s", title) && strcmp(title, "END")) {
    	printf("%s\n", title);
    	memset(dist, 0, sizeof(dist));
    	scanf("%d%d%s%d%d", &start.first, &start.second, sd, &dest.first, &dest.second);
    	char tmp = *sd;
    	vector<vector<pair<int, int>>> place(4, vector<pair<int, int>>());
    	if (tmp == 'N') res = mp(E, N);
		else if (tmp == 'E') res = mp(N, E);
		else if (tmp == 'W') res = mp(S, W);
		else if (tmp == 'S') res = mp(W, S);
		xx = res.second;
		place[xx].push_back(res);
		um[start] = place;
    	while (scanf("%d", &cur.first) && cur.first) {
    		scanf("%d", &cur.second);
    		uu.clear(); uu.resize(4, vector<pair<int, int>>());
    		while (scanf("%s", sd) && strcmp(sd, "*")) {
    			convert(sd + 1, sd[0]);
    		}
    	}
    	bfs();
    	puts("");
    }
}

int main() {
    solve();
    return 1;
}
