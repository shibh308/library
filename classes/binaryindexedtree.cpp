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

