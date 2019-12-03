template <typename T>
struct Dinic{
    struct Edge{
        int to, rev;
        T cap;
        Edge(int to, T cap, int rev) : to(to), rev(rev), cap(cap){}
    };

    vector<vector<Edge>> edges;
    T _inf;
    vector<T> min_cost;
    vector<int> cnt;

    Dinic(int n) : edges(n), _inf(numeric_limits<T>::max()){}

    void add(int from, int to, T cap){
        edges[from].emplace_back(to, cap, static_cast<int>(edges[to].size()));
        edges[to].emplace_back(from, 0, static_cast<int>(edges[from].size()) - 1);
    }

    bool bfs(int s, int t){
        min_cost.assign(edges.size(), -1);
        queue<int> que;
        min_cost[s] = 0;
        que.emplace(s);
        while(!que.empty() && min_cost[t] == -1){
            int x = que.front();
            que.pop();
            for(auto& ed : edges[x])
                if(ed.cap > 0 && min_cost[ed.to] == -1){
                    min_cost[ed.to] = min_cost[x] + 1;
                    que.emplace(ed.to);
                }
        }
        return min_cost[t] != -1;
    }

    T dfs(int idx, int t, T flow){
        if(idx == t)
            return flow;
        T ret = 0;
        while(cnt[idx] < edges[idx].size()){
            auto& ed = edges[idx][cnt[idx]];
            if(ed.cap > 0 && min_cost[idx] < min_cost[ed.to]){
                T d = dfs(ed.to, t, min(flow, ed.cap));
                ed.cap -= d;
                edges[ed.to][ed.rev].cap += d;
                ret += d;
                flow -= d;
                if(flow == 0)
                    break;
            }
            ++cnt[idx];
        }
        return ret;
    }

    T solve(int s, int t){
        T flow = 0;
        while(bfs(s, t)){
            cnt.assign(edges.size(), 0);
            T f = 0;
            while((f = dfs(s, t, _inf)) > 0)
                flow += f;
        }
        return flow;
    }

};

