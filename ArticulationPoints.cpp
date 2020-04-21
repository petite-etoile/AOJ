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
        os << "\n";
    }
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
template <typename T,typename S>
ostream& operator<<(ostream& os, map<T,S> const&M){
    for(auto e:M){
        os<<e;
    }
    os<<endl;
    return os;
}
vector<pair<int,int>> dxdy = {mp(0,1),mp(1,0),mp(-1,0),mp(0,-1)};
#pragma endregion
//fixed<<setprecision(10)<<ans<<endl;

struct LowLink{
    vector<bool> visited;
    vector<vector<int>> edge;
    vector<int> pre_order,low; //low[v]:=min{pre_order[u]|u==v or uがvの子孫(vを含む)に補木辺を持つ}
    int N;
    vector<int> articulation_points; //関節点:=2つ以上の2連結成分に含まれる点(=グラフから削除すると連結成分が一つ増えるような点)
    vector<pair<int,int>> bridge; //橋:=グラフから削除すると連結成分が一つ増えるような辺
    //O(N+M)
    LowLink(vector<vector<int>>& edge):edge(edge){
        N = edge.size();
        visited.assign(N,false);
        int order = 0; 
        pre_order.assign(N,0); low.assign(N,0);
        for(int v=0;v<N;v++) dfs(v,-1,v,order);
    }

    void dfs(int v,int pre,int root,int& order){
        if(visited[v]) return;
        visited[v] = true;
        
        pre_order[v] = order++; 
        low[v] = pre_order[v];
        int child_cnt = 0; 
        bool Art_flag = false;
        for(auto to:edge[v]){
            if(to==pre) continue;
            if(visited[to])  low[v] = min(low[v], pre_order[to]);
            else {
                dfs(to,v,root,order);
                low[v] = min(low[v], low[to]);
                child_cnt++;
                if(pre_order[v]<=low[to]) Art_flag=true;
                if(pre_order[v] < low[to]) bridge.emplace_back(min(v,to), max(v,to));
            }
        }
        if(v==root and child_cnt>=2) articulation_points.emplace_back(v);
        if(v!=root and Art_flag) articulation_points.emplace_back(v);
    }

    //関節点を返す
    vector<int> get_art_points(){
        /*点vが関節点 <=>DFS木において
            ・vが根なら子の数が複数
            ・そうでなければ、vの子孫と先祖を結ぶ補木辺が存在しない*/
        return articulation_points;
    }

    //橋を返す
    vector<pair<int,int>> get_bridge(){
        return bridge;
    }
};

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int N,M;
    cin >> N >> M;
    vector<vector<int>> edge(N);
    REP(i,M){
        int a,b; cin >> a >> b;
        edge[a].emplace_back(b);
        edge[b].emplace_back(a);
    }

    LowLink LL(edge);
    auto ans = LL.get_art_points();
    sort(ALL(ans));
    cout << ans;
}