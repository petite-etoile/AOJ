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

struct WeightedUnionFind{
    vector<int> parent,rank;
    vector<int64> weight;
    WeightedUnionFind(size_t N){
        parent.resize(N);
        REP(i,N) parent[i]=i;
        rank.assign(N,0);
        weight.assign(N,0);
    }

    int get_root(int v){
        if(parent[v]==v) return v;
        int par = get_root(parent[v]);
        weight[v] += weight[parent[v]];
        parent[v] = par;
        return par;
    }

    void unite(int x,int y,int64 w){
        int root_x = get_root(x), root_y = get_root(y);
        if(root_x == root_y) return;
        //xの木の高さ < yの木の高さ
        if(rank[root_x] < rank[root_y]){
            parent[root_x] = root_y;
            weight[root_x] = w - weight[x] + weight[y];
        }else{
            parent[root_y] = root_x;
            weight[root_y] = -w - weight[y] + weight[x];
            //木の高さが同じなら片方
            if(rank[root_x] == rank[root_y]) rank[root_x]++;
        }
    }

    bool same(int x,int y){
        return get_root(x) == get_root(y);
    }

    // xからyへのコスト
    int64 diff(int x,int y){
        return weight[x] - weight[y];
    }
};

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int N,Q;
    cin >> N >> Q;

    WeightedUnionFind UF(N);
    int a,x,y,w;
    REP(i,Q){
        cin >> a;
        if(a){
            cin >> x >> y;
            if(UF.same(x,y)) cout << UF.diff(x,y) << bn;
            else cout << "?" << bn;
        }else{
            cin >> x >> y >> w;
            if(not UF.same(x,y)) UF.unite(x,y,w);
        }
    }
}