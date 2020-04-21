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
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
using P = pair<ll, ll>;
typedef vector<int> vi;
const int MOD = (int)1e9 + 7;
const ll INF = 1LL << 62;
const int inf = 1<<30;
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i,s,n) for (int i = s; i < (n); i++)
#define ALL(obj) (obj).begin(), (obj).end() //コンテナじゃないと使えない!!
#define debug(x) cerr << #x << ": " << x << "\n";
#define mp make_pair
template <typename T>
ostream& operator<<(ostream& os, vector<T> &V){
    int N = V.size();
    REP(i,N){
        os << V[i];
        if (i!=N-1) os << " ";
    }
    os << "\n";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, pair<T,T> const&P){
    os << P.first;
    os << " ";
    os << P.second;
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
//fixed<<setprecision(10)<<ans<<endl;
ll big_weight_knapsack(vector<ll>& val,vector<ll>& weight, ll W){
    ll N = val.size();
    ll MAX=10001;
    // vector<vector<ll>> dp(N+1,vector<ll>(10001,INF));//価値vを達成するのに最小重さ
    vector<ll> dp(MAX+1,INF);//価値vを達成するのに最小重さ

    dp[0] = 0;
    REP(i,N){
        for(ll v=MAX;v>=0;v--){
            if (v>val[i])
                chmin(dp[v],dp[v-val[i]]+weight[i]);
            else
                chmin(dp[v],weight[i]);
        }
    }

    ll res=0;
    REP(i,MAX){
        if(dp[i]<=W)
            res=i;
        else break;
    }
    return res;
}
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N,M;
    cin >> N >> M;
    vector<ll> val(N),weight(N);
    REP(i,N){cin >> val[i] >> weight[i];}
    ll ans=big_weight_knapsack(val,weight,M);
    
    cout << ans << endl;
}