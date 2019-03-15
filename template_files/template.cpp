#include <bits/stdc++.h>

using namespace std;

using i64 = int64_t;

const i64 MOD = 1e9+7;

const i64 INF = 1e18+7;

// pythonのrangeのような範囲for文用のclass for(const auto& i : Range<>(10)) のように書く
template <typename T = i64>
struct Range{
    struct iterator{
        T value;
        const T step, last;
        const T& operator*(){return value;}
        iterator(T value, T step, T last) :
            value(value),
            step(step),
            last(last)
        {
        }
        iterator operator++(){value = step < static_cast<T>(0) ? max(value + step, last) : min(value + step, last); return *this;}
        bool operator!=(const iterator& x){return value != x.value;}
    };
    const T start, last, step;

    Range(const T start, const T last, const T step = static_cast<T>(1)) :
        start(start),
        last(last),
        step(step)
    {
    }

    Range(const T last) :
        start(0),
        last(last),
        step(1)
    {
    }

    iterator begin(){return iterator(start, step, last);}
    iterator end(){return iterator(last, step, last);}
};

// lambda式を用いた再帰
template <typename F>
struct FixPoint{
    const F _f;
    FixPoint(F&& f) : _f(forward<F>(f)){}

    template<typename... Types>
    decltype(auto) operator()(Types&&... args) const{
        return _f(*this, forward<Types>(args)...);
    }
};

template <typename F>
static decltype(auto) makeRec(F&& f){
    return FixPoint<F>(forward<F>(f));
}

// 多次元vectorの一斉初期化 makeVector<i64, 0>(a, b, ...)のように書く
template <typename T, T Value = T()>
vector<T> makeVector(size_t x){
    return vector<T>(x, T(Value));
}

template <typename T, T Value = T(), typename... Types>
auto makeVector(size_t x, Types... args){
    return vector<decltype(makeVector<T, Value>(args...))>(x, makeVector<T, Value>(args...));
}

// 最大値を更新し、更新できた時にはtrueを返す
template <typename T = i64>
bool chmax(T& a, T b){
    if(a < b){
        a = b;
        return true;
    }
    return false;
}

// 同様に最小値を更新する
template <typename T = i64>
bool chmin(T& a, T b){
    if(a > b){
        a = b;
        return true;
    }
    return false;
}

// 行数と変数名、値をclogに表示するデバッグ用print
#define dump(x) fprintf(stderr, "line =%4d, name =%7s , ", __LINE__, #x); clog << "value = " << x << endl;

// 同様の配列向けデバッグ用print
#define vecdump(x) fprintf(stderr, "line =%4d, name =%7s\n", __LINE__, #x); _dump_macro(x);

void _dump(int, string& x){
    clog << x << endl;
}

template <typename T>
void _dump(bool, T& x){
    clog << x << " ";
}

template <typename T, typename U = typename T::iterator>
void _dump(int, T& x){

    for(auto& elm : x)
        _dump(0, elm);

    clog << endl;
}

template <typename T>
void _dump_macro(T& x){
    _dump(0, x);
}

// input用の関数群
void _input(int, string& x){
    cin >> x;
}

template <typename T>
void _input(bool, T& x){
    cin >> x;
}

template <typename T, typename U = typename T::iterator>
void _input(int, T& x){

    for(auto& elm : x)
        _input(0, elm);
}

template <typename T>
void input_single(T& x){
    _input(0, x);
}

auto input(){}

template <typename T, typename... Types>
void input(T& value, Types&&... args){
    input_single(value);
    input(forward<Types>(args)...);
};

void _pararell_input(size_t){}

template <typename T, typename... Types>
void _pararell_input(size_t index, T& value, Types&&... args){
    input(value[index]);
    _pararell_input(index, forward<Types>(args)...);
}

template <typename... Types>
void pararell_input(size_t count, Types&&... args){
    for(const auto& i : Range<>(count))
        _pararell_input(i, forward<Types>(args)...);
}


signed main(){

    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

	// code template (2019/03/15)

}

