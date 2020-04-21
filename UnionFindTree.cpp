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

struct UnionFind{
    int N;
    vector<int> node;
    UnionFind(){}
    UnionFind(int N):N(N){
        node.assign(N,-1);
    }
    int get_root(int x){
        if (node[x]<0){
            return x;
        }
        node[x] = get_root(node[x]);
        return node[x];
    }
    void unite(int x,int y){
        int root_x = get_root(x);
        int root_y = get_root(y);
        int larger,smaller;
        if(root_x != root_y){
            if(node[root_x] < node[root_y]){ //size of x is lager than one of y
                larger  = root_x;
                smaller = root_y;
            }else{
                larger  = root_y;
                smaller = root_x;
            }
            node[larger] += node[smaller];
            node[smaller] = larger;
        }
    }
    int size(int x){
        return -node[x];
    }
    bool same(int x,int y){
        return get_root(x) == get_root(y);
    }
};

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int N,Q;
    cin >> N >> Q;
    UnionFind UF(N);
    REP(i,Q){
        int c,x,y; cin >> c >> x >> y;
        if(c){
            cout << UF.same(x,y) << bn;
        }else{
            UF.unite(x,y);
        }
    }

}