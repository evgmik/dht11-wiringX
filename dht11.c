#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h>  
#include <string.h>  

#include "wiringX.h"
#include "../src/platform/platform.h"

char *usage =
	"Usage: %s platform GPIO\n"
	"       GPIO is the GPIO to write to\n"
	"Example: %s bananapim2    1\n";

#define MAX_TIME 85  

int dht11_val[5]={0,0,0,0,0};  
  
void dht11_read_val(int dht11pin)  
{  
  uint8_t lststate=HIGH;  
  uint8_t counter=0;  
  uint8_t j=0,i;  
  for(i=0;i<5;i++)  
     dht11_val[i]=0;  
  pinMode(dht11pin,PINMODE_OUTPUT);  
  digitalWrite(dht11pin,HIGH);  
  delayMicroseconds(100*1000);  
  digitalWrite(dht11pin,LOW);  
  delayMicroseconds(20*1000);  
  digitalWrite(dht11pin,HIGH);  
  delayMicroseconds(40);  
  pinMode(dht11pin,PINMODE_INPUT);  
  for(i=0;i<MAX_TIME;i++)  
  {  
    counter=0;  
    while(digitalRead(dht11pin)==lststate){  
      counter++;  
      delayMicroseconds(1);  
      if(counter==255)  
        break;  
    }  
    lststate=digitalRead(dht11pin);  
    if(counter==255)  
       break;  
    // top 3 transistions are ignored  
    if((i>=4)&&(i%2==0)){  
      dht11_val[j/8]<<=1;  
      if(counter>16)  
        dht11_val[j/8]|=1;  
      j++;  
    }  
  }  
  // verify cheksum and print the verified data  
  if((j>=40)&&(dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF)))  
  {   
    printf("Humidity = %d.%d %% Temperature = %d.%d °C\n",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3]);  
  }  
  else  
    printf("Invalid Data!!\n");  
}  
  
int main(int argc, char *argv[]) {
	char *str = NULL, *platform = NULL;
	char usagestr[130];
	int gpio = 0, invalid = 0;

	memset(usagestr, '\0', 130);

	// expect only 1 argument => argc must be 2
	if(argc != 3) {
		snprintf(usagestr, 129, usage, argv[0], argv[0]);
		puts(usagestr);
		return -1;
	}

	// check for a valid, numeric argument
	platform = argv[1];
	str = argv[2];
	while(*str != '\0') {
		if(!isdigit(*str)) {
			invalid = 1;
		}
		str++;
	}
	if(invalid == 1) {
		printf("%s: Invalid GPIO %s\n", argv[0], argv[2]);
		return -1;
	}

	gpio = atoi(argv[2]);

	if(wiringXSetup(platform, NULL) == -1) {
		wiringXGC();
		return -1;
	}

	if(wiringXValidGPIO(gpio) != 0) {
		printf("%s: Invalid GPIO %d\n", argv[0], gpio);
		wiringXGC();
		return -1;
	}

  printf("Interfacing Temperature and Humidity Sensor (DHT11) With Banana Pi\n");  

  while(1)  
  {  
     dht11_read_val(gpio);  
     usleep(3000*1000);  
  }  
  return 0;  
}

