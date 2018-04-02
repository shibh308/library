int n;//要素数
int m;//最大でいくつ先を見るか(木なら最大の深さ…etc)

int t = 1
for(int i=1;i<=m;i<<=1)t++;
t--;
vector<V> next(n,V(t,-1));
auto dub = [&]{//ダブリングの下準備
  auto func = [&](int pos,int num){
    if(!num)return ed[pos];//ここを適当に変えてください
    return (next[pos][num-1]==-1?-1:next[next[pos][num-1]][num-1]);
  };
  REP(i,t)
    REP(j,n)
      next[j][i]=func(j,i);
};
auto calcdub = [&](int pos,int num){
  //posからnum個先を計算する
  int p = pos;
  REP(i,t){
    if(num & 1<<i && p!=-1)
      p = next[p][i];
  }
  return p;
};
