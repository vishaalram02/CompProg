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

vector<int> adj[172787];
vector<string> v;
int n;

bool bfs(int b,int e,int pred[]){
    queue<int> q;
    bool vis[n];

    for(int i=0;i<n;++i){
        vis[i]=0;
        pred[i]=-1;
    }

    vis[b]=1;
    q.push(b);

    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<adj[u].size();++i){
            if(vis[adj[u][i]]==0){
                vis[adj[u][i]]=1;
                pred[adj[u][i]]=u;
                q.push(adj[u][i]);

                if(adj[u][i]==e) return 1;
            }
        }
    }
    return 0;
}

void print(int b,int e){
    int pred[n];

    if(bfs(b,e,pred)==1){
        vector<int> path;
        int p=e;
        path.pb(p);
        while(pred[p] != -1){
            p=pred[p];
            path.pb(p);
        }

        for(int i=path.size()-1;i>=0;--i) cout << v[path[i]] << newl;
    }else{
        cout << "not connected" << newl;
    }
}
int main(){ sync;
    ifstream fin;
    fin.open("words.txt");

    string t;
    while(fin >> t) v.pb(t);

    n=v.size();
    for(int i=0;i<n;++i){
        int k=v[i].size();
        vector<string> p;
        //insert
        for(int j=0;j<=k;++j){
            for(char c='a';c<='z';++c){
                p.pb(v[i].substr(0,j)+c+v[i].substr(j));
            }
        }
        //replace
        for(int j=0;j<k;++j){
            for(char c='a';c<='z';++c){
                p.pb(v[i].substr(0,j)+c+v[i].substr(j+1));
            }
        }
        //delete
        for(int j=0;j<k;++j){
            p.pb(v[i].substr(0,j)+v[i].substr(j+1));
        }


        for(int j=0;j<p.size();++j){
            vector<string>::iterator it=lower_bound(all(v),p[j]);
            if(p[j] != v[i] && (*it)==p[j]) adj[i].pb(it-v.begin());

        }
    }
    cout << "done" << newl;
    string t1,t2;
    for(int i=0;i<100;++i){
        cin >> t1 >> t2;
        int b=lower_bound(all(v),t1)-v.begin(),e=lower_bound(all(v),t2)-v.begin();
        print(b,e);
    }
    return 0;
}
