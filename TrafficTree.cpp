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

int N;
vector<vector<int>> edge;
vector<int> DP;
vector<int> ans;
int dfs(int v, int pre){
    DP[v] = 0;
    for(auto to:edge[v]){
        if(to==pre) continue;
        chmax(DP[v], dfs(to,v) + 1);
    }
    return DP[v];
}
const int init_val = 0;
void dfs_with_rerooting(int v, int pre, int pre_val){
    //答えを得る
    for(auto to:edge[v]){
        if(to==pre){
            chmax(ans[v], pre_val + 1);
        }else{
            chmax(ans[v], DP[to] + 1);
        }
    }
    //左右から累積和
    int to;
    vector<int> left(edge[v].size(),init_val), right(edge[v].size(),init_val); 
    for(int i=0; i<edge[v].size(); i++){
        int j = edge[v].size() - i - 1;
        if(i) {
            left[i]  = left[i-1];
            right[j] = right[j+1];
        }
        to = edge[v][i];
        if(to == pre) {
            chmax(left[i], pre_val+1);
        }else{
            chmax(left[i], DP[to]+1);
        }
        to = edge[v][j];
        if(to == pre) {
            chmax(right[j], pre_val+1);
        }else{
            chmax(right[j], DP[to]+1);
        }
    }
    
    //根をくるくるする
    for(int i=0; i<edge[v].size(); i++){
        int to = edge[v][i];
        if(to!=pre){
            int val = init_val;
            if(i){
                chmax(val, left[i-1]);
            }
            if(i!=edge[v].size()-1){
                chmax(val, right[i+1]);
            }
            dfs_with_rerooting(to, v, val);
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> N;
    DP.assign(N,0);
    ans.assign(N,0);
    edge.assign(N,vector<int>());
    REP(i,N-1){
        int a,b;
        cin >> a >> b;

        edge[--a].emplace_back(--b);
        edge[b].emplace_back(a);
    }

    //一番遠い点へのパスに含まれる点は1度だけ通る
    //他の辺は2度通る
    

    dfs(0,-1);
    dfs_with_rerooting(0,-1,0);
    for(auto a:ans){
        cout << 2*(N-1)-a << bn;        
    }
}