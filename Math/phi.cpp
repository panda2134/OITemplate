int64 GetPhi(int64 x) { // 单个数的Phi
	int64 ret = x;
	for(int i = 2; i <= x; i++) if(x % i == 0) {
		ret = ret / i * (i-1);
		while(x % i == 0) x /= i;
	}
	if(x > 1)
		ret = ret / x * (x-1);
	return ret;
}

int PrimeCnt, Phi[MAXNUM+10], PrimeLst[MAXNUM+10], NotPrime[MAXNUM+10];
void PhiSieve() { // 线性筛Phi
	NotPrime[1] = true;
	Phi[1] = 1;
	for(int i = 2; i <= MAXNUM; i++) {
		if(!NotPrime[i]) {
			PrimeLst[++PrimeCnt] = i;
			Phi[i] = i-1;
		}
		for(int j = 1; j <= PrimeCnt; j++) {
			if(i * PrimeLst[j] > MAXNUM) break;
			NotPrime[i * PrimeLst[j]] = true;
			if(i % PrimeLst[j] == 0) {
				Phi[i * PrimeLst[j]] = Phi[i]  * PrimeLst[j];
				break;
			} else
				Phi[i * PrimeLst[j]] = Phi[i] * Phi[PrimeLst[j]];
		}
	}
}