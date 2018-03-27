template <typename T>
struct node_t{//平衡二分探索木のノード
 
  node_t *child[2];
  T val;
  int size;//部分木のサイズ
  int sum;//部分木の総和
 
  node_t(T v):val(v),sum(v),size(1){
    child[0]=NULL;
    child[1]=NULL;
  }
 
  ~node_t(){
    delete child[0];
    delete child[1];
  }

  static int Rand(){
    static int x=283593859;//適当なシード
    static int y=994833231;
    static int z=644315351;
    static int w=94583131;
    int t;
    t=x^(x<<11);
    x=y;y=z;z=w;
    return w=(w^(w>>19))^(t^(t>>8));
  }
 
  static int Size(node_t *x){
    return (!x?0:x->size);//空なら0
  }
 
  static int Sum(node_t *x){
    return (!x?0:x->sum);
  }
 
  static node_t *Update(node_t *x){
    x->size=Size(x->child[0])+Size(x->child[1])+1;
    x->sum=Sum(x->child[0])+Sum(x->child[1])+x->val;
    return x;
  }
 
  static node_t *Merge(node_t *x,node_t *y){
    if(!x || !y)return(x?x:y);
    if(Rand() % (Size(x)+Size(y)) < Size(x)){//xの方が高いならxの部分木とyをマージ
      x->child[1] = Merge(x->child[1],y);
      return Update(x);
    }else{
      y->child[0] = Merge(x,y->child[0]);
      return Update(y);
    }
  }
 
  static pair<node_t*,node_t*> Split(node_t *x,int k){//k番目を基準に[0,k)と[k,n)へ分割
    if(!x)return mp(nullptr,nullptr);
    if(k<=Size(x->child[0])){
      pair<node_t*,node_t*> s = Split(x->child[0],k);
      x->child[0]=s.second;
      return mp(s.first,Update(x));
    }else{
      pair<node_t*,node_t*> s= Split(x->child[1],k-Size(x->child[0]) - 1);
      x->child[1] = s.first;
      return mp(Update(x),s.second);
    }
  }

  static int LowerBound(node_t *x,T val){
    if(!x)return 0;
    if(val < (x->val) )return LowerBound(x->child[0],val);
    return LowerBound(x->child[1],val) + Size(x->child[0]) + 1;
  }
 
  static node_t *Insert(node_t *x,int k,node_t *new_x){//xのk番目にnew_xを追加
    pair<node_t*,node_t*> s = Split(x,k);
    x = Merge(Merge(s.first,new_x),s.second);//xを分割した後に3つをマージ
    return Update(x);
  }
  static node_t *Insert(node_t *x,node_t *new_x){//要素valを適切な値に挿入する
    pair<node_t*,node_t*> s = Split(x,LowerBound(x,new_x->val));
    x = Merge(Merge(s.first,new_x),s.second);
    return Update(x);
  }
 
  static node_t *Erase(node_t *x,int k){//k番目の要素を削除
    /*
    pair<node_t*,node_t*> a = Split(x,k+1);//3つに分けてからk以外をマージ
    pair<node_t*,node_t*> b = Split(a.first,k);
    return mp(Merge(b.first,a.second),b.second);//returnされるsecondは削除したノード
    */
    pair<node_t*,node_t*> a = Split(x,k);//3つに分けてからk以外をマージ
    pair<node_t*,node_t*> b = Split(a.second,1);
    delete b.first;
    x = Merge(a.first,b.second);
    return x;
  }
 
};
 
template<typename T>
class Treap{//平衡二分探索木 indexに注意(rootの初期値に最小値があるためGet等が1-indexed)
  typedef node_t<T> node;//省略
  public:
  node *root_;
 
  Treap(){
 
   //  root_=NULL;
   root_=new node(numeric_limits<T>::min());//rootの初期値を最小値にする
  }
 
  int LowerBound(T val){//val以上の値の位置
    return node::LowerBound(root_,val);
  }
 
  void Insert(int k,T val){//k番目に要素valを挿入する
    root_ = node::Insert(root_,k,new node(val));
  }
 
  void Insert(T val){//要素valを適切な値に挿入する
    root_ = node::Insert(root_,new node(val));
  }
 
  T Erase(int k){//k番目の要素を削除 新しい木の根を返す
    root_ = node::Erase(root_,k);
  }
 
  int Size(){return node::Size(root_);}//サイズ取得
 
  T Get(int k){//k番目の要素を確認する
    if(k<0||k>=Size())return 0;
    auto sl = node::Split(root_,k);//3つに分解して真ん中のvalを取得する
    auto sr = node::Split(sl.second,1);
    auto lr = sr.first;
    T val = lr->val;
    root_=node::Merge(node::Merge(sl.first,lr),sr.second);
    return val;
  }
 
  void Set(int k,T val){//k番目の要素をvalに書き換える
    auto sr = node::Split(root_,k+1);//3つに分解して真ん中のvalを書き換える
    auto sl = node::Split(sr.first,k);
    auto lr = sl.second;
    lr->val=val;
    root_=node::Merge(node::Merge(sl.first,lr),sr.second);
  }
 
};


