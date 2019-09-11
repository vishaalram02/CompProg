#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vii;
typedef pair<int,int> pii;

#define sync ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define sz(a) int((a).size())
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()
#define allr(c) (c).rbegin(),(c).rend()
#define newl '\n'


ll bit[100005];
vi adj[100005];
int pos[100005];
int ans[100005];


ll sum(ll x) {
    ll ret = 0;
    for (ll i = x; i >= 0; i = (i & (i + 1)) - 1)
        ret += bit[i];
    return ret;
}
void add(ll x, ll delta) {
    for (ll i = x; i < 100005; i = i | (i + 1))
        bit[i] += delta;
}

void dfs(int v, int p){
    ans[pos[v]] = sum(pos[v]);
    add(pos[v], 1);
    for(auto u:adj[v]) if(u != p) dfs(u,v);
    add(pos[v],-1);
}

int main(){ sync;
   // ifstream cin("/Users/Vishaal Ram/Downloads/input.txt");
   // ofstream cout("/Users/Vishaal Ram/Downloads/output.txt");

    int n; cin >> n;
    for(int i=0;i<n-1;++i){
        int x,y; cin >> x >> y;
        adj[x].pb(y); adj[y].pb(x);
    }
    for(int i=1;i<=n;++i){
        int x; cin >> x;
        pos[x] = i;
    }

    dfs(1,0);
    for(int i=1;i<=n;++i) cout << ans[i] << newl;
    return 0;
}
