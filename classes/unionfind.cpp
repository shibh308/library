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

