class FordFulkerson{//最大流(最小カット)を求める 辺の形式に注意
  public:
  FordFulkerson(vector<M> ed,int n);
  int Dfs(int v,int t,int f);
  ll Solve(int s,int t);
  int pnum;
  vector<M> edges;
  V flag;
};

FordFulkerson::FordFulkerson(vector<M> ed,int n){
  pnum=n;
  edges=ed;
}

int FordFulkerson::Dfs(int s,int t,int f){
  if(s==t)return f;
  flag[s]=true;
  FOREACH(e,edges[s]){
    if(!flag[e.first] && e.second>0){
      int d = Dfs(e.first,t,min(f,e.second));
      if(d>0){
        e.second-=d;
        edges[e.first][s]+=d;
        return d;
      }
    }
  }
  return 0;
}

ll FordFulkerson::Solve(int s,int t){
  ll ret=0;
  while(1){
    flag=V(pnum,0);
    int f=Dfs(s,t,INF);
    if(!f)return ret;
    ret+=f;
  }
}

