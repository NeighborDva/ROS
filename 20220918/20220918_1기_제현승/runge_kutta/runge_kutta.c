#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
    x0 : 초기 위치
    v0 : 초기 속도
    t0 : 초기 시각
    t1 : 최종 시각
    N : t0-t1 구간을 N 조각으로 불연속화
*/
#define N 160
double x_0 = 0.0; //위치
double v_0 = 1.0;// 속도
int t_0 = 0; //시간 
int t_1 = 0;
 
double B = 0.0; 
double M = 0.0; 
double K = 0.0; 

typedef struct runge_kutta
{
	double vel[N]; 
	double pos[N]; 
	int time[N];
}runge_kutta;

void init_data()
{
	printf("spring_mass_damper_model 상수 입력\n");
	printf("damper 상수 B: ");
	scanf("%lf",&B);
	printf("spring 상수 K: ");
	scanf("%lf",&K);
	printf("mass M: ");
	scanf("%lf",&M);
	
	printf("입력된 spring_mass_damper_model 상수 B:%lf K:%lf M:%lf \n", B, K, M);
	printf("B/M = %lf K/M = %lf \n", B/M , K/M);
}



double spring_mass_damper_model(int time, double pos, double vel)
{
	double res;
	res = -(B*vel/M)-(K*pos/M);
	//printf("%lf \n",res);
	return res;
}

//룽게-쿠타 함수
runge_kutta rungekutta_method(runge_kutta result)
{	

	double h =0;
	
	double kx1,kx2,kx3,kx4; // 룽게 쿤타에서 사용되는 4개의 k
	double kv1,kv2,kv3,kv4;
	
	double dx, dv;
	
	h=(double)(t_1-t_0) / N; //Step사이즈 계산 or 0.1 지정 
	// h=0.1;
	 printf("h:%lf \n",h);
	for(int i=0 ; i < N-1 ; i++)
	{
		
		kx1 = result.vel[i];
		kv1 = spring_mass_damper_model(result.time[i], result.pos[i], result.vel[i]);
		
		kx2 = result.vel[i] + h*kv1/2;
		kv2 = spring_mass_damper_model(result.time[i]+h/2, result.pos[i]+h*kx1/2, result.vel[i]+h*kv1/2);
		
		kx3 = result.vel[i]+ h*kv2/2;
		kv3 = spring_mass_damper_model(result.time[i]+h/2, result.pos[i]+h*kx2/2, result.vel[i]+h*kv2/2);
		
		kx4 = result.vel[i]+ h*kv3;
		kv4 = spring_mass_damper_model(result.time[i]+h, result.pos[i]+h*kx3, result.vel[i]+h*kv3);
		
		dx=h*(kx1+2*kx2+2*kx3+kx4)/6;
		dv=h*(kv1+2*kv2+2*kv3+kv4)/6;
		
		result.pos[i+1] = result.pos[i] + dx;
		result.vel[i+1] = result.vel[i] + dv;
	}
	

	return result;
}

int main()
{
	
	
	runge_kutta result;
	time_t cur_time,init_time;
	
	for(int i=0; i<N;i++)//result 초기화
	{
		printf("result 구조체 초기화 \n");
		if(i == 0)
		{
			result.pos[i] = x_0;
			result.vel[i] = v_0;
			result.time[i] = t_0;
			init_time = time(NULL);
		}
		else
		{
			result.pos[i] = 0.0;
			result.vel[i] = 0.0;
			
			cur_time = time(NULL);
			result.time[i] = cur_time - init_time;
			printf("시각 : %d \n",result.time[i]); 
			if(i==N-1)
			{
				t_1 = result.time[i];
				printf("초기시각 : %d ~ 최종시각 : %d \n",t_0, t_1);
			}
		}
		sleep(1);
	}
	
	init_data();
		
	result = rungekutta_method(result);
	
			for(int i=0 ; i < N ; i++)
	{
		printf("time:%d초  pos= %lf\n", result.time[i],result.pos[i]); 
	}

	return 0;
} 
