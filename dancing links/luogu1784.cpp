#include <bits/stdc++.h>
using namespace std;

#define IT(i, A, S) for (int i = A[S]; i != S; i = A[i])
#define F(i, a, b) for (int i = a; i < b; ++i)
#define FE(i, a, b) for (int i = a; i <= b; ++i)
#define initd(d) memset(d, 0, sizeof(d))
#define scan(a) scanf("%d", &a)

const int MAXN = 1e6;

int blk[10][10];
/*
	sudoku
		row: 9(rows) * 9(cols) * 9(grids) = 729 represents total possibilities
		col: represents 4 conditions
			cond1: 81 blocks all contain valid numbers
			cond2: 9 rows, where each row contains one permutation of [1..9]
			cond3: 9 cols, where each col contains one permutation of [1..9]
			cond4: 9 grids, where each grid contains one permutation of [1..9]
		cond1: [0, 81)	 cond2: [81, 162)	cond3: [162, 243)	cond4: [243, 324)
		if all conditions satisfies for each possibility, then there are in total 729 * 4 one's
*/
struct dlx {
	int idx;
	int ans[MAXN];
	// HEAD: row head	C: number of nodes in a column
	int L[MAXN],  R[MAXN], U[MAXN], D[MAXN], HEAD[MAXN], C[MAXN];
	int row[MAXN], col[MAXN]; //row & col of an idx

	void init(int c) {
		idx = c;
		FE(i, 0, idx) L[i] = i - 1, R[i] = i + 1, U[i] = D[i] = i; //initialize header cols
		L[0] = idx, R[idx] = 0;
		initd(HEAD); initd(C);
	}

	void add(int& r, int& c) {
		row[++idx] = r, col[idx] = c, ++C[c];
		U[idx] = c, U[D[c]] = idx;
		D[idx] = D[c], D[c] = idx;
		if (HEAD[r]) L[idx] = HEAD[r], R[idx] = R[HEAD[r]], L[R[HEAD[r]]] = idx, R[HEAD[r]] = idx;
		else HEAD[r] = L[idx] = R[idx] = idx;
	}

	void fold(int& c) {
		// target column c in the selected row are folded
		R[L[c]] = R[c], L[R[c]] = L[c];
		/* rows conflict with the selected row are folded
			0 0 1 0 1 (selected row)
			0 1 1 0 1 (conflict)
		*/
		IT(i, D, c) IT(j, R, i) U[D[j]] = U[j], D[U[j]] = D[j], --C[col[j]];
	}

	void unfold(int& c) {
		IT(i, U, c) IT(j, L, i) U[D[j]] = D[U[j]] = j, ++C[col[j]];
		R[L[c]] = L[R[c]] = c;
	}

	bool dance(int k) { //k refers to k chosen rows
		int c = R[0];
		if (!c) {
			F(i, 1, k) {
				int x = (ans[i] - 1) / 9 / 9 + 1;
		        int y = (ans[i] - 1) / 9 % 9 + 1;
		        int v = (ans[i] - 1) % 9 + 1;
		        blk[x][y] = v;
			}
			return 1;
		}
		IT(i, R, 0) if (C[i] < C[c]) c = i;
		fold(c); //since IT skips c, it needs to be folded explicitly
		// choose a row undeterministically
		IT(i, D, c) {
			ans[k] = row[i]; //include row in the partial solution
			IT(j, R, i) fold(col[j]);
			if (dance(k + 1)) return 1;
			IT(j, L, i) unfold(col[j]);
		}
		unfold(c);
		return 0;
	}
};

dlx solver;

void append(int r, int c, int n) {
	int grid = ((r - 1) / 3) * 3 + ((c - 1) / 3) + 1;
	int id = (r - 1) * 81 + (c - 1) * 9 + n;
	int cond1 = (r - 1) * 9 + c;
	int cond2 = 81 + (c - 1) * 9 + n;
	int cond3 = 162 + (grid - 1) * 9 + n;
	int cond4 = 243 + (r - 1) * 9 + n;
	solver.add(id, cond1);
	solver.add(id, cond2);
	solver.add(id, cond3);
	solver.add(id, cond4);
}

void solve() {
	solver.init(324);
    FE(i, 1, 9) FE(j, 1, 9) {
    		scan(blk[i][j]);
    		FE(n, 1, 9) {
    			if (blk[i][j] && blk[i][j] != n) continue;
    			append(i, j, n);
    		}
    	}
    solver.dance(1);
    FE(i, 1, 9) {
    	FE(j, 1, 9) printf("%d\t", blk[i][j]);
    	nl;
    }
}

int main() {
    solve();
    return 0;
}
