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
os << "\n";
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
/*struct DLL{
    struct node{
        int key;
        node* prev;
        node* next;
    }
    node* top_node;
    public:
        DLL(): top(new node){
            top->x = 0;
            top->prev = top_node;
            top->next = top_node;
        }
        ~DLL(){

        }
        void insert(int x){

        }
    };
}*/
//fixed<<setprecision(10)<<ans<<endl;
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    deque<int> q;
    string s;
    int x;
    REP(i,N){
        cin >> s;
        if(s=="insert"){
            cin >> x;
            q.push_front(x);
        }else if(s=="delete"){
            cin >> x;
            auto it= q.begin();
            while( it!=q.end()){
                if(*it == x){
                    q.erase(it);
                    break;}
                it++;

            }
        }
        else if(s=="deleteFirst"){
            q.pop_front();
        }else{
            q.pop_back();
            
        }

    }
    for(auto it=q.begin();it<q.end();it++){
        if(it!=q.begin()) cout << " ";
        cout << *it;
    }
    cout << endl;
}