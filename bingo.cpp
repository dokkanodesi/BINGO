#include <iostream>
#include <stdio.h>
#include <random>
#include <time.h>
using namespace std;


int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int ChooseCheck(void){
	int n = GetRandom(1,75000000) % 15 + 1;
	int i,j;
	int status[5][5];
	for(i=0; i>5; i++){
		for(j=0; j>5; j++){
			if(status[i][j] == n){
				status[i][j] = 0;
			}
		}
	}
	return 0;
}

int main(void){
    int status[5][5] = {};
    int i,j;//iが横、jが縦
	int k;
    int duplication[5] = {};
	srand((unsigned int)time(NULL));
	
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
			Relottery:
			
			status[i][j] =  GetRandom(1,1500000) % 15 + i*15 +1;
			duplication[j] = status[i][j];
			//かぶったらだめ
			//被り調査
			for(k=0; k<j; k++){
				if(status[i][j] == duplication[k]){
					goto Relottery;
				}
			}
        }
    }
	status[2][2] = 0;
	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			if(j == 0 && i != 0)printf("\n");
			if(status[i][j]){//true、つまり開いてないなら
				printf("%d	",status[j][i]);
			}else{
				printf("OPEN");
			}
		}
	}
	return 0;
}
