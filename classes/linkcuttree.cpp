using value_type = ll;


class Node;
using np = shared_ptr<Node>;

class Node{
public:

	value_type val, sum, lazy = 0;

	int index = -1;

	np p,l,r;

	int size = 1;
	bool rev = false;

	Node() : val(value_type()), sum(value_type()){}
	Node(value_type v) : val(v), sum(v){}
	Node(value_type v, int idx) : val(v), sum(v), index(idx){}


};

class LinkCutTree{

public:

	LinkCutTree()
	{
	}

	np makenode(value_type v){
		return make_shared<Node>(v);
	}

	np makenode(value_type v, int idx){
		return make_shared<Node>(v, idx);
	}

	void update(np x){
		x->size = 1;
		x->sum = x->val;

		if(x->r){
			x->size += x->r->size;
			x->sum += x->r->sum;
		}
		if(x->l){
			x->size += x->l->size;
			x->sum += x->l->sum;
		}
	}


	bool isroot(np x){
		return !(x->p)  || (x->p->l != x && x->p->r != x);
	};

	void rotr(np x){
		np q = x->p; // 一つ上の親
		np qq = q->p; // 二つ上の親

		if((q->l = x->r)) // xの右に子があったらqに付け替える
			x->r->p = q;

		x->r = q; // qとxで親子関係の入れ替え
		q->p = x;

		update(q);
		update(x);

		if((x->p = qq)){
			// 二つ上の親からみた子(qがあった所)をxに更新
			if(qq->l == q)
				qq->l = x;
			if(qq->r == q)
				qq->r = x;

			update(qq);
		}
	}

	void rotl(np x){
		np q = x->p; // 一つ上の親
		np qq = q->p; // 二つ上の親

		if((q->r = x->l)) // xの左に子があったらqに付け替える
			x->l->p = q;

		x->l = q; // qとxで親子関係の入れ替え
		q->p = x;

		update(q);
		update(x);

		if((x->p = qq)){
			// 二つ上の親からみた子(qがあった所)をxに更新
			if(qq->l == q)
				qq->l = x;
			if(qq->r == q)
				qq->r = x;

			update(qq);
		}
	}

	// 対象のノードをsplay木の親まで持っていく
	np splay(np x){
		push(x);

		while(!isroot(x)){
			np q = x->p;

			if(isroot(q)){

				push(q);
				push(x);

				if(q->l == x)
					rotr(x);
				else
					rotl(x);
				break;
			}

			np qq = q->p;

			push(qq);
			push(q);
			push(x);

			if(qq->l == q){
				if(q->l == x){
					rotr(q); // 一直線なら
					rotr(x);
				}else{
					rotl(x);
					rotr(x);
				}
			}else{
				if(q->r == x){
					rotl(q); // 一直線なら
					rotl(x);
				}else{
					rotr(x);
					rotl(x);
				}
			}
		}

		return x;
	}

	// xと根のパスを繋げて、根を返す
	np expose(np x){
		np y;
		// どんどん親に向かっていく
		for(np q = x; q; q = q->p){
			splay(q);
			q->r = y;
			update(q);
			y = q;
		}
		splay(x);

		return y;
	}

	// 反転処理 遅延評価で呼び出す
	void toggle(np x){
		swap(x->l, x->r);
		x->rev ^= 1;
	}

	// パスへの値追加 遅延評価で呼び出す
	void propagate(np x, value_type val){

		x->lazy += val;
		x->val += val;
		x->sum += (val * x->size);
	}


	// 遅延評価
	void push(np x){

		if(x->lazy){
			if(x->r)
				propagate(x->r, x->lazy);
			if(x->l)
				propagate(x->l, x->lazy);

			x->lazy = 0;
		}

		if(x->rev){
			if(x->r)
				toggle(x->r);
			if(x->l)
				toggle(x->l);

			x->rev = false;
		}
	}

	// xとyを繋げる xが根になる
	void link(np x, np y){
		expose(y);
		expose(x);
		x->r = y;
		y->p = x;
	}

	// xを根から切る
	void cut(np x){
		expose(x);
		np y = x->l;
		x->l.reset();
		y->p.reset();
	}

	np root(np x){
		expose(x);
		while(x->l)
			x = x->l;
		return x;
	}

	// xを根にする
	void evert(np x){
		expose(x);
		toggle(x);
		push(x);
	}

	np lca(np x, np y){
		expose(x);
		return expose(y);
	}

	// 根とxとのパスに重みを加算
	void set_propagate(np x, value_type val){
		expose(x);
		propagate(x, val);
		push(x);
	}

};

