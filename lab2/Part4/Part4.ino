#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"
#include "soc/timer_group_reg.h"

#define ledPin 19
#define readPin 1

uint16_t threshold;
int state = 0;
uint16_t reading = 0;
uint32_t LED_TOGGLE_INTERVAL = 10000000;
uint32_t cur = 0;
uint32_t last_toggle_time = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (1<<31); //T0_EN 
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (1<<30); //T0_INCREASE  
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0)&=~(TIMG_T0_DIVIDER_M);
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (0b1000 << 13);
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (1<<29);


  *(volatile uint32_t*) TIMG_T0ALARMLO_REG(0) = 10000000;  // reload at this count
  *(volatile uint32_t*) TIMG_T0ALARMHI_REG(0) = 0;

  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (1<<10);
  threshold = 2000; 
  ledcAttach(ledPin,512,12);

}

void loop() {
  // put your main code here, to run repeatedly:
  reading = analogRead(readPin);
*(volatile uint32_t *)TIMG_T0UPDATE_REG(0) = 1;
 cur = *((volatile uint32_t *)TIMG_T0LO_REG(0));
  if(reading <= threshold){
    if ((cur - last_toggle_time) >= LED_TOGGLE_INTERVAL) {
      Serial.println("interval met");
      if(state%3 == 0){
        ledcWrite(ledPin, 1023);
        Serial.println("state 0 ");
      } 
      if(state%3 == 1){
        ledcWrite(ledPin, 2047);
        Serial.println("state 1 ");
      }

      if(state%3 == 2){
          ledcWrite(ledPin, 4095);
          Serial.println("state 2 ");
      }

      state++;
      last_toggle_time = cur;
    }
  }
  else{
    ledcWrite(ledPin, 0);
    Serial.println("photores condition not meet ");
  }
}



