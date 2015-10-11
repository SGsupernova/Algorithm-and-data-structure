void * medianof3(void *lo, void *mid, void *hi, _Cmpfun *cmp) {
	return cmp(lo, mid) < 0 ?
		cmp(mid, hi) < 0 ? mid :
		cmp(lo, hi) < 0 ? hi : lo :
		cmp(lo, hi) < 0 ? lo :
		cmp(mid, hi) < 0 ? hi : mid;
}
