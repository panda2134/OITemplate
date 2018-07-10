int PrimeCnt, PrimeLst[MAXNUM+10], NotPrime[MAXNUM+10], Mu[MAXNUM+10];

void MuSieve() {
	NotPrime[1] = true;
	Mu[1] = 1;
	for(int i = 2; i <= MAXNUM; i++) {
		if(!NotPrime[i]) {
			PrimeLst[++PrimeCnt] = i;
			Mu[i] = -1;
		}
		for(int j = 1; j <= PrimeCnt; j++) {
			if(i * PrimeLst[j] > MAXNUM) break;
			NotPrime[i * PrimeLst[j]] = true;
			if(i % PrimeLst[j] == 0) {
				Mu[i * PrimeLst[j]] = 0;
				break;
			} else
				Mu[i * PrimeLst[j]] = -Mu[i];
		}
	}
}