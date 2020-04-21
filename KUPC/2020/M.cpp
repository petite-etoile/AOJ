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
        os << "\n";
    }
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

#define deb cout << "debug"<<endl;

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    while(n--){
        string s(n,'1');
        string del="";
        int c=0;
        vector<string> ans;
        while(s.size()){
            ans.emplace_back(del+s);
            // cout << del+s << endl;
            if(s=="10" && del.size()!=0) ans.emplace_back(del+"0");
            if(s[0]=='0'){
                del+="0";
                s=s.substr(1);
                if(s.size()==0) break;
            }else if(s[1]=='0'){
                del+="0";
                s=s.substr(1);
                if(s.size()==0) {
                    // cout << del <<endl;
                    break;
                }
                s[0]='1';
            }
            if(s.find('0')==string::npos){
                s=s.substr(1);
                if(s.size()==0) break;
                s[s.size()-1]= '0';
                
            }else{
                s=s.substr(1);
                if(s.size()==0) break;
                int zero= s.find('0');
                s[zero]='1';
                s[zero-1]='0';
            }
        }
        cout << ans.size() << bn;
        cout << ans;
        cout << "----------" << bn;
    }
}