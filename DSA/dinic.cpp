template<int SZ> struct Dinic {
    struct Edge { int v, rev; ll flow, cap; };

    vector<Edge> adj[SZ];

    void addEdge(int u, int v, ll cap) {
      //  cout << u << " " << v << " " << cap << newl;
        assert(cap >= 0); // don't do smth dumb
        Edge a{v, sz(adj[v]), 0, cap}, b{u, sz(adj[u]), 0, 0};
        adj[u].pb(a), adj[v].pb(b);
    }

    int ST, EN, level[SZ], ind[SZ];

    bool bfs() { // level = shortest distance from source
        // after computing flow, edges {u,v} such that level[u] \neq -1, level[v] = -1 are part of min cut
        for(int i=0;i<SZ;++i) level[i] = -1, ind[i] = 0;
        level[ST] = 0;
        queue<int> q; q.push(ST);
        while (sz(q)) {
            int u = q.front(); q.pop();
            for(auto e:adj[u]) if (level[e.v] < 0 && e.flow < e.cap) {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
        return level[EN] >= 0;
    }

    ll sendFlow(int s, ll flow) {
        if (s == EN) return flow;
        for (  ; ind[s] < sz(adj[s]); ind[s] ++) {
            Edge& e = adj[s][ind[s]];
            if (level[e.v] != level[s]+1 || e.flow == e.cap) continue;
            ll f = sendFlow(e.v, min(flow, e.cap-e.flow));
            if (f) { // saturated at least one edge
                e.flow += f; adj[e.v][e.rev].flow -= f;
                return f;
            }
        }
        return 0;
    }

    ll maxFlow(int _ST, int _EN) {
        ST = _ST, EN = _EN; if (ST == EN) return -1;
        ll tot = 0;
        while (bfs()) while (auto flow = sendFlow(ST, LLONG_MAX)) tot += flow;
        return tot;
    }
};
