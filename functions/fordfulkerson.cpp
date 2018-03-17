#define MAX 10000
//持ってたライブラリがバグ起こしてたので某所からコピペしてきました 申し訳なさある
struct edge { int to, cap, rev; };
vector<edge> G[MAX];
bool used[MAX];
 
void add_edge(int from, int to, int cap) {
    G[from].push_back((edge){to, cap, int(G[to].size())});
    G[to].push_back((edge){from, 0, int(G[from].size()-1)});
}
 
int dfs(int v, int t, int f) {
    if(v == t) return f;
    used[v] = 1;
    for(int i = 0 ; i < G[v].size(); i++){
        edge &e = G[v][i];
        if(used[e.to] or e.cap <= 0) continue;
        int d = dfs(e.to, t, min(f, e.cap));
        if(d > 0){
            e.cap -= d;
            G[e.to][e.rev].cap += d;
            return d;
        }
    }
    return 0;
}
 
int ford_fulkerson(int s, int t) {
    int flow = 0, f;
    while(1){
        memset(used, 0, sizeof(used));
        f = dfs(s, t, INF);
        if(f == 0) return flow;
        flow += f;
    }
}
