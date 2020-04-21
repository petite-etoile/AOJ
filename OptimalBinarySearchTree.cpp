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
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
using P = pair<ll, ll>;
const int MOD = (int)1e9 + 7;
const ll INF = 1LL << 60;
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
ld solve(vector<ld>& P, int N){
    /*
        区間[s,t]をiで分割する
        　　　i
        　子    子
        ・・・　・・・
        にする(今回はダミーは関節点に来ないことに注意)
    
        すると、dp[s][t] = min(dp[s][i-1] + dp[i+1][t]) + (s~tのコストの和)で表せる  (s<i<t かつ　実際の(ダミーでない)ノード)
    */
   vector<vector<ld>> dp(N,vector<ld>(N,1<<30)); 
    for(int i=0;i<N;i++) dp[i][i] = P[i]; 
    
    vector<ld> cumsum(N+1,0);
    REP(i,N) {cumsum[i+1]=cumsum[i]+P[i];}  //累積和(s~tのコストの和をO(1)で使うために)
    for(int i=2 ;i<N;i+=2){ 
        for(int left=1;left < N-i;left+=2){ // ダミー,...,ダミーを単位としてやる
            int right = left + i; //区間右端(閉)
            for(int mid = left+1; mid<right; mid+=2){ //ダミーは関節点に来ない
                chmin(dp[left][right], dp[left][mid-1] + dp[mid+1][right]); //上記の分割
            }
            dp[left][right] += cumsum[right+1]-cumsum[left];
        }
    }
    ld res = dp[1][N-1]; //1-indexに注意
    return res;
}
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    int L = 2*(N+1);  
    vector<ld> P(L,0);//1-index   DVDVDVDVDVDVDVDVD (D:ダミー,V:実際の)
    REP(i,N) cin >> P[2*(i+1)];
    REP(i,N+1) cin >> P[2*i+1];

    ld ans=solve(P,L);
    cout << fixed<<setprecision(10)<<ans<<endl;
}