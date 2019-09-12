#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int,int> pii;

#define sync ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define ll long long
#define ld long double
#define sz(a) int((a).size())
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()
#define allr(c) (c).rbegin(),(c).rend()
#define newl '\n'

const int n = 8;
int mx = 0;
int ans[n][n];
int mov[n][n];
int xm[] = {1,2,2,1,-1,-2,-2,-1};
int ym[] = {2,1,-1,-2,-2,-1,1,2};
vector<pair<pii,int>> bad[8];
int x = 0,y = 0;
int lol = 0;

bool fit(int xx, int yy){
    return (0<=xx && xx<n && 0<=yy && yy<n);
}
bool badfit(int xx, int yy, int i){
    bool ok = 1;
    for(auto u:bad[i]){
        int x1 = xx+u.f.f, y1 = yy+u.f.s;
        if(fit(x1,y1) && mov[x1][y1] == u.s) ok = 0;
    }
    return ok;
}

bool cmp(int a, int b){
    int acnt = 0, bcnt = 0, x1, y1;
    x1 = x + xm[a]; y1 = y + ym[a];
    for(int i=0;i<8;++i){
        if(fit(x1+xm[i],y1+ym[i]) && !ans[x1+xm[i]][y1+ym[i]] && badfit(x1,y1,i)) ++acnt;
    }
    x1 = x + xm[b]; y1 = y + ym[b];
    for(int i=0;i<8;++i){
        if(fit(x1+xm[i],y1+ym[i]) && !ans[x1+xm[i]][y1+ym[i]] && badfit(x1,y1,i)) ++bcnt;
    }
    return acnt < bcnt;
}

void dfs(int cur){
    ans[x][y] = cur;

    mx = max(mx,cur);
    cout << lol++ << " " << cur << " " << mx << newl;

   if(cur == 10000000){
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                cout << ans[i][j];
                if(ans[i][j] < 10) cout << "  ";
                else cout << " ";
            }
            cout << newl;
        }
        exit(0);
    }


    vector<int> m;
    for(int i=0;i<8;++i){
        int x1 = x+xm[i], y1 = y+ym[i];
        if(fit(x1,y1) && !ans[x1][y1] && badfit(x,y,i)) m.pb(i);
    }
    sort(all(m),cmp);

    for(auto i:m){
        mov[x][y] = i;
        x += xm[i]; y += ym[i];
        dfs(cur+1);
        x -= xm[i]; y -= ym[i];
        mov[x][y] = -1;
    }

    ans[x][y] = 0;
}

int main(){ sync;
    bad[0] = {{{-1,0},1},{{-1,1},2},{{0,1},3},{{0,1},2},{{0,1},1},{{-1,2},2},{{0,2},3},{{0,2},2},{{0,3},3},{{1,1},5},{{1,0},6},{{1,-1},7},{{2,0},6},{{2,2},5},{{1,1},6},{{1,0},7},{{2,1},6},{{1,1},7}};
    bad[1] = {{{0,-1},0},{{1,-1},7},{{1,0},6},{{1,0},7},{{1,0},0},{{2,-1},7},{{2,0},6},{{2,0},7},{{3,0},6},{{1,1},4},{{0,1},3},{{-1,1},2},{{0,2},3},{{2,2},4},{{1,1},3},{{0,1},2},{{1,2},3},{{1,1},2}};;
    bad[2] = {{{0,1},3},{{1,1},4},{{1,0},5},{{1,0},4},{{1,0},3},{{2,1},4},{{2,0},5},{{2,0},4},{{3,0},5},{{1,-1},7},{{0,-1},0},{{-1,-1},1},{{0,-2},0},{{2,-2},7},{{1,-1},0},{{0,-1},1},{{1,-2},0},{{1,-1},1}};
    bad[3] = {{{-1,0},2},{{-1,-1},1},{{0,-1},0},{{0,-1},1},{{0,-1},2},{{-1,-2},1},{{0,-2},0},{{0,-2},1},{{0,-3},0},{{1,-1},6},{{1,0},5},{{1,1},4},{{2,0},5},{{2,-2},6},{{1,-1},5},{{1,0},4},{{2,-1},5},{{1,-1},4}};
    bad[4] = {{{1,0},5},{{1,-1},6},{{0,-1},7},{{0,-1},6},{{0,-1},5},{{1,-2},6},{{0,-2},7},{{0,-2},6},{{0,-3},7},{{-1,-1},1},{{-1,0},2},{{-1,1},3},{{-2,0},2},{{-2,-2},1},{{-1,-1},2},{{-1,0},3},{{-2,-1},2},{{-1,-1},3}};
    bad[5] = {{{0,1},4},{{-1,1},3},{{-1,0},2},{{-1,0},3},{{-1,0},4},{{-2,1},3},{{-2,0},2},{{-2,0},3},{{-3,0},2},{{-1,-1},0},{{0,-1},7},{{1,-1},6},{{0,-2},7},{{-2,-2},0},{{-1,-1},7},{{0,-1},6},{{-1,-2},7},{{-1,-1},6}};
    bad[6] = {{{0,-1},7},{{-1,-1},0},{{-1,0},1},{{-1,0},0},{{-1,0},7},{{-2,-1},0},{{-2,0},1},{{-2,0},0},{{-3,0},1},{{-1,1},3},{{0,1},4},{{1,1},5},{{0,2},4},{{-2,2},3},{{-1,1},4},{{0,1},5},{{-1,2},4},{{-1,1},5}};
    bad[7] = {{{1,0},6},{{1,1},5},{{0,1},4},{{0,1},5},{{0,1},6},{{1,2},5},{{0,2},4},{{0,2},5},{{0,3},4},{{-1,1},2},{{-1,0},1},{{-1,-1},0},{{-2,0},1},{{-2,2},2},{{-1,1},1},{{-1,0},0},{{-2,1},1},{{-1,1},0}};

    for(int i=0;i<n;++i) for(int j=0;j<n;++j) mov[i][j] = -1;
    dfs(1);

    return 0;
}
