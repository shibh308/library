template<typename T>
class Compression{
  public:
  vector<T> compvec;
  void Comp(vector<T> inp){//圧縮する
    compvec = inp;
    sort(ALL(compvec));
    compvec.erase(unique(ALL(compvec)),compvec.end());
  }
  int Index(T val){//圧縮を元に対応するインデックスを返す
    auto it = lower_bound(ALL(compvec),val);
    return (*it==val?distance(compvec.begin(),it):-1);
  }
};