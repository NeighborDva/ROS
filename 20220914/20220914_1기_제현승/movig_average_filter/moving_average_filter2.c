#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_DATA 50 //n_samples 확인시 50나옴


typedef struct mov_avg_filter
{
	double x_n[N_DATA]; 
	double x_avg; 
}mov_avg_filt;


double get_sonar()
{
	double sonar_meas = 0.0;
	sonar_meas = (rand()%1000+1)/100; //0.01~10.0, 원래코드에서도 배열로 입력되어있는 Sonar 데이터를 하나씩 받아옴 
	
	//printf("1. %lf",sonar_meas);
	return sonar_meas;  
}



mov_avg_filt moving_avg_filter2(mov_avg_filt result, double x_meas)
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
	
	double x_meas_save[N_DATA]={0.0,}; //zero 0으로 초기화
	double x_avg_save[N_DATA]={0.0,};//zero 0으로 초기화
	
	double x_meas=0.0;
	mov_avg_filt result;
	
	for(int i=0; i<N_DATA;i++)//ones 1로 초기화
	{
		result.x_n[i] = 0.0;
	}
	//	result.x_n[N_DATA]={1.0,}; //이방식으로 하니  error: expected expression before ‘{’ token 에러 발생
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
