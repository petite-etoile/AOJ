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
ostream& operator<<(ostream& os, vector<T> &V){
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



int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int64 N;
    cin >> N;

    vector<vector<int>> edge(N);
    int64 edge_cnt = N*N;
    char c;
    REP(i,N){
        REP(j,N){
            cin >> c;
            if(c=='Y') edge[i].emplace_back(j);
            else edge_cnt--;
        }
    }
    edge_cnt>>=1;

    if(N&1){
        int64 tmp = N*(N-1)/2 - edge_cnt;
        if(tmp&1) cout << "Taro" << bn;
        else cout << "Hanako" << bn;
        return 0;
    }

    int ODD=0,EVEN=0;
    bitset<1000> visited;
    REP(i,N){
        if(visited[i]) continue;
        else{
            queue<int> q;
            q.push(i);
            int connect_size = 0;
            while(not q.empty()){
                int v = q.front(); q.pop();
                if(visited[v]) continue;
                visited[v]=1;
                connect_size++;
                for(auto u:edge[v]){
                    if(visited[u]) continue;
                    q.push(u);
                }
            }
            if(connect_size&1) ODD++;
            else EVEN++;
        }
    }

    bool taro_want_even = (N*(N-1)/2 - edge_cnt) & 1; //taroは偶・遇にしたい
    vector<vector<int>> memo(EVEN+ODD+1,vector<int>(EVEN+ODD+1,-1));

    auto f = [&](auto solve, int even, int odd) -> bool{
        //trueなら奇・奇になる
        if(even+odd==2){
            if(even) return false;
            else return true;
        }
        if(memo[even][odd]!=-1) return memo[even][odd];

        //turnがtrueなら
        bool taro_turn = ((ODD+EVEN) - (even + odd)) & 1;
        
        if(taro_turn ^ taro_want_even){ //偶数にしたい
            bool can_be_even = false;
            if(even>=2){
                can_be_even |= not solve(even-1, odd);
            }
            if(even && odd){
                can_be_even |= not solve(even-1, odd);
            }
            if(odd>=2){
                can_be_even |= not solve(even+1, odd-2);
            }
            memo[even][odd] = not can_be_even;
            return not can_be_even;
        }else{ //奇数にしたい
            bool can_be_odd = false;
            if(even>=2){
                can_be_odd |= solve(even-1, odd);
            }
            if(even && odd){
                can_be_odd |= solve(even-1, odd);
            }
            if(odd>=2){
                can_be_odd |= solve(even+1, odd-2);
            }
            memo[even][odd] = can_be_odd;
            return can_be_odd;
        }
    };
    bool will_be_odd = f(solve,EVEN,ODD);
    if(((N*(N-1)/2 - edge_cnt) + will_be_odd)&1) cout << "Taro" << bn;
    else cout << "Hanako" << bn;

}