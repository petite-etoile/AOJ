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

/* 全方位木の練習 */
vector<vector<pair<int,int>>> edge;
vector<int> Dist; //iを根とする部分木でのiからのパス最長

int dfs(int v,int pre){
    int res = 0;
    int to,cost;
    for(auto e:edge[v]){
        tie(to,cost) = e;
        if(to==pre) continue;
        chmax(res, cost+dfs(to, v));
    }   
    Dist[v] = res;
    return res;
}

int ans = 0;

// dist_preはrerooting後のDist[pre]
void dfs_with_rerooting(int v, int pre, int dist_pre){
    int to,cost;

    vector<pair<int,int>> child_dist;
    for(auto e:edge[v]){
        tie(to,cost) = e;
        if(to==pre) child_dist.emplace_back(cost+dist_pre, to);
        else child_dist.emplace_back(cost+Dist[to], to);
    }

    sort(ALL(child_dist), greater<pair<int,int>>());
    child_dist.emplace_back(0,-1); //sizeが1のときにバグらないように
    chmax(ans, child_dist[0].first + child_dist[1].first);

    //再帰で根をくるくるしちゃう
    for(auto e:edge[v]){
        tie(to,cost) = e;
        if(to==pre) continue;
        if(child_dist[0].second == to) dfs_with_rerooting(to, v, child_dist[1].first);
        else dfs_with_rerooting(to, v, child_dist[0].first);
    }
}

template<typename T>
struct Rerooting{

    using F = function<T(T,T)>; 
    F vertex_operation_merge; //頂点作用
    F accumulation_merge; //累積

    T identity_vertex_operation; //頂点作用用の単位元
    T identity_accumulate; //左右から累積する用の単位元
    int N;
    vector<vector<int>> edge;
    vector<T> DP;
    vector<T> ans;

    Rerooting(){}
    Rerooting(vector<vector<int>>& edge, F f1, T identity_vertex_operation, F f2, T identity_accumulate)
        :N(edge.size()), edge(edge), vertex_operation_merge(f1), identity_vertex_operation(identity_vertex_operation), 
            accumulation_merge(f2), identity_accumulate(identity_accumulate){
            DP.assign(N,identity_vertex_operation);
            ans.assign(N,identity_vertex_operation);
    }

    T dfs(int v, int pre){
        T res = identity_vertex_operation;
        
        for(auto to:edge[v]){
            if(to==pre) continue;
            DP[v] = vertex_operation_merge(DP[v], dfs(to, v));
        }
        return DP[v];
    }

    T dfs_with_rerooting(int v, int pre, T pre_value){
        //答えを得る
        for(auto to:edge[v]){
            if(to==pre){ ans[v] = vertex_operation_merge(ans[v], pre_value); }
            else{ ans[v] = vertex_operation_merge(ans[v], DP[to]); }
        }

        //左右から累積Foo
        int to;
        vector<T> left(edge[v].size(), identity_accumulate), right(edge[v].size(), identity_accumulate);
        for(int i=0; i<edge[v].size(); i++){
            int j = edge[v].size() - i - 1;
            if(i){
                left[i] = left[i-1];
                right[j] = right[j+1];
            }

            to = edge[v][i];
            if(to==pre){ left[i]  = accumulation_merge(left[i] , pre_value); }
            else{ left[i]  = accumulation_merge(left[i] , DP[to]); }

            to = edge[v][j];
            if(to==pre){ right[j] = accumulation_merge(right[j], pre_value); }
            else{ right[j] = accumulation_merge(right[j], DP[to]); }
        }

        //根をくるくる
        for(int i=0;i<edge[v].size();i++){
            int to = edge[v][i];
            if(to==pre) continue;
            T value = identity_vertex_operation;
            if(i) value = vertex_operation_merge(value, left[i-1]);
            if(i!=edge[v].size()-1) value = vertex_operation_merge(value, right[i+1]);
            dfs_with_rerooting(to, v, value);
        }
    }

    void build(){
        dfs(0,-1);
        dfs_with_rerooting(0,-1,identity_vertex_operation);
    }

};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    edge.resize(N);
    Dist.assign(N,0);

    int a,b,c;
    REP(i,N-1){
        cin >> a >> b >> c;
        edge[a].emplace_back(b,c);
        edge[b].emplace_back(a,c);
    }

    // dfs(0,-1);
    // dfs_with_rerooting(0,-1,0);

    Rerooting R(edge, []()->{}, 単位元, []()->{}, 単位元);



    cout << ans << endl;
}