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

