#include <bits/stdc++.h>
const int MAXN = 1000000;

int fail[MAXN+5];

void KMP(char* a,char* b){
    int na = strlen(a+1),nb = strlen(b+1); //注意+1 
    //Init
    fail[1] = 0;//! static在每次进入函数时保留上次修改的值 
    for(int i = 2; i <= nb; i++){
        int j = fail[i-1];//尝试扩展已经匹配部分 
        //无法匹配则缩短前后缀 
        while(j != 0 && b[j+1] != b[i]) j = fail[j];
        //用已经匹配部分更新fail数组 
        if(b[j+1] == b[i]) fail[i] = j+1;// !!
        //无法匹配前后缀 
        else fail[i] = 0; 
    }
    //Match
    for(int i = 1,j = 0; i <= na; i++){
        //缩短前后缀 
        while(j != 0 && b[j+1] != a[i]) j = fail[j];
        if(b[j+1] == a[i]) j++; //成功匹配 
        if(j == nb){
            printf("%d\n", i - nb + 1);
            j = fail[j];
            //j = 0; //如果两个匹配部分不可重叠 
        }
    }
}

int main() {
    char a[MAXN+5], b[MAXN+5];
    scanf("%s", a+1);
    scanf("%s", b+1);
    KMP(a, b); int t = strlen(b+1);
    for(int i = 1; i <= t; i++)
        printf("%d ", fail[i]);
    return 0;
}
