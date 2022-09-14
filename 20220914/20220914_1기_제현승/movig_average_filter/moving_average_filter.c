#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_DATA 50 //n_samples 기존은 500으로 지정했지만 결과 캡처를 위해 50지정


typedef struct mov_avg_filter
{
	double x_n[N_DATA]; 
	double x_avg; 
}mov_avg_filt;


double get_sonar()
{
	double sonar_meas = 0.0;
	sonar_meas = ((double)(rand()%1000+1))/100; //0.01~10.0, 원래코드에서도 배열로 입력되어있는 Sonar 데이터를 하나씩 받아옴 
	// 또한 초음파 거리값은 0이 나올 확률은 없기때문에 double형으로 치환--> 안하면 0값이 나옴, / 연산이 정수 / 정수 가되다보니 소수점아래는 다른 부분에는 적용이 안됨
	
	//printf("1. %lf",sonar_meas);
	return sonar_meas;  
}


mov_avg_filt moving_avg_filter(mov_avg_filt result, double x_meas) //github-파이썬
{
	double mean=0.0;
	double sum=0.0;
	
	for(int i =0 ;i < N_DATA-1;i++)
	{
		result.x_n[i] = result.x_n[i+1];
	}
	
	for(int i =0 ;i < N_DATA;i++)
	{
		sum += result.x_n[i];
	}
	mean = sum / N_DATA ;
	
	result.x_n[N_DATA-1] = x_meas;
	result.x_avg = mean;
	
	return result;  
}

mov_avg_filt moving_avg_filter2(mov_avg_filt result, double x_meas)// 링크-게시글
{
	double front = 0.0;
	double mean=0.0;
	double sum=0.0;
	
	front = result.x_n[0];
	for(int i =0 ;i < N_DATA-1;i++)
	{
		result.x_n[i] = result.x_n[i+1];
	}
	
	result.x_n[N_DATA-1] = x_meas;
	result.x_avg =result.x_avg + (x_meas-front)/N_DATA;
	
	return result;  
}

int main()
{
	srand(time(NULL));
	
	int mode;
	double x_meas_save[N_DATA]={0.0,}; //zero 0으로 초기화
	double x_avg_save[N_DATA]={0.0,};//zero 0으로 초기화
	
	double x_meas=0.0;
	mov_avg_filt result;
	
	
	
	printf("movig filter 함수 선택-1.git hub 2.게시글 \n");
	printf("선택: ");
	scanf("%d", &mode);
	
	if(mode == 1) //파이썬 변환
	{
		for(int i=0; i<N_DATA;i++)//ones 1로 초기화
	{
		result.x_n[i] = 1.0;
	}
	//	result.x_n[N_DATA]={1.0,}; //이방식으로 하니  error: expected expression before ‘{’ token 에러 발생
	result.x_avg = 0.0;
	for(int i=0; i<N_DATA;i++)
	{
		//k = i+1;
		x_meas = get_sonar();
		if(i==0)
		{
			result.x_avg=x_meas;
			for(int i=0; i<N_DATA;i++)
			{
				result.x_n[i] = x_meas * result.x_n[i];
			}
		}
		else
			{
				result =moving_avg_filter(result,x_meas);
			}
			
		x_meas_save[i] = x_meas;
		x_avg_save[i] = result.x_avg;
		printf("%d. x_meas_save[%d]= %lf, x_avg_save[%d]= %lf \n", i+1,i,x_meas_save[i],i,x_avg_save[i]); 
	}
	}
	else if(mode == 2)//링크 게시글참조
	{
		for(int i=0; i<N_DATA;i++)//ones 0으로 초기화
	{
		result.x_n[i] = 0.0;
	}
	//	result.x_n[N_DATA]={0.0,}; //이방식으로 하니  error: expected expression before ‘{’ token 에러 발생
	result.x_avg = 0.0;
	for(int i=0; i<N_DATA;i++)
	{
		x_meas = get_sonar();
		result = moving_avg_filter2(result,x_meas);
		
		x_meas_save[i] = x_meas;
		x_avg_save[i] = result.x_avg;
		
		printf("%d. x_meas_save[%d]= %lf, x_avg_save[%d]= %lf \n", i+1,i,x_meas_save[i],i,x_avg_save[i]); 
	}	
	}
	else
		printf("잘못된 모드를 선택하셨습니다.\n");
	
	return 0;
} 
