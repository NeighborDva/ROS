#include <stdio.h>

float avg(int num[], int count)
{
	int i;
	int sum=0;
	float avg = 0;
	
	for(i=0;i<count;i++)
	{
		sum = sum + num[i];
		//printf("%d \n",sum);
	}
	
	avg = sum / (float)count;
	
	return avg;
}
int main()
{
	int i;
	float sum  = 0;
	float mx, my;
	float divisor,dividend;
	float a,b; //a:기울기, b:y절편
	//x값과 y값
	int x[4] = {2,4,6,8};
	int y[4] = {81,93,91,97};
	int length=sizeof(x)/sizeof(int);
	
	//x와 y의 평균값
	mx = avg(x, length);// 배열의 실제 크기를 알기 위해서는 이와같으 방식으로 다른 매개변수를 통해 배열 크기 받아야함
	my = avg(y, length);
	printf("x의 평균값: %lf \n", mx);
	printf("y의 평균값: %lf \n", my);
	
	//기울기 공식의 분모
	for(i = 0 ; i<4;i++){
		sum+=(mx-x[i]) * (mx-x[i]);
	}
	divisor = sum;
	//기울기 공식의 분자
	sum = 0;
	for(i = 0 ; i<4 ; i++)
	{
		sum +=(x[i] - mx) * (y[i] - my);
	}
	
	dividend = sum;
	printf("분모: %lf \n", divisor);
	printf("분자: %lf \n", dividend);
	// 기울기와 y 절편 구하기
	a = dividend / divisor;
	b = my - (mx*a);
	
	//출력으로 확인
	printf("기울기 a = %lf \n", a);
	printf("y 절편 b = %lf \n", b);
	printf("y = %lfx+%lf \n",a,b);
	
	return 0;
	
	
	
}
