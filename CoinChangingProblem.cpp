//17D8101002F OnoTakaki petite_prog C++14 
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const int MOD = (int)1e9 + 7;
const int INF = 1LL << 60;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ALL(obj) (obj).begin(), (obj).end() //コンテナじゃないと使えない!!
#define debug(x) cerr << #x << ": " << x << "\n";
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
//fixed<<setprecision(10)<<ans<<endl;
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N,M;
    cin >> N >> M;
    vector<int> C(M);
    REP(i,M){
        cin >> C[i];
    }
    vector<int> dp(N+1);
    REP(i,N+1){
        dp[i] = i;
    }
    REP(i,M){
        int c = C[i];
        REP(j,N){
            if (j+c>N)break;
            dp[j+c]=min(1+dp[j],dp[j+c]);
        }        
    }
    cout << dp[N]<<endl;

}

