int primecnt, primelst[MAXN+10], notprime[MAXN+10], sigma[MAXN+10], smin[MAXN+10];

void euler_sieve() {
    notprime[1] = true;
    smin[1] = sigma[1] = 1;
    for(int i = 2; i <= MAXN; i++) {
        if(!notprime[i]) {
            primelst[++primecnt] = i;
            smin[i] = sigma[i] = i+1;
        }
        for(int j = 1; j <= primecnt; j++) {
            if(i * primelst[j] > MAXN) break;
            notprime[i * primelst[j]] = true;
            if(i % primelst[j] == 0) {
                smin[i * primelst[j]] = smin[i] * primelst[j] + 1;
                sigma[i * primelst[j]] = sigma[i] / smin[i] * smin[i * primelst[j]];
                break;
            } else  {
                smin[i * primelst[j]] = smin[primelst[j]];
                sigma[i * primelst[j]] = sigma[i] * smin[i * primelst[j]];
            }
        }
    }
}
