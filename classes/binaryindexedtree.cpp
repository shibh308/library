class BinaryIndexedTree{//BIT 加算と区間和 内部1-indexed
  public:
  int pnum;
  V elements;
  BinaryIndexedTree(int n){pnum=n+1;elements=V(pnum,0);}
  void add(int pos,int val){ //0-indexedで呼び出す
	++pos;
    for(int x=pos;x<pnum;x+=x&-x)elements[x]+=val;
  }
  ll sum(int pos){ //1-indexedで呼び出される
    ll ret=0;
    for(int x=pos;x>0;x-=x&-x)ret+=elements[x];
    return ret;
  }
  ll sum(int st,int en){
    return sum(en)-sum(st);//0-indexedの半開区間 [0,3)なら0,1,2
  }
};



