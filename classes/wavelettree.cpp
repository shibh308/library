class WaveletTreeNode{
public:

  vector<ll> rui_bit;
  vector<bool> binary;
  int n;
  ll value = LINF;
  ll st,en,bound;// [st,en)をカバーする

  vector<WaveletTreeNode*> childs;

  // 座標圧縮なしでの構築 再帰的に末端ノードまで展開する
  WaveletTreeNode(int len, vector<ll>& inp_vec) : n(len){

    st = *min_element(ALL(inp_vec));
    en = *max_element(ALL(inp_vec)) + 1;

    // [0,2)なら1 [0,8)なら4 境界の大きい側
    bound = (st + en) / 2;


    // 単一要素のみからできていたら末端ノードにする
    if(en - st == 1){
      value = st;
      return ;
    }

    childs.resize(2);

    binary.resize(n, 0);

    // 左右への振り分け
    vector<V> left_right(2);
    REP(i,n){
      bool is_right = (inp_vec[i] >= bound);
      left_right[is_right].pb(inp_vec[i]);
      binary[i] = is_right;
    }

    rui_bit = V(n, binary[0]);
    REP(i,n-1)rui_bit[i+1]=rui_bit[i]+binary[i+1];

    childs.at(0) = new WaveletTreeNode(left_right[0].size(), left_right[0]);
    childs.at(1) = new WaveletTreeNode(left_right[1].size(), left_right[1]);
  }

  // [0,pos)中にstateが含まれる数
  int bitRank(bool state, int pos){
    if(!pos)return 0;
    return state ? rui_bit[pos - 1] : pos - rui_bit[pos - 1];
  }
  // num+1回目のstateの出現位置
  int bitSelect(bool state, int num){
    ++num;
    if( (state ? rui_bit[n-1] : n - rui_bit[n-1]) < num)
      return INF;

    int ok = n-1;int ng = -1;
    while(ok - ng > 1){
      int mid = (ok + ng) / 2;
      ((state ? rui_bit[mid] : mid + 1 - rui_bit[mid]) >= num ? ok : ng) = mid;
    }
    return ok;
  }

  // v[index]を返す
  int Access(int index){
    return (childs.empty() ? value : childs[binary[index]]->Access(bitRank(binary[index], index)));
  }

  // [0,pos)中にvalが含まれる数
  int Rank(ll val, int pos){

    if(childs.empty())
      return -1;

    bool is_right = (val >= bound);

    // ここのRankのposを変えます
    int rank = childs[is_right]->Rank(val, bitRank(is_right, pos));
    if(rank == -1)
      return bitRank(is_right, pos);
    else
      return rank;
  }

  // num+1回目のvalの出現位置
  int Select(ll val, int num){

    if(childs.empty())
      return -1;
    
    bool is_right = (val >= bound);

    // 順方向にいろいろする
    int sele = childs[is_right]->Select(val, num);
    if(sele == -1)
      return bitSelect(is_right, num);
    else
      return bitSelect(is_right, sele);
  }

  // [st,en)の最大値
  ll rangeMax(int st, int en){
    if(childs.empty())
      return value;
    bool is_right = (bitRank(1, en) != bitRank(1, st));
    return childs[is_right]->rangeMax(bitRank(is_right, st), bitRank(is_right, en));
  }

  // [st,en)の最小値
  ll rangeMin(int st, int en){
    if(childs.empty())
      return value;
    bool is_right = !(bitRank(0, en) != bitRank(0, st));
    return childs[is_right]->rangeMin(bitRank(is_right, st), bitRank(is_right, en));
  }

};
