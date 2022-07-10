#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LED_GPIO_DIR "/sys/class/gpio"

int main(){
 int  jks_gp,value, i;
 char buff[256];
 FILE *jetson_led_gpio;
 
 printf("gp:");
 scanf("%d",&jks_gp);

 snprintf(buff,sizeof(buff),"%s/export",LED_GPIO_DIR);
 jetson_led_gpio = fopen(buff,"w");
 fprintf(jetson_led_gpio,"%d\n",jks_gp);
 fclose(jetson_led_gpio);

 snprintf(buff,sizeof(buff),"%s/gpio%d/direction",LED_GPIO_DIR,jks_gp);
 jetson_led_gpio = fopen(buff,"w");
 fprintf(jetson_led_gpio,"out\n");
 fclose(jetson_led_gpio);

 snprintf(buff,sizeof(buff),"%s/gpio%d/value",LED_GPIO_DIR,jks_gp);
 jetson_led_gpio = fopen(buff,"w");
 setvbuf(jetson_led_gpio,NULL,_IONBF,0);
  
 value = 0;
 for(i=0;i<=30;i++){
  fprintf(jetson_led_gpio,"%d\n",value);
  sleep(1);
  value = !value;
 }
 fclose(jetson_led_gpio);

 snprintf(buff,sizeof(buff),"%s/unexport",LED_GPIO_DIR);
 jetson_led_gpio = fopen(buff,"w");
 fprintf(jetson_led_gpio,"%d\n",jks_gp);
 fclose(jetson_led_gpio);

 return 0;
}
