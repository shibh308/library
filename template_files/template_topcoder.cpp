#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC target("tune=native")
#pragma GCC target("avx")
// #pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")

using namespace std;

using i64 = int64_t;

const i64 MOD = 1e9+7;

const i64 INF = 1e18+7;

template <typename T = i64>
struct Range{
    struct iterator{
        T value;
        const T step, last;
        const T& operator*(){return value;}
        iterator(T value, T step, T last) :
            value(step < static_cast<T>(0) ? max(last, value) : min(last, value)),
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

template <typename T = i64>
bool chmax(T& a, T b){
    if(a < b){
        a = b;
        return true;
    }
    return false;
}

template <typename T = i64>
bool chmin(T& a, T b){
    if(a > b){
        a = b;
        return true;
    }
    return false;
}

#define dump(x) fprintf(stderr, "line =%4d, name =%7s , ", __LINE__, #x); clog << "value = " << x << endl;

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

void input(){}

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


#define __class CheatingQuiz
#define __func howMany

class __class{
public:
    vector<int> __func(string s){
        int n = s.size();
        vector<int> ret(n, 0);
        vector<int> v = {static_cast<int>(count(s.begin(), s.end(), 'A')), static_cast<int>(count(s.begin(), s.end(), 'B')), static_cast<int>(count(s.begin(), s.end(), 'C'))};
        for(const auto& i : Range<>(n)){
            int c = s[i] - 'A';
            for(const auto& j : Range<>(3))
                ret[i] += bool(v[j]);
            --v[c];
        }
        return ret;
    }

    template<typename... Args>
    auto operator()(Args... args) -> decltype(__func(forward<Args>(args)...)){
        return __func(forward<Args>(args)...);
    }
};

template <typename Class>
struct OutputChecker{
    Class c;
    int x;
    OutputChecker() : c(), x(0){}
    template<typename Answer, typename... Args>
    void operator()(Answer correct, Args... args){
        clog << "Case " << x++ << ": ";

        Answer ret = c(forward<Args>(args)...);
        clog << (ret == correct ? "Yes" : "No") << endl;
    }
};

signed main(){

    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    OutputChecker<__class> c;
    c(vector<int>{1, 1, 1, 1, 1}, "AAAAA");
    c(vector<int>{2, 2, 2, 1, 1, 1}, "AAABBB");
}

