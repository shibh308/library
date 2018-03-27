class UnionFind{
public:
    V par,rank,num;
    vector<list<int>> child;
    int count;//今までに何回併合されたか
    UnionFind(int n);
    int Find(int x);//xの親が何か
    bool Unite(int x,int y);//xとyの併合
    bool Same(int x,int y);//xとyが同じ集合に含まれるか
    int Count(int x);//xと同じ集合に含まれる要素の数
    list<int> Child(int x);//xと同じ集合に含まれる要素の列挙
};

UnionFind::UnionFind(int n){
    par.resize(n);num=V(n,1);rank=V(n,0);
    child.resize(n);
    count=0;
    REP(i,n){par[i]=i;child[i].pb(i);}
}

int UnionFind::Find(int x){
    return (par[x]==x?x:Find(par[x]));
}

bool UnionFind::Unite(int x,int y){
    x=Find(x);y=Find(y);
    
    if(x==y)return false;
    if(rank[x]<rank[y]){
      par[x]=y;
      num[y]+=num[x];
      child[y].splice(child[y].end(),move(child[x]));
      num[x]=0;
    }
    else{
      par[y]=x;
      num[x]+=num[y];
      child[x].splice(child[x].end(),move(child[y]));
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

list<int> UnionFind::Child(int x){
  return child[Find(x)];
}

