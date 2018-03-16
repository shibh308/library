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

