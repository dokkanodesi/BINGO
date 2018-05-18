#include <iostream>
#include <stdio.h>
#include <random>
using namespace std;
int main(void){
    int status[5][5] = {};
    int i,j;//iが横、jが縦
	int k;
    int duplication[5] = {};

    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
			Relottery:
			
			status[i][j] = rand() % 15 + i*15 +1;
			duplication[j] = status[i][j];
			//かぶったらだめ
			//被り調査
			for(k=0; k<j; k++){
				if(status[i][j] == duplication[k]){
					goto Relottery;
				}
			}
			printf("%d\n",status[i][j]);
        }
    }
}
