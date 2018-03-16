class RectangleSum{//O(HW)で初期化してO(1)で長方形の和を出す(閉区間)
  public:
  vector<V> sum;
  RectangleSum(vector<V> v,int h,int w){
    sum=vector<V>(h,V(w,0));
    REP(i,h)
      REP(j,w){
        sum[i][j]=v[i][j];
        if(i>0)sum[i][j]+=sum[i-1][j];
        if(j>0)sum[i][j]+=sum[i][j-1];
        if(i>0&&j>0)sum[i][j]-=sum[i-1][j-1];
      }
  }
  ll getSum(int l,int r,int u,int d){//閉区間 第3,4引数が縦に対応してるので注意
    ll ret=sum[d][r];
    if(l>0)ret-=sum[d][l-1];
    if(u>0)ret-=sum[u-1][r];
    if(l>0&&u>0)ret+=sum[u-1][l-1];
    return ret;
  }
};

