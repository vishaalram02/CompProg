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

ll dp[(1<<20)], ans = -1;
ll s[20], w[20], h[20];

ll calc(int v){
    if(dp[v] != 0) return dp[v];

    dp[v] = -1;
    for(int i=0;i<20;++i){
        if((1<<i)&v){
            ll k = calc(v^(1<<i));
            if(k != -1 && w[i] <= k) dp[v] = max(dp[v],min(k-w[i],s[i]));
        }
    }

    return dp[v];
}

int main(){ sync;
    int n,x; cin >> n >> x;
    for(int i=0;i<n;++i) cin >> h[i] >> w[i] >> s[i];

    dp[0] = 1e18;
    calc((1<<n)-1);

    for(int i=0;i<(1<<n);++i){
        int cur = 0;
        for(int j=0;j<n;++j){
            if((1<<j)&i) cur += h[j];
        }
        if(cur >= x) ans = max(ans,dp[i]);
    }

    if(ans == -1) cout << "Mark is too tall" << newl;
    else cout << ans << newl;

    return 0;
}
