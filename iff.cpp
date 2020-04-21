/*
　　　∫ ∫ ∫
　　　ノヽ
　　（＿　 ）
　（＿　　　 ）
（＿＿＿＿＿＿ ）
　ヽ(´･ω･)ﾉ　
　　 |　 /
　　 UU
*/
#pragma region macro
#include <bits/stdc++.h>
typedef long long int64;
using namespace std;
using P = pair<int64, int64>;
typedef vector<int> vi;
const int MOD = (int)1e9 + 7;
const int64 INF = 1LL << 62;
const int inf = 1<<30;
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i,s,n) for (int i = s; i < (n); i++)
#define ALL(obj) (obj).begin(), (obj).end() //コンテナじゃないと使えない!!
#define debug(x) cerr << #x << ": " << x << "\n";
#define mp make_pair
#define bn '\n'
template <typename T>
ostream& operator<<(ostream& os, const vector<T> &V){
    int N = V.size();
    REP(i,N){
        os << V[i];
        if (i!=N-1) os << " ";
    }
    os << "\n";
    return os;
}
template <typename T,typename S>
ostream& operator<<(ostream& os, pair<T,S> const&P){
    os << "(";
    os << P.first;
    os << " , ";
    os << P.second;
    os << ")";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, set<T> &S){
    auto it=S.begin();
    while(it!=S.end()){
        os << *it;
        os << " ";
        it++;
    }
    os << "\n";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, deque<T> &q){
    for(auto it=q.begin();it<q.end();it++){
        os<<*it;
        os<<" ";
    }
     os<<endl;
    return os;
}
vector<pair<int,int>> dxdy = {mp(0,1),mp(1,0),mp(-1,0),mp(0,-1)};
#pragma endregion
//fixed<<setprecision(10)<<ans<<endl;

struct StronglyConnectedComponents{
    vector<int> topological_idx; //属する強連結成分のトポロジカル順序
    vector<bool> visited;
    vector<vector<int>> edge, edge_rev;
    vector<int> post_order;
    int N;
    int scc_size = 0; //強連結成分の数


    //O(N+M)
    StronglyConnectedComponents(vector<vector<int>>& edge):edge(edge){
        N = edge.size();
        edge_rev.resize(N);
        for(int v=0;v<N;v++){
            for(auto to:edge[v]){
                edge_rev[to].emplace_back(v);
            }
        }
        visited.assign(N,false);
        topological_idx.resize(N);
        for(int i=0;i<N;i++){
            if(not visited[i]) dfs(i);
        }
        visited.assign(N,false);
        reverse(post_order.begin(), post_order.end());
        for(auto v:post_order){
            if(not visited[v]) dfs_rev(v,scc_size++);
        }
    }

    void dfs(int v){
        visited[v] = true;
        for(auto to:edge[v]){
            if(not visited[to]) dfs(to);
        }
        post_order.emplace_back(v);
    }

    void dfs_rev(int v, int idx){
        visited[v] = true;
        topological_idx[v] = idx;
        for(auto to:edge_rev[v]){
            if(not visited[to]) dfs_rev(to, idx);
        }
    }

    //vが属している強連結成分のトポロジカル順序
    int get_topological_idx(int v){
        return topological_idx[v];
    }

    //強連結成分の数
    int get_scc_size(){
        return scc_size;
    }

    vector<vector<int>> build_graph(){
        vector<vector<int>> new_edge(N);
        for(int i=0;i<N;i++){
            int topo = topological_idx[i];
            for(auto to:edge[i]){
                new_edge[topo].emplace_back(topological_idx[to]);
            }
        }
        for(int i=0;i<scc_size;i++){
            sort(new_edge[i].begin(), new_edge[i].end());
            new_edge[i].erase(unique(new_edge[i].begin(), new_edge[i].end()), new_edge[i].end());
        }
        return new_edge;
    }

};


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N , M;
    cin >> N >> M;

    vector<vector<int>> edge(N);
    REP(i,M){
        int a,b;
        cin >> a >> b;
        edge[--a].emplace_back(--b);
    }

    StronglyConnectedComponents SCC(edge);
    vector<vector<int>> components(SCC.get_scc_size());
    REP(i,N){
        components[SCC.get_topological_idx(i)].emplace_back(i);;
    }
    vector<vector<int>> ans(N);
    REP(i,N){
        for(auto a:components[SCC.get_topological_idx(i)]){
            ans[i].emplace_back(a+1);
        }
        cout << ans[i];
    }
}