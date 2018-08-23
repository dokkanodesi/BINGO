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
	////printf("%d�ł��I",n);
	return n;
}

int bingo(void){
	int status[5][5] = {};
	int i,j;//i�����A�����c
	int k;
	int duplication[5] = {};
	
	for(i=0; i<5; i++){//�r���S�J�[�h���
		for(j=0; j<5; j++){
			Relottery:
			status[i][j] =  GetRandom(1,1500000) % 15 + i*15 +1;
			
			//��蒲��
			duplication[j] = status[i][j];
			for(k=0; k<j; k++){
				if(status[i][j] == duplication[k]){
				goto Relottery;//��5�s���炢�ɔ��
				}
			}
		}
	}
	status[2][2] = 0;//�������J��
	
	
	
	
	int cnt = 0;
	int num;
	int OpenJudge = 0;
	int CallNumber[75];
	
	int yoko[5][5];//�s�A���r���S����
	int tate[5][5];//��A�c�r���S����
	int naname[2][5];
	int yokocnt = 0;
	int tatecnt = 0;
	int nanamecnt = 0;
	int Bingopos = 0;
	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			yoko[i][j]=-1;
			tate[i][j]=-1;
			naname[i][j]=-1;
		}
	}	
	yoko[2][2] = 0;
	tate[2][2] = 0;
	naname[0][2] = 0;//�@�_����
	naname[1][2] = 0;//�@�^����
	
	
	while(cnt < 75){//bingo������cnt��9999�ɂȂ�
		Recall://��4�s���炢�ɂ���
		num = Choose();
		for(i=0; i<cnt + 1; i++){
			if(num == CallNumber[i]){
				goto Recall;//��4�s���炢�ɔ��
			}
		}
		CallNumber[cnt] = num;
		for(i=0; i<5; i++){//�J�[�h�̐������J�����ǂ�������A�J������0�ɂ���
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
				if(j == 0 && i != 0)//printf("\n");//���s���ăJ�[�h���ۂ��\���ɂ���
				if(status[j][i] != 0){//�ԍ����J���Ă��Ȃ��Ȃ�
					//printf("%d	",status[j][i]);
				}else{//�J���Ă���Ȃ�
					//printf("OPEN	");
				}
			}
		}
		//�r���S�A���[�`����
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
				//printf("%d��߂̉��r���S�ł��I",i+1);
				Bingopos = i+1;//1~5
				goto goodbingo;//���d���[�v����
			}
			if(tatecnt==5){
				//printf("%d��߂̏c�r���S�ł��I",i+1);
				if(i==2){
					Bingopos = 8;
				}else{
					Bingopos = i+6;//6,7,9,10
				}
				goto goodbingo;
			}
			if(nanamecnt==5){
				//printf("%d��߂̂ȂȂ߃r���S�ł��I",i+1);
				Bingopos = i+11;//11,12
				goto goodbingo;
			}
			yokocnt=0;
			tatecnt=0;
			nanamecnt=0;
			//printf("test��؂�");
		}
		goodbingo:
		if(Bingopos > 0){
			//printf("�r���S����");
			cnt = 9999;
		}
		//printf("%d�ł��I",num);
		if(OpenJudge == 1){
			//printf("�Y�����鐔�����I�[�v������܂��I");
			OpenJudge--;
		}
		//printf("\n\n");
		cnt++;//�P�̂��ƃe�X�g�p
	}
	return Bingopos;
	
}

int main(void){
	srand((unsigned int)time(NULL));
	int i,j;
	int bingocnt[13];
	int n;
	printf("�r���S���ʂ�����o���H");
	scanf("%d",&n);
	for(i=1; i<13; i++){//������
		bingocnt[i] = 0;
	}
	for(i=0; i<n; i++){//i<n��n��r���S���ʂ����Ă��邼
		int BingoType = bingo();
		printf("%d\n",BingoType);
		bingocnt[BingoType]++;
	}
	for(i=1; i<13; i++){
		printf("%d ",bingocnt[i]);
	}//���̕Ӄ_�T����.
}

