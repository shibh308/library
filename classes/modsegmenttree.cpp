class ModSegmentTree{//遅延セグ木 初期値0で総和を出すやつ
  public:
  ModSegmentTree(ll n);
  void addVal(ll st,ll en,ll val,ll k,ll l,ll r);
  ll calcVal(ll pos);//半開区間 3,6なら3,4,5の総和
  V elements;
  ll pnum;
};
 
ModSegmentTree::ModSegmentTree(ll n){
  pnum=1;while(pnum<n)pnum*=2;
  elements=V(pnum*2-1,0);
}
 
void ModSegmentTree::addVal(ll st,ll en,ll val,ll k=0,ll l=0,ll r=-1){
 
  if(r<0)r=pnum;
  if(en<=l || r<=st) return ;
  if(st<=l && r<=en){
    elements[k] += val;
    elements[k] %= MOD;
    return ;
  }else{
    addVal(st,en,val,2*k+1,l,(l+r)/2);
    addVal(st,en,val,2*k+2,(l+r)/2,r);
  }
}
 
ll ModSegmentTree::calcVal(ll pos) {
    pos += pnum - 1;
    ll sum = 0;
    while(pos){
        sum += elements[pos];
        --pos;
        pos /= 2;
        sum %= MOD;
    }
    sum += elements[0];
    sum %= MOD;
    return sum;
}
