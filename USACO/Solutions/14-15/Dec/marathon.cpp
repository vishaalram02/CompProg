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

int d(pii a, pii b){return abs(a.f-b.f)+abs(a.s-b.s); }

struct Tree1 {
    Tree1 *pl, *pr;
    int nl = 0, nr = 0, val = 0;

    void updateVal() { val = pl->val + pr->val; }

    Tree1(int l, int r, int A[]) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        pl = new Tree1(nl, nl + nr >> 1, A);
        pr = new Tree1(nl + nr >> 1, nr, A);
        updateVal();
    }
    void modify(int p, int x) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            val = x;
            return;
        }
        pl->modify(p, x);
        pr->modify(p, x);
        updateVal();
    }
    int query(int l, int r) {
        if (l <= nl && r >= nr)
            return val;
        if (l >= nr || nl >= r)
            return 0;
        return pl->query(l, r) + pr->query(l, r);
    }
};

struct Tree2 {
    Tree2 *pl, *pr;
    int nl = 0, nr = 0, val = 0;

    void updateVal() { val = max(pl->val,pr->val); }

    Tree2(int l, int r, int A[]) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        pl = new Tree2(nl, nl + nr >> 1, A);
        pr = new Tree2(nl + nr >> 1, nr, A);
        updateVal();
    }
    void modify(int p, int x) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            val = x;
            return;
        }
        pl->modify(p, x);
        pr->modify(p, x);
        updateVal();
    }
    int query(int l, int r) {
        if (l <= nl && r >= nr)
            return val;
        if (l >= nr || nl >= r)
            return 0;
        return max(pl->query(l, r),pr->query(l, r));
    }
};

int main(){ sync;
    int n,q; cin >> n >> q;

    vector<pii> a(n);

    for(int i=0;i<n;++i) cin >> a[i].f >> a[i].s;

    int dist[n], skip[n];

    for(int i=0;i<n-1;++i) dist[i] = d(a[i],a[i+1]);
    for(int i=1;i<n-1;++i) skip[i] = dist[i-1]+dist[i]-d(a[i-1],a[i+1]);

    Tree1 *D = new Tree1(0,n,dist);
    Tree2 *S = new Tree2(0,n,skip);

    for(int i=0;i<q;++i){
        char c; cin >> c;
        if(c == 'Q'){
            int l,r; cin >> l >> r;
            cout << D->query(l-1,r-1)-S->query(l,r-1) << newl;
        }else if(c == 'U'){
            int p,x,y; cin >> p >> x >> y; --p;
            a[p] = {x,y};

            if(p <= n-2) dist[p] = d(a[p],a[p+1]);
            if(p >= 1) dist[p-1] = d(a[p-1],a[p]);
            if(p >= 1) D->modify(p-1,dist[p-1]);
            if(p <= n-2) D->modify(p,dist[p]);
            if(p >= 2) S->modify(p-1,dist[p-2]+dist[p-1]-d(a[p-2],a[p]));
            if(p >= 1 && p <= n-2) S->modify(p,dist[p-1]+dist[p]-d(a[p-1],a[p+1]));
            if(p <= n-3) S->modify(p+1,dist[p]+dist[p+1]-d(a[p],a[p+2]));
        }
    }
    return 0;
}
