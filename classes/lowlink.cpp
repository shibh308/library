class Lowlink{//O(n+m)時間で橋と関節点の列挙をする
  public:
  int pnum,edgenum;
  V edge_a,edge_b;
  vector<V> edges;
  V articulations;//関節点
  vector<P> bridges;//橋
  V ord,vis,low;
  int k=0;
  Lowlink(int n,int m,V va,V bn);
  void Solve();
  void Dfs(int v,int p);
};

Lowlink::Lowlink(int n,int m,V va,V vb){
  edge_a=va;
  edge_b=vb;
  pnum=n;
  edgenum=m;
  edges.resize(m);
  ord = V(n,0);vis = V(n,0);low = V(n,0);
  REP(i,m){edges[edge_a[i]].pb(edge_b[i]);edges[edge_b[i]].pb(edge_a[i]);}
}

void Lowlink::Solve(){
  REP(i,pnum)if(!vis[i])Dfs(i,-1);
  sort(ALL(articulations));sort(ALL(bridges));
}

void Lowlink::Dfs(int v,int p){
  vis[v]=1;
  ord[v]=k++;
  low[v]=ord[v];
  bool flag=false;
  int ct=0;
  REP(i,edges[v].size()){
    if(!vis[edges[v][i]]){
      ct++;
      Dfs(edges[v][i],v);
      low[v]=min(low[v],low[edges[v][i]]);
      if(!p && ord[v] <= low[edges[v][i]])flag=true;
      if(ord[v]<low[edges[v][i]])bridges.pb(mp(min(v,edges[v][i]),max(v,edges[v][i])));
    }else if(edges[v][i] != p)
      low[v] = min(low[v],ord[edges[v][i]]);
  }
  if(p==-1&&ct>1)flag=true;
  if(flag)articulations.pb(v);
}

