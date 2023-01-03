// advanced example of lazy propagation
// range arthmetic sequence addition with range sum queries

struct Tree {
    Tree *pl, *pr;
    int nl = 0, nr = 0, val = 0, lazya = 0, lazyk = 0;

    void updateVal() { val = pl->val + pr->val; }
    void propagate() {
        pl->apply(lazya,lazyk), pr->apply(lazya+( nr-nl >> 1 )*lazyk,lazyk), lazya=0, lazyk=0;
    }
    void apply(int a, int k){
        lazya += a,lazyk += k, val += ((2*a+(nr-nl-1)*k)*(nr-nl))/2;

    }

    Tree(int l, int r, int A[]) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        pl = new Tree(nl, nl + nr >> 1, A);
        pr = new Tree(nl + nr >> 1, nr, A);
        updateVal();
    }
    void modify(int l, int r, int a, int k) {
        if (l <= nl && nr <= r) {
            apply(a + (nl-l)*k, k);
            return;
        }
        if (l >= nr || nl >= r)
            return;
        propagate();
        pl->modify(l, r, a, k);
        pr->modify(l, r, a, k);
        updateVal();
    }
    int query(int l, int r) {
        if (l <= nl && r >= nr)
            return val;
        if (l >= nr || nl >= r)
            return 0;
        propagate();
        return pl->query(l, r) + pr->query(l, r);
    }
};


int main(){ sync;

    int a[] = {1,3,5,2,4,6,3};

    Tree *T;
    T = new Tree(0,7,a);

    T -> modify(0,4,3,2);

    for(int i=0;i<7;++i) cout << T->query(i,i+1) << " ";
    return 0;
}
