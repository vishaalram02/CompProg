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
#define sz(a) int((a).size())
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()
#define allr(c) (c).rbegin(),(c).rend()
#define newl '\n'

int main(){ sync;
    ifstream cin("cowjog.in");
    ofstream cout("cowjog.out");

    ll n,t; cin >> n >> t;
    vector<ll> A(n);
    for(int i=0;i<n;++i){
        ll x,y; cin >> x >> y;
        A[i] = -(x+y*t);
    }

    vector<ll> ans;
    for (auto x:A) {
        auto it = upper_bound(all(ans), x);
        if(it == ans.end()) ans.pb(x);
        else *it = x;
    }

    cout << sz(ans) << newl;
    return 0;
}
