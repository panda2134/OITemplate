bool Gauss(int n, double A[MAXN + 10][MAXN + 10]) {
    for(int i = 1; i <= n; i++) {
        int k = i;
        for(int j = n; j >= i; j--)
            if(dcmp(A[j][i]) != 0) k = j;
        
        if(k != i)
            for(int j = 1; j <= n; j++) swap(A[i][j], A[k][j]);
        
        if(dcmp(A[i][i]) == 0) return false; // no solution
        for(int j = i+1; j <= n; j++) {
            double t = A[j][i] / A[i][i];
            for(int k = 1; k <= n; k++)
                A[j][k] -= t * A[i][k];
        }
    }
    return true;
}