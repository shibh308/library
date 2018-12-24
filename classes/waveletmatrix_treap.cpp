using value_type = ll;

class Node;
using np = shared_ptr<Node>;

class Node{
public:

	static np nil;

	value_type val;
	uint32_t pri;
	np l = nil;
	np r = nil;

	int size;
	value_type sum;

	Node() : val(0), pri(rndpri()), size(1), sum(0), l(nil), r(nil){}
	Node(value_type v) : val(v), pri(rndpri()), size(1), sum(v), l(nil), r(nil){}
	Node(value_type v, uint32_t p) : val(v), pri(p), size(1), sum(v), l(nil), r(nil){}

	static uint32_t rndpri() {
		static uint32_t x = 123456789, y = 362436069, z = 521288629, w = time(0);
		uint32_t t = x ^ (x << 11);
		x = y;
		y = z;
		z = w;
		w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		return max<uint32_t>(1, w & 0x3FFFFFFF);
	}
};

np Node::nil = make_shared<Node>(value_type(), 0);

class Treap{

public:

	np root;

	Treap() : root(Node::nil){}

	Treap(value_type val) : root(make_shared<Node>(val)){}

	// イテレータが指す[st,en)の範囲で初期化する
	Treap(vector<value_type>::iterator st, vector<value_type>::iterator en) : root(Node::nil){
		while(st != en){
			root = _merge(root, make_shared<Node>(*st));
			++st;
		}
	}

	// 配列で初期化する
	Treap(vector<value_type> v) : root(Node::nil){
		FOREACH(xx,v)
			root = _merge(root, make_shared<Node>(xx));
	}

protected:

	int _size(np x){return x == Node::nil ? 0 : x->size;}
	value_type _sum(np x){return x == Node::nil ? 0 : x->sum;}

	np _update(np x){
		x->size = _size(x->l) + _size(x->r) + 1;
		x->sum = _sum(x->l) + _sum(x->r) + x->val;
		return x;
	}

	np _merge(np l, np r){
		if(l == Node::nil || r == Node::nil)
			return l == Node::nil ? r : l;

		if(l->pri > r->pri){
			l->r = _merge(l->r, r);
			return _update(l);
		}else{
			r->l = _merge(l, r->l);
			return _update(r);
		}
	}

	pair<np,np> _split(np x, int k){
		if(x == Node::nil)
			return mp(Node::nil, Node::nil);

		if(k <= _size(x->l)){
			pair<np,np> s = _split(x->l, k);
			x->l = s.second;
			return mp(s.first, _update(x));

		}else{
			pair<np,np> s = _split(x->r, k - _size(x->l) - 1);
			x->r = s.first;
			return mp(_update(x), s.second);
		}
	}

	np _insert(np x, int k, value_type val){
		np l,r;
		tie(l, r) = _split(x, k);
		return _merge(_merge(l, make_shared<Node>(val)), r);
	}
	
	np _erase(np x, int k){
		np l,r,m;
		tie(l, r) = _split(x, k);
		tie(m, r) = _split(r, 1);
		return _merge(l, r);
	}

	void _set(np x, int k, value_type val){
		if(k < _size(x->l))
			_set(x->l, k, val);
		else if(_size(x->l) == k)
			x->val = val;
		else
			_set(x->r, k - _size(x->l) - 1, val);

		_update(x);
	}

	void _add(np x, int k, value_type val){
		if(k < _size(x->l))
			_add(x->l, k, val);
		else if(_size(x->l) == k)
			x->val += val;
		else
			_add(x->r, k - _size(x->l) - 1, val);

		_update(x);
	}

	value_type _get(np x, int k){
		if(k < _size(x->l))
			return _get(x->l, k);
		else if(_size(x->l) == k)
			return x->val;
		else
			return _get(x->r, k - _size(x->l) - 1);
	}

	value_type _rangesum(np x, int l, int r){
		l = max(l, 0);
		r = min(r, _size(x));
		if(l >= r)
			return 0;
		if(l == 0 && r == _size(x))
			return _sum(x);
		value_type retval(0);
		int sl = _size(x->l);
		retval += _rangesum(x->l, l, r);
		retval += _rangesum(x->r, l - sl - 1, r - sl - 1);
		if(l <= sl && sl < r)
			retval += x->val;
		return retval;
	}

	int _lowerbound(np x, value_type val){
		if(x == Node::nil)
			return 0;
		if(val < x->val)
			return _lowerbound(x->l, val);
		else
			return _lowerbound(x->r,val) + _size(x->l) + 1;
	}

	np _insert(np x, value_type val){
		return _insert(x, _lowerbound(x, val), val);
	}

public:

	void push_front(value_type val){
		root = _merge(make_shared<Node>(val), root);
	}

	void push_back(value_type val){
		root = _merge(root, make_shared<Node>(val));
	}

	void pop_front(){
		root = _split(root, 1).second;
	}

	void pop_back(){
		root = _split(root, _size(root) - 1).first;
	}

	// rootを含めたサイズの出力
	int size(){
		return root->size;
	}

	// [l, r)の総和 (同様の実装でRMQ等も可能)
	value_type rangesum(int l, int r){
		return _rangesum(root, l, r);
	}

	// k番目への代入
	void set(int k, value_type val){
		return _set(root, k, val);
	}

	// k番目への加算
	void add(int k, value_type val){
		return _add(root, k, val);
	}

	// k番目の取得
	value_type get(int k){
		return _get(root, k);
	}

	// k番目への挿入
	void insert(int k, value_type val){
		root = _insert(root, k, val);
	}

	// 適切な位置への挿入
	void insert(value_type val){
		root = _insert(root, val);
	}

	// val <= get(k) となるような最小のk
	int lowerbound(value_type val){
		return _lowerbound(root, val);
	}

	// k番目の要素削除
	void erase(int k){
		root = _erase(root, k);
	}

};

class BitVector{
public:
	int n;

	BitVector(int size, std::vector<bool>& v){}

	// 要素アクセス
	virtual bool operator[](int pos) = 0;

	virtual int zerocount() = 0;

	// [0,pos)中の1の出現回数
	virtual int rank(int pos) = 0;

	virtual void insert(int pos, bool val) = 0;
	virtual void erase(int pos) = 0;

	int rank(int pos, bool value){
		return value ? rank(pos) : pos - rank(pos);
	}
	// [st,en)中のrank
	int rank(int st, int en, bool value){
		return rank(en, value) - rank(st, value);
	}

	// ind番目の1の出現
	int select(int ind){
		return select(true, ind);
	}
	int select(int ind, bool value){
		int st = -1;
		int en = n + 1;
		while(en - st > 1){
			int num = (st + en) / 2;
			((rank(num, value) >= ind) ? en : st) = num;
		}
		return en;
	}
};

class BitVector_uint64 : public BitVector{
public:

	vector<uint64_t> bitvector;
	vector<int> accumvector;

	bool operator[](int pos){
		return (bitvector[pos / 64] >> (pos % 64)) & 1;
	}

	int zerocount(){
		return n - accumvector.back();
	}

	BitVector_uint64(int size, std::vector<bool> v) : BitVector(size, v){
		n = size;
		bitvector.resize((n + 63) / 64, 0);
		accumvector.resize((n + 63) / 64, 0);

		REP(i,n){
			if(i && (i % 64 == 0))
				accumvector[i / 64] = accumvector[i / 64 - 1];

			bitvector[i / 64] |= (v[i] << (i % 64));
			accumvector[i / 64] += v[i];
		}
	}

	int rank(int pos){
		return (pos / 64 ? accumvector[pos / 64 - 1] : 0) + __builtin_popcount(bitvector[pos / 64] & ((1LL << (pos % 64)) - 1));
	}
	void insert(int pos, bool val){}
	void erase(int pos){}
};

// T:入力する値の型 U:使うBitVector
template <typename T, typename U>
class WaveletMatrix{
public:
	int n;
	int a;
	T maxvalue;
	std::vector<std::shared_ptr<BitVector>> bitvector;

	WaveletMatrix(int size, vector<T> inp, int defsize= -1) : n(size), a(defsize){

		// 値は全て正の値である前提で扱う
		REP(i,n)
			REPR(j,63)
				if(inp[i] & (1LL<<j)){
					a = max(1LL * a, j + 1);
					break;
				}

		bitvector.resize(a);
		vector<int> index_vec(n);
		iota(ALL(index_vec), 0);
		queue<int> que_1, que_2;

		REP(i,a){
			vector<bool> boolvec(n, false);
			int j = 0;
			FOREACH(k, index_vec){
				boolvec[j] = inp[k] & (1LL << (a - i - 1));
				(boolvec[j] ? que_2 : que_1).push(k);
				++j;
			}
			j = 0;
			while(!que_1.empty()){
				index_vec[j] = que_1.front();
				que_1.pop();
				++j;
			}
			while(!que_2.empty()){
				index_vec[j] = que_2.front();
				que_2.pop();
				++j;
			}
			bitvector[i] = std::make_shared<U>(n, move(boolvec));
		}

	}

	// [0,index)にvalueがいくつ存在するか
	int rank(int index, T value){
		assert((1LL<<a) > value);
		return rank(0, index, value);
	}

	int rank(int st, int en, T value){
		assert((1LL<<a) > value);
		REP(i,a){
			bool flag = value & (1LL << (a - i - 1));
			st = bitvector[i]->rank(st, flag);
			en = bitvector[i]->rank(en, flag);
			if(flag){
				st += bitvector[i]->zerocount();
				en += bitvector[i]->zerocount();
			}
		}

		return en - st;
	}

	int select(int ind, T value){
		assert((1LL<<a) > value);
		int st = -1;
		int en = n + 1;

		while(en - st > 1){
			int num = (st + en) / 2;
			((rank(num, value) >= ind) ? en : st) = num;
		}
		return en;
	}

	// [st,en)中でk番目に大きな値 (kは1-indexed)
	T quantile(int st, int en, int k){
		assert(k && en - st >= k);
		T value(0);
		REP(i,a){
			int count = bitvector[i]->rank(st, en, true);
			if(count >= k){
				st = bitvector[i]->zerocount() + bitvector[i]->rank(0, st, true);
				en = st + count;
				value += 1LL << (a - i - 1);
			}else{
				int bef_st = st;
				st = bitvector[i]->rank(0, st, false);
				en = st + (en - bef_st) - count;
				k -= count;
			}
		}
		return value;
	}

	T rangemax(int st, int en){
		return quantile(st, en, 1);
	}

	T rangemin(int st, int en){
		return quantile(st, en, en - st);
	}

	// [st,en)中で[0,value)を満たす値の数
	int rangebelow(int st, int en, T value){
		assert((1LL<<a) > value);
		int retval = 0;
		REP(i,a){
			if(!(en-st))
				break;
			bool flag = value & (1LL << (a - i - 1));
			int count = bitvector[i]->rank(st, en, true);
			if(flag){
				retval += (en - st) - count;
				st = bitvector[i]->zerocount() + bitvector[i]->rank(0, st, true);
				en = st + count;
			}else{
				st = bitvector[i]->rank(0, st, false);
				en = st + (en - st) - count;
			}
		}
		return retval;
	}

	// [st,en)中で[min,max)を満たす値の数
	int rangefreq(int st, int en, T minval, T maxval){
		assert((1LL<<a) > minval && (1LL<<a) > maxval);
		return rangebelow(st, en, maxval) - rangebelow(st, en, minval);
	}

};

class BitVector_Treap : public BitVector{
public:

	Treap t;

	bool operator[](int pos){
		return t.get(pos);
	}

	int zerocount(){
		return n - t.rangesum(0, n);
	}

	vector<ll> vectoll(vector<bool>& v){
		vector<ll> vv;
		FOREACH(xx,v)
			vv.pb(xx);

		return vv;
	}

	BitVector_Treap(int size, vector<bool> v) : BitVector(size, v), t(vectoll(v)){
		n = size;
	}

	int rank(int pos){
		return t.rangesum(0, pos);
	}

	void insert(int pos, bool val){
		t.insert(pos, val);
		++n;
	}

	void erase(int pos){
		t.erase(pos);
		--n;
	}
};


template <typename T>
class WaveletMatrix_Treap : public WaveletMatrix<T, BitVector_Treap>{
public:
	using WaveletMatrix<T, BitVector_Treap>::WaveletMatrix;

	void insert(int pos, T val){
		++this->n;
		REP(i, this->a){ 
			bool flag = val & (1LL << (this->a - i - 1));

			if(flag){
				this->bitvector[i]->insert(pos, true);
				pos = this->bitvector[i]->zerocount() + this->bitvector[i]->rank(0, pos, true);
			}else{
				this->bitvector[i]->insert(pos, false);
				pos -= this->bitvector[i]->rank(0, pos, true);
			}
		}
	}

	void erase(int pos){
		--this->n;
		T val = this->rangemax(pos, pos + 1);

		REP(i, this->a){
			bool flag = val & (1LL << (this->a - i - 1));
			this->bitvector[i]->erase(pos);

			if(flag){
				pos = this->bitvector[i]->zerocount() + this->bitvector[i]->rank(0, pos, true);
			}else{
				pos -= this->bitvector[i]->rank(0, pos, true);
			}
		}
	}

	void update(int pos, T val){
		erase(pos);
		insert(pos, val);
	}

};

