<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: lib/classes/matrix.cpp
* category: lib/classes


[Back to top page](../../../index.html)



## Code
```cpp
template <typename T>
struct Matrix{
    int h, w;
    vector<T> v;

    Matrix() : h(1), w(1), v(1, 1){}
    Matrix(int n){*this = makeUnit(n);}
    Matrix(int h, int w) : h(h), w(w), v(h * w, 0){}

    Matrix(vector<vector<T>> v_) : h(v_.size()), w(v_[0].size()), v(h * w){
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

    T& at(int i, int j){
        assert(0 <= i && i <= h && 0 <= j && j < w);
        return v[i * h + j];
    };

    Matrix pow(i64 x){
        assert(h == w);
        auto mat = x & 1 ? *this : makeUnit(h);
        auto u = *this;
        while(u = u * u, x >>= 1)
            if(x & 1)
                mat *= u;
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

    Matrix& operator%=(const T mod){
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
    Matrix operator%(const T mod){return Matrix(*this) %= mod;}
    Matrix& operator*=(const Matrix& mat){return *this = *this * mat;}
};


```

[Back to top page](../../../index.html)

