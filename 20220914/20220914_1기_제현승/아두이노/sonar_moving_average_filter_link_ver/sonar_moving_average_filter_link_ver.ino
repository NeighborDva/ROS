#include <NewPing.h>

#define TRIG 12
#define ECHO 11
#define MAX_DISTANCE 200 //200cm

NewPing sonar(TRIG, ECHO, MAX_DISTANCE); 



//// movig filter부분
#define N_DATA 5

double meas_save[N_DATA];



typedef struct mov_avg_filter
{
  double x_n[N_DATA]; 
  double x_avg; 
}mov_avg_filt;


mov_avg_filt res;

void init_res()
{
for(int i=0; i<N_DATA;i++)//ones 1로 초기화
  {
    res.x_n[i] = 0.0;
  }
  //  result.x_n[N_DATA]={1.0,}; //이방식으로 하니  error: expected expression before ‘{’ token 에러 발생
  res.x_avg = 0.0;
}

double get_sonar()
{
 double dDist = (double)sonar.ping()/US_ROUNDTRIP_CM;

  return dDist;
}

mov_avg_filt moving_avg_filter(mov_avg_filt result, double x_meas) //
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
////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Sonar_Meas");
  init_res();
}

void loop() {
  // put your main code here, to run repeatedly:

  
  double x_meas=0.0;
  init_res();
  
  for(int i=0; i<N_DATA;i++)
  {
    x_meas = get_sonar();
    res = moving_avg_filter(res,x_meas);
      
    Serial.println(res.x_avg);
    delay(200);
  }
}
