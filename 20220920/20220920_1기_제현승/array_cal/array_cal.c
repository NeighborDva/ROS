#include <stdio.h>



int a,b,c,d;

void init_array(int Front[][b], int Back[][d])
{
	int i, j;
	printf("앞 배열 Front:\n");
	for(i = 0; i < a; i++){
		for(j = 0; j < b; j++){
			printf("%d행 %d열 :",i,j);
			scanf("%d", &Front[i][j]);
		}
		}
	
	printf("뒷 배열 Back:\n");
	for(i = 0; i < c; i++){
		for(j = 0; j < d; j++){
			printf("%d행 %d열 :",i,j);
			scanf("%d", &Back[i][j]);
		}
		}

}

int array_mul(int Front[][b], int Back[][d],double result[][d])
{
	int i, j, k;
	int f_c,r_r;
	
	printf("\n앞 배열 Front:\n");
	printf("%d x %d 행렬\n", a,b);
	for(i = 0; i < a; i++){
		for(j = 0; j < b; j++)
			printf("%d\t", Front[i][j]);
		printf("\n");
	}

	printf("\n");
	printf("뒷 배열 Back:\n");
	printf("%d x %d 행렬\n", c,d);
	for(i = 0; i < c; i++){
		for(j = 0; j < d; j++)
			printf("%d\t", Back[i][j]);
		printf("\n");
	}
	printf("\n");
	
	if(b == c)
	{
		printf("행렬 곱의 조건에 맞습니다.\n\n");
	}
	else
	{
		printf("행렬 곱의 조건에 맞지 않습니다. 조건에 맞는 데이터를 준비해주세요.\n");
		return -1;
	}

	
	for(i = 0; i < a; i++)
		for(j = 0; j < d; j++){
			result[i][j] = 0; //계산전 초기화
			for(k = 0; k < b; k++)
				result[i][j] += Front[i][k] * Back[k][j]; // A의 행요소 B의 열요소 간 곱 들의 합 ->결과행렬에 행순으로 채워짐
		}
		
		return 0;
}

int array_inverse(double result[][d])
{
	int i,j;
	int det=0;
	double inverse_array[a][d];
	
	
	printf("\n역행렬 조건1: 행렬이 정방 행렬일것\n");
	printf("역행렬 조건2: 행렬식의 값이 0이 아닐 것\n");
	printf("%d x %d 행렬\n", a,d);
 if(a == d)
 {
	printf("역행렬 조건1을 충족하셨습니다.\n");
 }	
  else
  {
	printf("역행렬 조건1을 충족하지 않습니다.\n");
	return -1;
  }
  
  if(a == 2)
  {
   det = result[0][0] * result[1][1]	-  result[0][1] * result[1][0];
   printf("det: %d\n", det);
   if(det != 0)
   {
	   printf("역행렬 조건2를 충족하셨습니다.\n");
	   inverse_array[0][0]=result[1][1]/det;
	    //printf("res00: %d\n", result[0][0]);
	   inverse_array[0][1]=-result[0][1]/det;
	    //printf("res01: %d\n", result[0][1] );
	   inverse_array[1][0]=-result[1][0]/det;
	    //printf("res10: %d\n", result[1][0] );
	   inverse_array[1][1]=result[0][0]/det;
	    //printf("res11: %d\n", result[1][1] );
	   
	   for(i = 0; i < a; i++)
		for(j = 0; j < d; j++){
				result[i][j] = inverse_array[i][j]; // 역행렬 결과 대입
		}
   }
   else
   {
	   printf("역행렬 조건2를 충족하지 않습니다.\n");
	   return -1;
	}	
  }
  else if(a == 3)
  {
	  det = result[0][0] * (result[1][1]*result[2][2] - result[1][2]*result[2][1])-result[0][1]*(result[1][0]*result[2][2]-result[1][2]*result[2][0])+result[0][2]*(result[1][0]*result[2][1] - result[1][1]*result[2][0]);
	  printf("det: %d\n", det);
   if(det != 0)
   {
	   printf("역행렬 조건2를 충족하셨습니다.\n");
		//전치행렬 계산
		for(i = 0; i < a; i++)
		for(j = 0; j < d; j++){
				inverse_array[j][i] = result[i][j]; 
		}
		result[0][0] = (inverse_array[1][1] * inverse_array[2][2] - inverse_array[2][1] * inverse_array[1][2]) / det;
		 //printf("res00: %d\n", result[0][0] );
		result[0][1] = (-(inverse_array[1][0] * inverse_array[2][2] - inverse_array[1][2] * inverse_array[2][0])) / det;
		 //printf("res01: %d\n", result[0][1] );
		result[0][2] = ((inverse_array[1][0] * inverse_array[2][1] - inverse_array[1][1] * inverse_array[2][0])) / det;
		 //printf("res02: %d\n", result[0][2] );
		result[1][0] = (-(inverse_array[0][1] * inverse_array[2][2] - inverse_array[1][2] * inverse_array[2][1])) / det;
		 //printf("res10: %d\n", result[1][0] );
		result[1][1] = ((inverse_array[0][0] * inverse_array[2][2] - inverse_array[1][2] * inverse_array[2][0])) / det;
		 //printf("res11: %d\n", result[1][1] );
		result[1][2] = (-(inverse_array[0][0] * inverse_array[2][1] - inverse_array[0][1] * inverse_array[2][0])) / det;
		 //printf("res12: %d\n", result[1][2] );
		result[2][0] = ((inverse_array[0][1] * inverse_array[1][2] - inverse_array[0][2] * inverse_array[1][1])) / det;
		 //printf("res20: %d\n", result[2][0] );
		result[2][1] = (-(inverse_array[0][0] * inverse_array[1][2] - inverse_array[0][2] * inverse_array[1][0])) / det;
		 //printf("res21: %d\n", result[2][1] );
		result[2][2] = ((inverse_array[0][0] * inverse_array[1][1] - inverse_array[0][1] * inverse_array[1][0])) / det;
		 //printf("res22: %d\n", result[2][2] );
   }
   else
   {
	   printf("역행렬 조건2를 충족하지 않습니다.\n");
	   return -1;
	}  
  }
  else
  {
	  printf("3x3 이후의 행렬에 대한 역행렬계산은 아직 미구현\n");
  }
 
 return 0;
}

int main(void) {
	printf("Front 행렬을 정의 해주세요\n");
	printf("Front 행: ");
	scanf("%d",&a);
	printf("Front 열: ");
	scanf("%d",&b);
	
	int Front_Arr[a][b];

	printf("back 행렬을 정의 해주세요\n");
	printf("back 행: ");
	scanf("%d",&c);
	printf("back 열: ");
	scanf("%d",&d);
	
	int Back_Arr[c][d];
	
	init_array(Front_Arr,Back_Arr);
	
	double result[a][d]; // result = Front_Arrⅹ Back_Arr
	
	int check;
	check= array_mul(Front_Arr,Back_Arr,result);
    
    if(check == 0)
    {
    printf("행렬 곱 결과 입니다.\n");
		
	int i, j, k;
	for(i = 0; i < a; i++){
		for(j = 0; j < d; j++)
			printf("%d\t", (int)result[i][j]);
		printf("\n");
	}
	
	}
	else
	{
		printf("행렬 곱을 할 수 없습니다.\n");
       return -1;
	}
	
	
	check = array_inverse(result);
	
	 if(check == 0)
    {
    printf("역 행렬 결과 입니다.\n");
		
	int i, j, k;
	for(i = 0; i < a; i++){
		for(j = 0; j < d; j++)
			printf("%lf\t", result[i][j]);
		printf("\n");
	}
	
	}
	else
	{
		printf("역행렬을 수행할 수 없습니다.\n");
       return -1;
	}
	
	return 0;
}

