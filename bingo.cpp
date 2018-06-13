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
	
	
	int cnt = 0;
	int num;
	int OpenJudge = 0;
	int CallNumber[75];
	
	while(cnt < 5){//bingoしたら終わりにしたい
	Recall:
	num = Choose();
	for(i=0; i<cnt + 1; i++){
		if(num == CallNumber[i]){
			goto Recall;//上4行くらいに飛ぶ
		}
	}
	CallNumber[cnt] = num;
		for(i=0; i<5; i++){//開くかどうか判定
			for(j=0; j<5; j++){
				if(num == status[j][i]){
					status[j][i] = 0;
					OpenJudge++;
				}
				if(j == 0 && i != 0)printf("\n");//改行してカードっぽい表示にする
				if(status[j][i] != 0){//true、つまり番号が開いていない(0じゃない)なら
					printf("%d	",status[j][i]);
				}else{
					printf("OPEN	");
				}
			}
		}
		
		//ビンゴ、リーチ判定
		printf("%dです！",num);
		if(OpenJudge == 1){
			printf("該当する数字がオープンされます！");
			OpenJudge--;
		}
		printf("\n\n");
		cnt++;//単体だとテスト用
	}
	return 0;
}




