#include <stdio.h>
#include <math.h>
#include <iostream>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

//데이터 개수
#define N 12

//점저장소
float datax[N] = {0,};
float datay[N] = {0,};

float dis(float x, float y, float a, float b) {
	return abs(a * x - y + b) / sqrt(a * a + 1);
}

float  f(float a, float b) {
	float sum = 0.0;
	for (int i = 0; i < N; i++) {
		sum += dis(datax[i], datay[i], a, b) / N;
	}
	return sum;
}

float dfabda(float a, float b, float da) {
	return (f(a + da, b) - f(a, b)) / da;
}
float dfabdb(float a, float b, float db) {
	return (f(a, b + db) - f(a, b)) / db;
}

float EE(float x0, float x1, float y0, float y1) {
	return sqrt((x0 - x1) * (x0 - x1)+(y0-y1)*(y0-y1));
}

int main() {
	srand(time(NULL));
	
	for (int i = 0; i <N; i++) {
		datax[i] = i+((rand()%11-5))/10.0 ;// -0.5~0.5 의 난수 오차 적용
		datay[i] = i+((rand()%11-5))/10.0;// -0.5~0.5 의 난수 오차 적용
		printf("%lf %lf\n", datax[i], datay[i]);
	}
	float a0 = 0, b0 = 0;
	
	int iteration = 0;
	
	float eta = 0.0001;
	float psi = 0.005;
	
	float da = 0.01;
	float db = 0.01;
		
	float a1 = 12, b1 = 17;
	while (EE(a0, b0, a1, b1) > eta && iteration < 1000000) {
		a0 = a1;
		b0 = b1;
		a1 -=   psi * dfabda(a0, b0, da);
		b1 -=   psi * dfabdb(a0, b0, db);
		iteration++;
	}
	printf("y = %lfx + %lf, iteration = %d, E = %lf\n", a1, b1, iteration, EE(a0, b0, a1, b1));
	return 0;
}
