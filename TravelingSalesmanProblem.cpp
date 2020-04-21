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
const int MOD = (int)1e9 + 7;
const ll INF = 1LL << 60;
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
ostream& operator<<(ostream& os, pair<T,T> &P){
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
bool is_one(int bit){
    while(bit%2==0){
        bit>>=1;
    }
    return bit==1;
}
//fixed<<setprecision(10)<<ans<<endl;
ll TravelingSalesmanProblem(vector<vector<P>> &edge, int N, int start=0){
    ll max_bit = 1<<N; //MAX_BIT
    vector<vector<ll>> dp(max_bit,vector<ll>(N,INF)); //dp[bit][i]:=bitのすべてをまわり、iにいるときの最短路
    dp[1][0] = 0; //始点は0

    //配るDP
    ll from,to,dist;
    for(ll bit_mask=1;bit_mask<max_bit;bit_mask++){
        REP(from,N){
            if(dp[bit_mask][from]>=INF) continue; //未実現の状態
            for(auto e: edge[from]){
                tie(to,dist) = e; //行き先、距離
                if( (1<<to) & bit_mask ) continue; //2回通ってはいけない
                ll next_bit = 1<<to | bit_mask;
                chmin(dp[next_bit][to], dp[bit_mask][from]+dist);
            }
        }
    }

    ll ans = INF;
    REP(from,N){
        for(auto e:edge[from]){
            tie(to,dist) = e;
            if(to==start)
                chmin(ans,dp[max_bit-1][from]+dist);    
        }
    }

    return ans;
}
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll N,M;
    cin >> N >> M;
    
    //辺入力
    vector<vector<pair<ll,ll>>> edge(N);
    vector<P> edge_to_zero;
    REP(i,M){
        ll a,b,c;
        cin  >> a >> b >> c;
        edge[a].push_back(mp(b,c));
        if(b==0) edge_to_zero.push_back(mp(a,c));
    }

    ll ans = TravelingSalesmanProblem(edge,N);
    if(ans>=INF) cout << -1 << endl;
    else cout << ans << endl;
}