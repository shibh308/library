class Dijkstra{
public:
    Dijkstra(vector<vector<P>> ed,int firs,int pnum);
    void Solve();
    V range;// range[a]=b;
    vector<vector<P>> edges;// [a][b]=c;
    priority_queue<P,vector<P>,greater<P>> que;// queue=(range,point);
    V keiro;
    V CalcRoute(int startp,int endp);
};

Dijkstra::Dijkstra(vector<vector<P>> ed,int firs,int pnum){
    edges=ed;
    V ttt(pnum,INF);
    range=ttt;
    range[firs]=0;
    que.push(mp(0,firs));
    keiro=V(pnum);
    REP(i,pnum)keiro[i]=i;
}

void Dijkstra::Solve(){
    while(!que.empty()){
        P top_=que.top();
        que.pop();
        FOREACH(x,edges[top_.second]){
            if(range[x.first] > range[top_.second] + x.second){
                range[x.first] = range[top_.second] + x.second;
                que.push(mp(range[x.first],x.first));
                keiro[x.first] = top_.second;
            }
        }
    }
}

V Dijkstra::CalcRoute(int startp,int endp){
  V vec(1,endp);
  int point = endp;
  while(point==startp){
    point = keiro[point];
    vec.pb(point);
  }
  return vec;
}

