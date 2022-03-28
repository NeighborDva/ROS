#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 쓰레드 함수--. 쓰레스 실습시 텍스트 파일 속 예제 긁어올것

void *t_function1(void *data)
{
    int id;
    int i = 0;
    id = *((int *)data);


 
    while(1)
    {
        printf("%d : %d\n", id, i);
        i++;
        sleep(1);
    }
}

// 1초를 기다린후 아규먼트^2 을 리턴한다.
void *t_function2(void *data)
{
    char a[100000];
    int num = *((int *)data);
 printf("Thread Start\n");
    sleep(5);
 printf("Thread end\n");
}


  /*
 1.int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
          
* 쓰레드 생성을 위해서 사용 
* 첫번째 아규먼트인 thread 는 쓰레드가 성공적으로 생성되었을때 생성된 쓰레드를 식별하기 위해서 사용되는 쓰레드 식별자
* 두번째 아규먼트인 attr 은 쓰레드 특성을 지정하기 위해서 사용하며, 기본 쓰레드 특성을 이용하고자 할경우에 NULL 을 사용
* 3번째 아규먼트인 start_routine는 분기시켜서 실행할 쓰레드 함수
* 4번째 아규먼는인 arg는 쓰레드 함수의 인자
* 성공적으로 생성될경우 0을 리턴하며, 실패하면 0보다 작은수를 리턴
     */
  
  /*
2.int pthread_join(pthread_t th, void **thread_return);

*첫번째 아규먼트 th는 기다릴(join)할 쓰레드 식별자
*두번째 아규먼트 thread_return은 쓰레드의 리턴(return) 값
*thread_return 이 NULL 이 아닐경우 해다 포인터로 쓰레드 리턴 값을 받기 가능 
   */
  
  /*
3.int pthread_detach(pthread_t th);
 
*main 쓰레드에서 pthread_create 를 이용해 생성된 쓰레드를 분리 
*식별번호th인 쓰레드를 detach 시키는데, detach 되었을경우 해당(detach 된) 쓰레드가 종료될경우 pthread_join 을 호출하지 않더라도 즉시 모든 자원이 해제(free)
*pthread_create 호출후 detach 하는 방법과 pthread_create 호출시에 쓰레드가 detach 되도록 하는 방법도 있음
   */
int main()
{
    pthread_t p_thread[2];
    int thr_id;
    int status;
    int a = 1;
    int b = 2;

    // 쓰레드 생성 아규먼트로 1 을 넘긴다.  
    thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }

    // 쓰레드 생성 아규먼트로 2 를 넘긴다. 
    thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)&b);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }

    // 쓰레드 종료를 기다린다. 
    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);

    return 0;
}
