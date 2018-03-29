//くちもちガチプロをすこれ  http://kutimoti.hatenablog.com/entry/2018/01/27/130831

class UnionFind{
public:
    V par,rank,num;
    int count;
    UnionFind(int n);
    int Find(int x);
    bool Unite(int x,int y);
    bool Same(int x,int y);
    int Count(int x);
};
UnionFind::UnionFind(int n){
    par.resize(n);num=V(n,1);rank=V(n,0);
    count=0;
    REP(i,n)par[i]=i;
}
int UnionFind::Find(int x){
    
    return (par[x]==x?x:Find(par[x]));
}
bool UnionFind::Unite(int x,int y){
    x=Find(x);y=Find(y);//parent
    
    if(x==y)return false;;//end
    if(rank[x]<rank[y]){
      par[x]=y;
      num[y]+=num[x];
      num[x]=0;
    }
    else{
        par[y]=x;
        num[x]+=num[y];
        num[y]=0;
        if(rank[x]==rank[y])rank[x]++;
    }
    count++;
    return true;
}
bool UnionFind::Same(int x,int y){
    return (Find(x)==Find(y));
}
int UnionFind::Count(int x){
  return num[Find(x)];
}

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

class SegmentTree{//RMQ 最小値を出すやつ
  public:
  SegmentTree(int n,V v);
  void updateVal(int pos,int val);
  int calcVal(int st,int en);//半開区間 3,6なら3,4,5の最小値
  V elements;
  int pnum;
};
SegmentTree::SegmentTree(int n,V v){
  pnum=1;while(pnum<n)pnum*=2;
  elements=V(pnum*2-1,MOD);
  
  REP(i,n)updateVal(i,v[i]);
}
void SegmentTree::updateVal(int pos,int val){
  function<void(int)> f = [&](int pos_l){
    elements[pos_l]=min(elements[pos_l*2+1],elements[pos_l*2+2]);
    if(pos_l)f((pos_l-1)/2);
  };
  int num = pos+pnum-1;
  elements[num]=val;
  if(num)f((num-1)/2);
}
int SegmentTree::calcVal(int st,int en){
  function<int(int,int,int,int,int)> f = [&](int st_l,int en_l,int node,int l,int r){
    if(r <= st_l || en_l <= l)return MOD;//交差しない
    if(st_l <= l && r <= en_l)return elements[node];
    int vl = f(st_l,en_l,node*2+1,l,(l+r)/2);
    int vr = f(st_l,en_l,node*2+2,(l+r)/2,r);
    return min(vl,vr);
  };
  return f(st,en,0,0,pnum);
}


class LazySegmentTree{//遅延セグ木 初期値0で総和を出すやつ
  public:
  LazySegmentTree(int n,V v);
  void addVal(int st,int en,int val,int k,int l,int r);
  int calcVal(int st,int en,int k,int l,int r);//半開区間 3,6なら3,4,5の総和
  void eval(int k,int l,int r);
  V elements,lazy;
  int pnum;
};
LazySegmentTree::LazySegmentTree(int n,V v){
  pnum=1;while(pnum<n)pnum*=2;
  elements=V(pnum*2-1,0);
  lazy=V(pnum*2-1,0);
  
  REP(i,n)
    elements[i+pnum-1] = v[i];
  REPR(i,pnum-2)
    elements[i]=elements[i*2+1]+elements[i*2+2];
}
void LazySegmentTree::addVal(int st,int en,int val,int k=0,int l=0,int r=-1){
  if(r<0)r=pnum;
  eval(k,l,r);
  if(en<=l || r<=st) return ;
  if(st<=l && r<=en){
    lazy[k] += (r-l) * val;
    eval(k,l,r);
  }else{
    addVal(st,en,val,2*k+1,l,(l+r)/2);
    addVal(st,en,val,2*k+2,(l+r)/2,r);
    elements[k]=elements[2*k+1]+elements[2*k+2];
  }
}
void LazySegmentTree::eval(int k,int l,int r){
  if(!lazy[k])return ;
  elements[k]+=lazy[k];
  if(r-l>1){
    lazy[2*k+1]+=lazy[k]/2;
    lazy[2*k+2]+=lazy[k]/2;
  }
  lazy[k]=0;
}
int LazySegmentTree::calcVal(int st,int en,int k=0,int l=0,int r=-1) {
  if(r<0)r=pnum;
  eval(k,l,r);

  if(en<=l || r<=st)return 0;
  if(st<=l && r<=en)return elements[k];
  int vl = calcVal(st,en,2*k+1,l,(l+r)/2);
  int vr = calcVal(st,en,2*k+2,(l+r)/2,r);
  return vl + vr;
}

class BinaryIndexedTree{//BIT 加算と区間和 1-indexed
  public:
  int pnum;
  V elements;
  BinaryIndexedTree(int n){pnum=n;elements=V(n+1,0);}
  void add(int pos,int val){
    for(int x=pos;x<pnum;x+=x&-x)elements[x]+=val;
  }
  ll sum(int pos){
    ll ret=0;
    for(int x=pos;x>0;x-=x&-x)ret+=elements[x];
    return ret;
  }
  ll sum(int st,int en){
    return sum(en)-sum(st-1);//閉区間((1,3)なら1,2,3)
  }
};

class FordFulkerson{
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

class RectangleSum{//O(HW)で初期化してO(1)で長方形の和を出す(閉区間)
  public:
  vector<V> sum;
  RectangleSum(vector<V> v,int h,int w){
    sum=vector<V>(h,V(w,0));
    REP(i,h)
      REP(j,w){
        sum[i][j]=v[i][j];
        if(i>0)sum[i][j]+=sum[i-1][j];
        if(j>0)sum[i][j]+=sum[i][j-1];
        if(i>0&&j>0)sum[i][j]-=sum[i-1][j-1];
      }
  }
  ll getSum(int l,int r,int u,int d){//閉区間 第3,4引数が縦に対応してるので注意
    ll ret=sum[d][r];
    if(l>0)ret-=sum[d][l-1];
    if(u>0)ret-=sum[u-1][r];
    if(l>0&&u>0)ret+=sum[u-1][l-1];
    return ret;
  }
};

class UnionFindTwoDim{
public:
    vector<vector<P>> par;
    vector<V> rank;// parent,rank
    UnionFindTwoDim(int n,int m);
    P Find(P x);
    void Unite(P x,P y);
    bool Same(P x,P y);
};
UnionFindTwoDim::UnionFindTwoDim(int n,int m){
    rank = vector<V>(n,V(m,0));
    par = vector<vector<P>>(n,vector<P>(m));
    REP(i,n)REP(j,m)par[i][j]=mp(i,j);
}
P UnionFindTwoDim::Find(P x){
    
    return (par[x.first][x.second]==x?x:Find(par[x.first][x.second]));
}
void UnionFindTwoDim::Unite(P x,P y){
    x=Find(x);y=Find(y);//parent
    
    if(x==y)return;//end
    if(rank[x.first][x.second]<rank[y.first][y.second])par[x.first][x.second]=y;
    else{
        par[y.first][y.second]=x;
        if(rank[x.first][x.second]==rank[y.first][y.second])rank[x.first][x.second]++;
    }
}
bool UnionFindTwoDim::Same(P x,P y){
    return (Find(x)==Find(y));
}

