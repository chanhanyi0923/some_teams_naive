#include<bits/stdc++.h>
using namespace std;

stack<int> S;

void kep(){
    //printf("nowsize = %d\n",S.size());
    //stack<int>S2;//printf("Stack:\n");
    /*while(!S.empty()){
        printf("%d\n",S.top());
        S2.push(S.top());
        S.pop();
    }
    while(!S2.empty()){
        S.push(S2.top());
        S2.pop();
    }*/
    while(S.size()>1){
        int t1=S.top();
        S.pop();
        int t2=S.top();
        S.pop();
        if(t1==t2)S.push(t1<<1);
        else{//printf("%d  !=  %d\n",t1,t2);
            S.push(t2);
            S.push(t1);
            return;
        }
    }
    /*printf("Stack:\n");
    while(!S.empty()){
        printf("%d\n",S.top());
        S2.push(S.top());
        S.pop();
    }
    while(!S2.empty()){
        S.push(S2.top());
        S2.pop();
    }*/
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        while(!S.empty())S.pop();
        char s[500];
        scanf("%s",s);
        int l=strlen(s);
        for(int i=0;i<l;i++){
            while(!S.empty() && s[i]-'0'>S.top()){
                int t=S.top();
                printf("%d",t);
                S.push(t);
                kep();
            }
            printf("%d",s[i]-'0');
            S.push(s[i]-'0');
            kep();
        }//printf("size = %d\n",S.size());
        //system("pause");
        int sum=0;
        while(S.size()>1){
            int t=S.top();
            if(t<8){
                printf("%d",t);
                S.push(t);
                kep();
                continue;
            }
            S.pop();//printf("------------\n");
            for(int i=0;i*8<t;i++)printf("8");
            S.push(t<<1);
            kep();
        }
        puts("");
    }
    return 0;
}