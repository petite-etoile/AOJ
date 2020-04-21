int N;
vector<vector<int>> edge;
vector<T> DP;
vector<T> ans;
T dfs(int v, int pre){
    T DP[v] = 1;

    for(auto to:edge[v]){
        if(to==pre) continue;
        DP[v] *= dfs(to,v);
    }
    for(auto to:edge[v]){
        if(to==pre) continue;
        DP[v] *= hoge;
    }
    return DP[v];
}
void dfs_with_rerooting(int v, int pre, T pre_val){
    //答えを得る
    for(auto to:edge[v]){
        if(to==pre){
            ans[v] *= hoge;
        }else{
            ans[v] *= hoge;
        }
    }
    //左右から累積和
    int to;
    vector<T> left(edge[v].size(),init_val), right(edge[v].size(),init_val); 
    for(int i=0; i<edge[v].size(); i++){
        int j = edge[v].size() - i - 1;
        if(i) {
            left[i]  = left[i-1];
            right[j] = right[j+1];
        }
        to = edge[v][i];
        if(to == pre) {
            left[i] *= hoge;
        }else{
            left[i] += hoge;
        }
        to = edge[v][j];
        if(to == pre){
            right[j] += hoge;
        }else{
            right[j] *= hoge;
        }
    }
    
    //根をくるくるする
    for(int i=0; i<edge[v].size(); i++){
        int to = edge[v][i];
        if(to!=pre){
            T val = init_val;
            if(i){
                val *= hoge;
            }
            if(i!=edge[v].size()-1){
                val *= hoge;
            }
            dfs_with_rerooting(to, v, val);
        }
    }
}