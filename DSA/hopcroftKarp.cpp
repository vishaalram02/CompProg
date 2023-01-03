//for unweighted bipartite matching

bool dfs(int a, int L, vector<vector<int>>& g, vector<int>& btoa, vector<int>& A, vector<int>& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for(auto b:g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vector<int>>& g, vector<int>& btoa) {
	int res = 0;
	vector<int> A(g.size()), B(btoa.size()), cur, next; 
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);

		cur.clear();
		for(auto a:btoa) if(a != -1) A[a] = -1;
		for(int a=0;a<sz(g);++a) if(A[a] == 0) cur.pb(a);

		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for(auto a:cur) for(auto b:g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.pb(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for(auto a:next) A[a] = lay;
			cur.swap(next);
		}
		
		for(int a=0;a<sz(g);++a)
			res += dfs(a, 0, g, btoa, A, B);
	}
}
