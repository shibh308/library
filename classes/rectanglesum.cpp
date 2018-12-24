class RectangleSum{//O(HW)で初期化してO(1)で長方形の和を出す(半開区間)
  public:
  vector<V> sum;
  RectangleSum(vector<V>& v){
	  int h = v.size();
	  int w = v[0].size();

	  sum.resize(h + 1, V(w + 1, 0));

	  REP(i,h)REP(j,w)
		  sum[i+1][j+1] = v[i][j];

	  REP(i,h + 1)REP(j,w)
		  sum[i][j+1] += sum[i][j];

	  REP(i,h)REP(j,w + 1)
		  sum[i + 1][j] += sum[i][j];
  }
  ll getSum(int sx, int sy, int ex, int ey){
    return sum[ex][ey] + sum[sx][sy] - sum[sx][ey] - sum[ex][sy];
  }
};

