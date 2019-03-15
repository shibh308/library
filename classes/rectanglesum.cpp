struct RectangleSum{//O(HW)で初期化してO(1)で長方形の和を出す(半開区間)
    vector<vector<i64>> sum;
    int h, w;
    RectangleSum(vector<vector<i64>>& v) :
        h(v.size()),
        w(v[0].size()),
        sum(v)
    {}

    // 半開区間で設定する事に注意する
    void set(int sx, int sy, int ex, int ey, i64 val){
        sum[sx][sy] += val;
        sum[sx][ey] -= val;
        sum[ex][sy] -= val;
        sum[ex][ey] += val;
    }

    void run(){

        for(int i = 0; i < h + 1; ++i)
            for(int j = 0; j < w; ++j)
                sum[i][j + 1] += sum[i][j];

        for(int j = 0; j < w + 1; ++j)
            for(int i = 0; i < h; ++i)
                sum[i + 1][j] += sum[i][j];
    }

    i64 getSum(int sx, int sy, int ex, int ey){
        return sum[ex][ey] + sum[sx][sy] - sum[sx][ey] - sum[ex][sy];
    }
};


