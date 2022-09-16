#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_DATA 50 //n_samples 기존은 500으로 지정했지만 결과 캡처를 위해 50지정

double alpha=0.7;

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

double low_pass_filter(double x_meas, double x_esti)
{
	x_esti = alpha * x_esti + (1-alpha)* x_meas;
	
	return x_esti;
}
int main()
{
	srand(time(NULL));
	
	double x_meas_save[N_DATA]={0.0,}; //zero 0으로 초기화
	double x_esti_save[N_DATA]={0.0,};//zero 0으로 초기화
	
	double x_meas=0.0;
	double x_esti=0.0;
	
	for(int i=0; i<N_DATA;i++)
	{
		//k = i+1;
		x_meas = get_sonar();
		if(i == 0)
		{
			x_esti = x_meas;
		}
		else
		{
			x_esti = low_pass_filter(x_meas, x_esti);
		}
			
		x_meas_save[i] = x_meas;
		x_esti_save[i] = x_esti;
		printf("%d. x_meas_save[%d]= %lf, x_esti_save[%d]= %lf \n", i+1,i,x_meas_save[i],i,x_esti_save[i]); 
	}
	return 0;
} 
