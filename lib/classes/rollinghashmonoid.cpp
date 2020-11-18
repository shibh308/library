struct RollingHashMonoid{
    using Hash = RollingHashMonoid;
    using u64 = uint64_t;
    static constexpr u64 mod = (1uLL << 61) - 1;
    static constexpr u64 m30 = (1uLL << 30) - 1;
    static constexpr u64 m31 = (1uLL << 31) - 1;
    static constexpr u64 m61 = mod;
    static constexpr u64 _base = 550390130435464343;
    static constexpr u64 _base_inv = 1803816245541264939;
    static vector<u64> base, base_inv;

    static inline u64 calc_mod(u64 x){
        u64 xu = x >> 61;
        u64 xd = x & m61;
        u64 res = xu + xd;
        if(res >= mod)
            res -= mod;
        return res;
    }

    static inline u64 raw_mul(u64 a, u64 b){
        u64 au = a >> 31;
        u64 ad = a & m31;
        u64 bu = b >> 31;
        u64 bd = b & m31;
        u64 mid = ad * bu + au * bd;
        u64 midu = mid >> 30;
        u64 midd = mid & m30;
        return au * bu * 2 + midu + (midd << 31) + ad * bd;
    }

    static void remake_table(int len){
        while(base.size() <= len){
            base.emplace_back(calc_mod(raw_mul(base.back(), _base)));
            base_inv.emplace_back(calc_mod(raw_mul(base_inv.back(), _base_inv)));
        }
    }

    u64 h, l;

    static inline u64 lshift(u64 a, int len){
        remake_table(len);
        return raw_mul(a, base[len]);
    }
    static inline u64 rshift(u64 a, int len){
        remake_table(len);
        return raw_mul(a, base_inv[len]);
    }

    Hash concat(const Hash& b) const{
        return RollingHashMonoid(
                calc_mod(h + lshift(b.h, l)),
                l + b.l
                );
    }
    Hash sub(const Hash& b) const{
        return RollingHashMonoid(
                calc_mod(rshift(h + mod - b.h, b.l)),
                l - b.l
                );
    }

    RollingHashMonoid() : h(0), l(0){}
    RollingHashMonoid(u64 x) : h(x), l(1){}
    RollingHashMonoid(u64 h, u64 l) : h(h), l(l){}

    friend bool operator==(const Hash& a, const Hash& b){return a.h == b.h && a.l == b.l;}

    template <typename T>
    static vector<Hash> make(vector<T>& x){
        vector<Hash> v(x.size() + 1);
        for(int i = 0; i < x.size(); ++i){
            v[i + 1] = v[i].concat(x[i]);
        }
        return v;
    }
    static vector<Hash> make(string& x){
        vector<Hash> v(x.size() + 1);
        for(int i = 0; i < x.size(); ++i){
            v[i + 1] = v[i].concat(x[i]);
        }
        return v;
    }
};

namespace std{
template<> struct hash<RollingHashMonoid>{
size_t operator()(const RollingHashMonoid x) const noexcept{
    return x.concat(x.l).h;
}
};
}


using Hash = RollingHashMonoid;
vector<uint64_t> Hash::base = {1};
vector<uint64_t> Hash::base_inv = {1};
