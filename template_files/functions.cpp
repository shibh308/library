ll sqMod(ll x){ 
  return 1LL*x*x%MOD;
}
ll powMod(ll x,ll n){//xのn乗
  if(n==0)return 1;
  else if(n==1)return x;
  if(n%2==0)return (sqMod(powMod(x,n/2)%MOD)%MOD);
  else return ((x*sqMod(powMod(x,n/2)%MOD)%MOD)%MOD);
}
ll sq(ll x){return x*x;}
ll pow_(ll x,ll n){//xのn乗
  if(n==0)return 1;
  else if(n==1)return x;
  if(n%2==0)return (sq(pow_(x,n/2)));
  else return ((x*sq(pow_(x,n/2))));
}
bool Enumrate(vector<int> inpvec,vector<int> &outvec){
  if(inpvec==outvec)return false;
  REP(i,inpvec.size()){
    if(outvec[i]!=inpvec[i]){
      outvec[i]++;
      REPR(j,i-1)outvec[j]=0;
      break;
    }
  }
  return true;
}
S Eratosthenes(int n){
  S set_;
  FOR(i,2,n+1)set_.insert(i);
  FOREACH(s,set_){
    if(s>sqrt(n))break;
    FOREACH(ss,set_){
      if(ss>s&&ss%s==0)set_.erase(ss);
    }
  }
  return set_;
}
int gcd(int m,int n){
  if(0==n)return m;
  return gcd(n,m%n);
}

int lcm(int m,int n){
  int g=gcd(m,n);
  return (m/g*n);
}
V kaitable,gyakutable;
ll ncr(int n,int r){
  return 1LL * kaitable[n] * gyakutable[n-r] % MOD * gyakutable[r]% MOD;
}
ll nhr(int n,int r){
  return ncr(n+r-1,r);
}
void calcTable(int t){
  kaitable = V(t);
  gyakutable = V(t);
  kaitable[0]=1;
  gyakutable[0]=1;
  FOR(i,1,t){
    kaitable[i] = 1LL * kaitable[i-1] * i % MOD;
    gyakutable[i] = powMod(kaitable[i],1e9+5)%MOD;
  }
}
ll kruskal(int n,priority_queue<pair<int,P>,vector<pair<int,P>>,greater<pair<int,P>>> que){
  UnionFind uni(n);
  ll cost = 0;
  while(uni.count!=n-1 && !que.empty()){
    int a = que.top().second.first;
    int b = que.top().second.second;
    int range = que.top().first;
    que.pop();
    if(!uni.Same(a,b)){
      cost += range;
      uni.Unite(a,b);
    }
  }
  if(uni.count != n-1)return -1;
  return cost;
}
void imosTwoDim(int n,int m,V sx,V sy,V ex,V ey,V val){
  int h,w;
  h=n;m=w;
  vector<V> vec(h,V(w,0));
  REP(i,sx.size()){
    if(sx[i]>=0&&sx[i]<h&&sy[i]>=0&&sy[i]<w)
      vec[sx[i]][sy[i]]+=val[i];
    if(ex[i]>=0&&ex[i]<h&&ey[i]>=0&&ey[i]<w)
      vec[ex[i]][ey[i]]+=val[i];
    if(sx[i]>=0&&sx[i]<h&&ey[i]>=0&&ey[i]<w)
      vec[sx[i]][ey[i]]-=val[i];
    if(ex[i]>=0&&ex[i]<h&&sy[i]>=0&&sy[i]<w)
      vec[ex[i]][sy[i]]-=val[i];
  }
  REP(i,h)FOR(j,1,w)vec[i][j]+=vec[i][j-1];
  REP(j,w)FOR(i,1,h)vec[i][j]+=vec[i-1][j];
  
}

int main(){




  V inpvec={1,2,4,6,4};
  V outvec(5,0);
    
  while(Enumrate(inpvec,outvec)){REPR(i,vec.size()-1)SCOUT(vec[i]);ENDL;cou++;}

  return 0;
}

