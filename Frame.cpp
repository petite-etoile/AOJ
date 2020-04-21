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

struct cumsum2D{
    int H,W;
    vector<vector<int64>> cumsum;
    cumsum2D(vector<vector<int64>> A) :H(A.size()), W(A[0].size()){
        cumsum.assign(H+1, vector<int64>(W+1,0));
        for(int h=0;h<H;h++){
            for(int w=0;w<W;w++){
                cumsum[h+1][w+1] = A[h][w];
            }
        }

        for(int h=0;h<H;h++){
            for(int w=0;w<W;w++){
                cumsum[h+1][w+1] += cumsum[h+1][w] + cumsum[h][w+1] - cumsum[h][w];
            }
        }
    }

    // return sum(A[h][w]) {h,w | h in [h_begin, h_end) and w in [w_begin, w_end)}
    int64 get(int h_begin, int h_end, int w_begin, int w_end){
        return cumsum[h_end][w_end] - cumsum[h_begin][w_end] - cumsum[h_end][w_begin] + cumsum[h_begin][w_begin];
    }
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<vector<int64>> P(N,vector<int64>(N));
    REP(i,N){
        REP(j,N) cin >> P[i][j];
    }

    int64 ans = -INF;
    cumsum2D cumsum(P);
    REP(w,N){
        REP(u,N){
            for(int d=u+1; d<=N;d++){
                chmax(ans, cumsum.get(u,d,w,w+1));
                int h=w,l=u,r=d;
                chmax(ans, cumsum.get(h,h+1,l,r));
            }
        }
    }
    REP(u,N){
        for(int d=u+1; d<N; d++){
            int64 S = cumsum.get(u,u+1,0,N) + cumsum.get(d,d+1,0,N);
            vector<int64> DP_L(N,-INF), DP_R(N,-INF);
            REP(l,N){
                if(l) DP_L[l] = DP_L[l-1];
                int64 val = - (cumsum.get(u,u+1,0,l) + cumsum.get(d,d+1,0,l)) + (cumsum.get(u+1,d,l,l+1) ) ;
                chmax(DP_L[l], val);

                int r = N-l-1;
                if(l) DP_R[r] = DP_R[r+1];
                val =  - (cumsum.get(u,u+1,r+1,N) + cumsum.get(d,d+1,r+1,N)) + (cumsum.get(u+1,d,r,r+1) ) ;
                chmax(DP_R[r], val);
            }
            REP(i,N-1) chmax(ans, S + DP_L[i] + DP_R[i+1]);
        }
    }

    cout << ans << endl;
}