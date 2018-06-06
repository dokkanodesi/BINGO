#include <iostream>
#include <stdio.h>
#include <random>
#include <time.h>
using namespace std;


int GetRandom(int min,int max){
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int Choose(void){
	int n = GetRandom(1,75000000) % 75 + 1;
	//printf("%dです！",n);
	return n;
}

/*int hit(){
	int i,j;
	int status[5][5];
	int num = Choose();
	for(i=0; i>5; i++){
		for(j=0; j>5; j++){
			if(num == status[i][j]){
				status[i][j] = 0;
				goto RoopEscape;//下5行くらいの場所に飛ぶ
			}
		}
	}
	RoopEscape:
	//system("pause");
	return status[i][j];
}*/

/*
int bingo(){
	
}
*/
int main(void){
    int status[5][5] = {};
    int i,j;//iが横、ｊが縦
	int k;
    int duplication[5] = {};
	srand((unsigned int)time(NULL));
	
    for(i=0; i<5; i++){//ビンゴカード作り
        for(j=0; j<5; j++){
			Relottery:
			status[i][j] =  GetRandom(1,1500000) % 15 + i*15 +1;
			
			//被り調査
			duplication[j] = status[i][j];
			for(k=0; k<j; k++){
				if(status[i][j] == duplication[k]){
					goto Relottery;//上5行くらいに飛ぶ
				}
			}
        }
    }
	status[2][2] = 0;//中央が開く
	
	int cnt = 1;
	int num;
	while(cnt==1){//bingoしたら終わりにしたい
		for(i=0; i<5; i++){
			for(j=0; j<5; j++){
				num = Choose();
				if(num == status[i][j]){
					status[i][j] = 0;
				}
				if(j == 0 && i != 0)printf("\n");//改行してカードっぽい表示にする
				if(status[i][j]){//true、つまり番号が開いていない(0)なら
					printf("%d	",status[j][i]);
				}else{
					printf("OPEN	");
				}
			}
		}
		//ビンゴ、リーチ判定
		printf("%dです！",num);
		cnt++;//単体だとテスト用
	}
	return 0;
}
