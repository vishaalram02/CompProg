template<class T, int SZ> struct BIT {
    T bit[SZ];
    T sum(int x) {
        if(x < 0) return 0;
        T ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            ret += bit[i];
        return ret;
    }
    T sum(int x, int y){
        return sum(y)-sum(x-1);
    }
    void add(int x, T delta) {
        for (int i = x; i < SZ; i = i | (i + 1))
            bit[i] += delta;
    }
    void upd(int x, T t){
        T k = sum(x,x);
        add(x, t-k);
    }
};
