#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

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

ll ans = 0;
int n, bx, by;
map<pii,char> m;
map<int,vi> X,Y;
vector<pair<pii,int>> oh, bh;
vector<pair<int,pii>> ov, bv;

vector<pii> path(int xx, int yy, char d){
    map<pair<pii,char>,bool> vis;
    vector<pii> p;
    int x = xx, y = yy; char dir = d;
    bool done = 0;
    p.pb({x,y});
    while(!done){
        if(dir == 'N'){
            auto z = upper_bound(all(X[x]), y);
            if(z == X[x].end()){
                y = 1e9+1;
                done = 1;
            } else{
                y = *z;
                char c = m[{x,y}];
                if(c == '\\') dir = 'W';
                else if(c == '/') dir = 'E';
            }
        } else if(dir == 'S'){
            auto z = lower_bound(all(X[x]),y)-1;
            if(z == X[x].begin()-1){
                y = -1e9-1;
                done = 1;
            }else{
                y = *z;
                char c = m[{x,y}];
                if(c == '\\') dir = 'E';
                else if(c == '/') dir = 'W';
            }
        } else if(dir == 'E'){
            auto z = upper_bound(all(Y[y]),x);
            if(z == Y[y].end()){
                x = 1e9+1;
                done = 1;
            }else{
                x = *z;
                char c = m[{x,y}];
                if(c == '\\') dir = 'S';
                else if(c == '/') dir = 'N';
            }
        } else if(dir == 'W'){
            auto z = lower_bound(all(Y[y]),x)-1;
            if(z == Y[y].begin()-1){
                x = -1e9-1;
                done = 1;
            }else{
                x = *z;
                char c = m[{x,y}];
                if(c == '\\') dir = 'N';
                else if(c == '/') dir = 'S';
            }
        }

        p.pb({x,y});
        if(vis[{{x,y},dir}]) done = 1;
        else vis[{{x,y},dir}] = 1;
        if((x == 0 && y == 0) || (x == bx && y == by)) done = 1;
    }

    return p;
}

void fix(vector<pair<int,pii>> &m){
    sort(all(m));
    auto last = unique(all(m));
    m.erase(last, m.end());

}
void fix(vector<pair<pii,int>> &m){
    sort(all(m));
    auto last = unique(all(m));
    m.erase(last, m.end());
}

int calc(vector<pair<pii,int>> h, vector<pair<int,pii>> v){
    Tree<pii> T;
    set<pii> r;
    int cur = 0, res = 0;

    for(auto u:v){
        while(cur < sz(h) && h[cur].f.f + 1 <= u.f){
            T.insert({h[cur].s, h[cur].f.s});
            r.insert({h[cur].f.s, h[cur].s});
            ++cur;
        }
        while(!r.empty() && r.begin()->f <= u.f){
            T.erase({r.begin()->s,r.begin()->f});
            r.erase(r.begin());
        }
        res += T.order_of_key({u.s.s,-1e9})-T.order_of_key({u.s.f,1e9});

    }
    return res;
}
int main(){ sync;
    cin >> n >> bx >> by;
    X[0].pb(0); Y[0].pb(0);
    X[bx].pb(by); Y[by].pb(bx);

    for(int i=0;i<n;++i){
        int x,y; char c; cin >> x >> y >> c;
        m[{x,y}] = c;
        X[x].pb(y);
        Y[y].pb(x);
    }
    for(auto &u:X) sort(all(u.s));
    for(auto &u:Y) sort(all(u.s));

    vector<pii> op = path(0,0,'N');
    for(int i=0;i<sz(op)-1;++i){
        if(op[i].f == op[i+1].f) ov.pb({op[i].f,{min(op[i].s,op[i+1].s), max(op[i].s,op[i+1].s)}});
        else oh.pb({{min(op[i].f,op[i+1].f), max(op[i].f,op[i+1].f)},op[i].s});
    }
    vector<pii> bp[4];
    bp[0] = path(bx,by,'N'); bp[1] = path(bx,by,'E'); bp[2] = path(bx,by,'S'); bp[3] = path(bx,by,'W');
    for(int d=0;d<4;++d){
        for(int i=0;i<sz(bp[d])-1;++i){
            if(bp[d][i].f == bp[d][i+1].f) bv.pb({bp[d][i].f,{min(bp[d][i].s,bp[d][i+1].s), max(bp[d][i].s,bp[d][i+1].s)}});
            else bh.pb({{min(bp[d][i].f,bp[d][i+1].f), max(bp[d][i].f,bp[d][i+1].f)},bp[d][i].s});
        }
    }
    fix(oh); fix(ov); fix(bh); fix(bv);
    ans = calc(oh,bv) + calc(bh,ov);

    cout << ans << newl;
    return 0;
}
