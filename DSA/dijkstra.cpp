template<int SZ> struct D {
    ll dist[SZ];
    vector<pii> adj[SZ];
    pqg<pair<ll,ll>> q;

    void addEdge(int A, int B, int C) {
        adj[A].pb({B,C}); // adj[B].pb({A,C}); if undirected
    }

    void init(int st) {
        fill_n(dist,SZ,INF);
        q = pqg<pair<ll,ll>>(); q.push({dist[st] = 0,st});
    	while (sz(q)) {
    		auto x = poll(q); if (dist[x.s] < x.f) continue;
    		for(auto y:adj[x.s]) if (x.f+y.s < dist[y.f])
    			q.push({dist[y.f] = x.f+y.s,y.f});
    	}
    }
};
