class PartPersistentUnionFind{//部分永続Union-Find
public:
    V par,rank,time;
    int count;//今までに何回併合されたか
    PartPersistentUnionFind(int n);
    int Find(int t,int x);//時刻tのxの親が何か
    bool Unite(int x,int y);//xとyの併合
    bool Same(int t,int x,int y);//時刻tにxとyが同じ集合に含まれるか
};

PartPersistentUnionFind::PartPersistentUnionFind(int n){
    par.resize(n);rank=V(n,0);
    time=V(n,INF);
    count=0;
    iota(ALL(par),0);
}

int PartPersistentUnionFind::Find(int t,int x){
    if(time[x]>t)return x;
    return Find(t,par[x]);
}

bool PartPersistentUnionFind::Unite(int x,int y){
    x=Find(count,x);y=Find(count,y);
    
    count++;//ここは変えてもいいかもしれない
    if(x==y)return false;
    if(rank[x]<rank[y]){
      par[x]=y;
      time[x]=count;
    }
    else{
      par[y]=x;
      time[y]=count;
      if(rank[x]==rank[y])rank[x]++;
    }
    return true;
}

bool PartPersistentUnionFind::Same(int t,int x,int y){
    return (Find(t,x)==Find(t,y));
}
