struct UnionFind{
    vector<int> par, time;
    int count;
    UnionFind(int n) : par(n, -1), time(n, MOD), count(0){}
    // [0, t]の間に併合されたかどうか
    int Find(int x, int t){return par[x] < 0 || time[x] > t ? x : Find(par[x], t);}
    int Size(int x){return par[x] < 0 ? -par[x] : Size(par[x]);}
    // 現在のcount+1のタイミングで併合された事にする
    // Unite失敗時もcountが増えるので注意
    int Unite(int x, int y){
        x = Find(x, MOD + 1);
        y = Find(y, MOD + 1);
        ++count;
        if(x == y)
            return 0;
        if(par[x] > par[y])
            swap(x, y);
        par[x] += par[y];
        par[y] = x;
        time[y] = count;
        return count;
    }
};

