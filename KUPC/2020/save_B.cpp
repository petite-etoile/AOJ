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


vector<string> grid;
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int H,W;
    cin >> H >> W;
    grid.resize(H);
    if(H%2==0 and W%2==0){
        cout << "No" << bn;
        return 0;
    }
    REP(i,H){
        cin >> grid[i];
    }
    //とりあえずH&1 and W&1を仮定して解く
    int H_half = (H+1)/2;
    int W_half = (W+1)/2;
    queue<pair<int,int>> q;
    q.push(mp(0,0));
    vector<vector<bool>> visited(H,vector<bool> (W,false));
    string pattern_col_1 = "156", pattern_col_1_rev = "126";
    string pattern_row_1 = "136", pattern_row_1_rev = "146";
    string pattern_col_6 = "621", pattern_col_6_rev = "651";
    string pattern_row_6 = "631", pattern_row_6_rev = "641";
    int h,w;
    while(not q.empty()){
        tie(h,w) = q.front(); q.pop();
        debug(mp(h,w))
        if(visited[h][w]) continue;
        visited[h][w] = true;
        //うえ
        if(h and not visited[h-2][w]){
            string s;
            s += grid[h-2][w];
            s += grid[h-1][w];
            s += grid[h][w];
            debug(s)
            string t;
            if(grid[h][w] == '1'){
                if((w/2)&1){ //反転
                    t = pattern_col_1;
                }else{
                    t = pattern_col_1_rev;
                }
                if(s==t){
                    q.push(mp(h-2,w));
                }
            }else{
                if((w/2)&1){ //反転
                    t = pattern_col_6;
                }else{
                    t = pattern_col_6_rev;
                }
                if(s==t){
                    q.push(mp(h-2,w));
                }
            }
        }
        //した
        if(h+2<H and not visited[h+2][w]){
            string s;
            s += grid[h][w];
            s += grid[h+1][w];
            s += grid[h+2][w];
            debug(s)
            string t;
            if(grid[h][w] == '1'){
                if((w/2)&1){ //反転
                    t = pattern_col_1_rev;
                }else{
                    t = pattern_col_1;
                }
                if(s==t){
                    q.push(mp(h+2,w));
                }
            }else{
                if((w/2)&1){ //反転
                    t = pattern_col_6_rev;
                }else{
                    t = pattern_col_6;
                }
                if(s==t){
                    q.push(mp(h+2,w));
                }
            }
        }
        //ひだり
        if(w and not visited[h][w-2]){
            string s;
            s += grid[h][w-2];
            s += grid[h][w-1];
            s += grid[h][w];
            debug(s)
            string t;
            if(grid[h][w] == '1'){
                if((h/2)&1){ //反転
                    t = pattern_row_1;
                }else{
                    t = pattern_row_1_rev;
                }
                if(s==t){
                    q.push(mp(h,w-2));
                }
            }else{
                if((h/2)&1){ //反転
                    t = pattern_row_6;
                }else{
                    t = pattern_row_6_rev;
                }
                if(s==t){
                    q.push(mp(h,w-2));
                }
            }
        }
        //みぎ
        if(w+2<W and not visited[h][w+2]){
            string s;
            s += grid[h][w];
            s += grid[h][w+1];
            s += grid[h][w+2];
            debug(s)
            string t;
            if(grid[h][w] == '1'){
                if((h/2)&1){ //反転
                    t = pattern_row_1_rev;
                }else{
                    t = pattern_row_1;
                }
                debug(t)
                if(s==t){
                    q.push(mp(h,w+2));
                }
            }else{
                if((h/2)&1){ //反転
                    t = pattern_row_6_rev;
                }else{
                    t = pattern_row_6;
                }
                if(s==t){
                    q.push(mp(h,w+2));
                }
            }
        }
    }
    debug(visited)
    
}