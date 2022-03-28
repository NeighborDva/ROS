#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
int num1,num2;
int result;
 printf("argc = %d\n",argc);
 
 //printf(" %s\n",argv[0]);
 
 //argc, argv 숙지-> ./test 인자1 인자2 하면 ./test 포함 argv에 입력되고 개수가 argc에 입력
 for(int i=0 ; i<argc; i++)
 {
	 printf(" %s\n",argv[i]);
 }
 
num1 = atoi(argv[1]);
num2 = atoi(argv[2]);


printf("입력된 숫자는 %d, %d 입니다. \n",num1,num2);

printf("%d + %d = %d\n",num1,num2, num1+num2);
printf("%d - %d = %d\n",num1,num2, num1-num2);
printf("%d * %d = %d\n",num1,num2, num1*num2);
printf("%d / %d = %d\n",num1,num2, num1/num2);


 return 1;
 
}
