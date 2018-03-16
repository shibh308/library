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

