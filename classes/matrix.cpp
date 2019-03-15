struct Matrix{
	int h, w;
	vector<i64> v;

	Matrix(int h, int w) : h(h), w(w), v(h * w, 0){}

	Matrix(vector<vector<i64>> v_) : h(v_.size()), w(v_[0].size()), v(h * w){
		for(int i = 0; i < h; ++i)
			for(int j = 0; j < w; ++j)
				v[i * w + j] = v_[i][j];
	}

	static Matrix makeUnit(int n){
		Matrix mat(n, n);
		for(int i = 0; i < n; ++i)
			mat.at(i, i) = 1;
		return mat;
	}

	static Matrix modMul(const Matrix& a, const Matrix& b, const int mod = MOD){
		assert(a.w == b.h);
		Matrix ret(a.h, b.w);
		for(int i = 0; i < a.h; ++i)
			for(int k = 0; k < a.w; ++k)
				for(int j = 0; j < b.w; ++j)
					ret.v[i * b.w + j] = (ret.v[i * b.w + j] + a.v[i * a.w + k] * b.v[k * b.w + j]) % mod;
		return ret;
	}

	i64& at(int i, int j){
		assert(0 <= i && i <= h && 0 <= j && j < w);
		return v[i * h + j];
	};

	Matrix pow(i64 x, const i64 mod = MOD){
		assert(h == w);
		auto mat = x & 1 ? *this : makeUnit(h);
		auto u = *this;
		while(u = modMul(u, u, mod), x >>= 1)
			if(x & 1)
				mat = modMul(mat, u, mod);
		return mat;
	}

	Matrix& operator+=(const Matrix& mat){
		assert(h == mat.h && w == mat.w);
		for(int i = 0; i < h * w; ++i)
			v[i] += mat.v[i];
		return *this;
	}

	Matrix& operator-=(const Matrix& mat){
		assert(h == mat.h && w == mat.w);
		for(int i = 0; i < h * w; ++i)
			v[i] -= mat.v[i];
		return *this;
	}

	Matrix& operator%=(const i64 mod){
		for(int i = 0; i < h * w; ++i)
			v[i] %= mod;
		return *this;
	}

	Matrix operator*(const Matrix& mat){
		assert(w == mat.h);
		Matrix ret(h, mat.w);
		for(int i = 0; i < h; ++i)
			for(int k = 0; k < w; ++k)
				for(int j = 0; j < mat.w; ++j)
					ret.v[i * mat.w + j] += v[i * w + k] * mat.v[k * mat.w + j];
		return ret;
	}

	Matrix operator+(const Matrix& mat){return Matrix(*this) += mat;}
	Matrix operator-(const Matrix& mat){return Matrix(*this) -= mat;}
	Matrix operator%(const i64 mod){return Matrix(*this) %= mod;}
	Matrix& operator*=(const Matrix& mat){return *this = *this * mat;}
};

