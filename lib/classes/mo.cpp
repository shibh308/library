struct Mo{
    int l, r;
    function<void(int)> left_add, left_erase, right_add, right_erase;
    Mo(function<void(int)> left_add, function<void(int)> left_erase,
       function<void(int)> right_add, function<void(int)> right_erase,
       int sl = 0, int sr = 0) :
       l(sl), r(sr), left_add(left_add), left_erase(left_erase), right_add(right_add), right_erase(right_erase){}
    void move(int next_l, int next_r){
        for(int i = l; i < next_l; ++i)
            left_erase(i);
        for(int i = l - 1; i >= next_l; --i)
            left_add(i);
        for(int i = r; i < next_r; ++i)
            right_add(i);
        for(int i = r - 1; i >= next_r; --i)
            right_erase(i);
        l = next_l, r = next_r;
    }
};

