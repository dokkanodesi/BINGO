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
	////printf("%dです！",n);
	return n;
}

int bingo(void){
	int status[5][5] = {};
	int i,j;//iが横、ｊが縦
	int k;
	int duplication[5] = {};
	
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
	
	int yoko[5][5];//行、横ビンゴ判定
	int tate[5][5];//列、縦ビンゴ判定
	int naname[2][5];
	int yokocnt = 0;
	int tatecnt = 0;
	int nanamecnt = 0;
	int Bingo_yokocnt = 0;
	int Bingo_tatecnt = 0;
	int Bingo_Centtatecnt = 0;
	int Bingo_nanamecnt = 0;
	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			yoko[i][j]=-1;
			tate[i][j]=-1;
			naname[i][j]=-1;
		}
	}	
	yoko[2][2] = 0;
	tate[2][2] = 0;
	naname[0][2] = 0;//　＼方向
	naname[1][2] = 0;//　／方向
	
	
	while(cnt < 75){//bingoしたらcntが9999になる
		Recall://下4行くらいにある
		num = Choose();
		for(i=0; i<cnt + 1; i++){
			if(num == CallNumber[i]){
				goto Recall;//上4行くらいに飛ぶ
			}
		}
		CallNumber[cnt] = num;
		for(i=0; i<5; i++){//カードの数字が開くかどうか判定、開いたら0にする
			for(j=0; j<5; j++){
				if(num == status[j][i]){
					status[j][i] = 0;
					OpenJudge++;
					yoko[i][j] = 0;
					tate[j][i] = 0;
					if(i == j){
						naname[0][i] = 0;
					}
					if(i + j == 4){
						naname[1][i] = 0;
					}
				}
				if(j == 0 && i != 0)//printf("\n");//改行してカードっぽい表示にする
				if(status[j][i] != 0){//番号が開いていないなら
					//printf("%d	",status[j][i]);
				}else{//開いているなら
					//printf("OPEN	");
				}
			}
		}
		//ビンゴ、リーチ判定
		for(i=0; i<5; i++){
			for(j=0; j<5; j++){
				if(yoko[i][j] == 0){
					yokocnt++;
				}
				if(tate[i][j] == 0){
					tatecnt++;
				}
				if(i<2 && naname[i][j] == 0){
					nanamecnt++;
				}
				//printf("\n%d%d%d",yokocnt, tatecnt, nanamecnt);
				
			}
			
			if(yokocnt==5){
				//printf("%d列めの横ビンゴです！",i+1);
				Bingo_yokocnt = 0;
				goto goodbingo;//多重ループ抜け
			}
			if(tatecnt==5){
				//printf("%d列めの縦ビンゴです！",i+1);
				if(i==2){
					Bingo_Centtatecnt = 1;
				}else{
					Bingo_tatecnt = 2;
				}
				goto goodbingo;
			}
			if(nanamecnt==5){
				//printf("%d列めのななめビンゴです！",i+1);
				Bingo_nanamecnt = 3;
				goto goodbingo;
			}
			yokocnt=0;
			tatecnt=0;
			nanamecnt=0;
			//printf("test区切り");
		}
		goodbingo:
		//printf("%d%d%d%d\n",Bingo_yokocnt, Bingo_tatecnt, Bingo_Centtatecnt, Bingo_nanamecnt);
		if(Bingo_yokocnt==0 || Bingo_Centtatecnt==1 || Bingo_tatecnt==2 || Bingo_nanamecnt==3){
			//printf("ビンゴだよ");
			cnt = 9999;
		}
		//printf("%dです！",num);
		if(OpenJudge == 1){
			//printf("該当する数字がオープンされます！");
			OpenJudge--;
		}
		//printf("\n\n");
		cnt++;//単体だとテスト用
	}
	if(Bingo_yokocnt == 0){
		return Bingo_yokocnt;
	}else if(Bingo_Centtatecnt == 1){
		return Bingo_Centtatecnt;
	}else if(Bingo_tatecnt == 2){
		return Bingo_tatecnt;
	}else if(Bingo_nanamecnt == 3){
		return Bingo_nanamecnt;
	}
}

int main(void){
	srand((unsigned int)time(NULL));
	int i,j;
	int bingocnt[4];
	printf("aaa");
	for(j=0; j<4; j++){//初期化
		bingocnt[i] = 0;
	}
	for(i=0; i<10; i++){//i<nのn回ビンゴ結果もってくるぞ
		int BingoType = bingo();
		bingocnt[BingoType]++;
	}
	for(i=0; i<4; i++){
		printf("%d",bingocnt[i]);
	}//この辺ダサすぎ
}

