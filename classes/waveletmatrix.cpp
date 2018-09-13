class BitVector{
public:
	int n;

	BitVector(int size, std::vector<bool>& v){}

	// 要素アクセス
	virtual bool operator[](int pos){return true;}

	virtual int zerocount(){return 0;}

	// [0,pos)中の1の出現回数
	virtual int rank(int pos){return 0;}

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
};

// T:入力する値の型 U:使うBitVector
template <typename T, typename U>
class WaveletMatrix{
public:
	int n;
	int a;
	T maxvalue;
	std::vector<std::shared_ptr<BitVector>> bitvector;
	vector<T> v;
	vector<int> indexes;

	WaveletMatrix(int size, vector<T> inp, int defsize= -1) : n(size), v(inp), a(defsize){

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
		indexes = move(index_vec);

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
		return indexes[st];
		return value;
	}

	int rangemax(int st, int en){
		return quantile(st, en, 1);
	}

	int rangemin(int st, int en){
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

