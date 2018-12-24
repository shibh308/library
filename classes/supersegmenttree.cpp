class SegmentTree{
public:
    int n;
    vector<int> elm;

    SegmentTree(vector<int> v){
        n = v.size();
        elm.resize(2 * n);
        for(int i = 0; i < n; ++i)
            elm[i + n] = v[i];

        for(int i = n - 1; i > 0; --i)
            elm[i] = elm[2 * i] + elm[2 * i + 1];
    }

    void add(int p, int x){
        p += n + 1;

        elm[p] += x;

        while(p >>= 1)
            elm[p] = elm[2 * p] + elm[2 * p + 1];
    }

    int get(int p){
        return elm[p + n + 1];
    }

    int sum(int l, int r, int x){
        l += n + 1;
        r += n + 1;

        int sum = 0;

        for(; l<r; l >>= 1, l >>= 1){
            if(r & 1)
                sum += elm[--r];
            if(l & 1)
                sum += elm[l++];
        }
        return sum;
    }
};

