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

struct CH{
    size_t operator()(pll x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        x.f ^= FIXED_RANDOM;
        x.s ^= FIXED_RANDOM;
        return (x.f^x.s) ^ ((x.f^x.s) >> 16);
    }
};

const int MOD = 1e9 + 7;
const pll BASE = {4441, 7817};
unordered_map<pll,int,CH> m;

pll operator+(const pll& a, const pll& b) {
	return { (a.first + b.first) % MOD, (a.second + b.second) % MOD };
}
pll operator+(const pll& a, const ll& b) {
	return { (a.first + b) % MOD, (a.second + b) % MOD };
}
pll operator-(const pll& a, const pll& b) {
	return { (MOD + a.first - b.first) % MOD, (MOD + a.second - b.second) % MOD };
}
pll operator*(const pll& a, const pll& b) {
	return { (a.first * b.first) % MOD, (a.second * b.second) % MOD };
}
pll operator*(const pll& a, const ll& b) {
	return { (a.first * b) % MOD, (a.second * b) % MOD };
}

pll get_hash(string s) {
	pll h = {0, 0};
	for (int i = 0; i < s.size(); i++) {
		h = BASE * h + s[i];
	}
	return h;
}

set<int,greater<int>> st;

int main(){ sync;
    string t; cin >> t;
    int k = sz(t);
    int n; cin >> n;

    for(int i=0;i<n;++i){
        string x; cin >> x;
        auto hsh = get_hash(x);
        m[hsh] = 1;
        st.insert(sz(x));
    }
    char ans[k];
    vector<pll> pre(k+1), pp(k);
    pre[0] = {0,0}; pp[0] = {1,1};

    int cur = 0;
    for(int i=0;i<k;++i,++cur){
        ans[cur] = t[i];

        if(i) pp[i] = pp[i-1]*BASE;
        pre[cur+1] = pre[cur]*BASE + ans[cur];

        for(auto u:st){
            if(u <= cur+1){
                pll h = pre[cur+1] - pp[u]*pre[cur+1-u];
                if(m.count(h)){
                    cur -= u;
                    break;
                }
            }
        }
    }

    for(int i=0;i<cur;++i) cout << ans[i]; cout << newl;

    return 0;
}
