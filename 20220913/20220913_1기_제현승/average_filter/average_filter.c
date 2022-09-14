#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_DATA 50 //n_samples 확인시 50나옴

#define STD_DEV 4.0
#define MEAN 0	




double get_volt()
{
	double v = 0.0;
	double volt_mean = 14.4;
	double volt_meas = 0.0;
	
	v = (rand()%201-100)/10; //-10.0~10.0, 원래 파이썬도 하나의 값 나옴
	
	volt_meas = volt_mean + v;
	//printf("1. %lf",volt_meas);
	return volt_meas;  
}


double avg_filter(int k, double x_meas , double x_avg)
{
	double alpha = 0.0;
	alpha = ((double)(k - 1)) / k;
    x_avg = alpha * x_avg + (1 - alpha) * x_meas;
	//printf(" 2. %lf\n",x_avg);
	//printf(" 3. %lf 4.%d \n",alpha, k); //alpha 값이 실수 형태로 K값으로 계산되어야함
	return x_avg;  
}


int main()
{
	srand(time(NULL));
	
	double x_meas_save[N_DATA]=	{0.0,}; //zero 0으로 초기화
	double x_avg_save[N_DATA]={0.0,};//zero 0으로 초기
	
	double x_meas=0.0;
	double x_avg=0.0;
	int k=0;
	
	for(int i=0; i<N_DATA;i++)
	{
		k = i+1;
		x_meas = get_volt();
		x_avg = avg_filter(k,x_meas,x_avg);
		
		x_meas_save[i] = x_meas;
		x_avg_save[i] = x_avg;
		
		printf("%d. x_meas_save[%d]= %lf, x_avg_save[%d]= %lf \n", i+1,i,x_meas_save[i],i,x_avg_save[i]); 
	}
} 
