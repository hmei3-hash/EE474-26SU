#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"
#include "soc/timer_group_reg.h"
#define GPIO_PIN  05// GPIO5
void setup() {
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (1<<31); //T0_EN 
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (1<<30); //T0_INCREASE  
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0)&=~(TIMG_T0_DIVIDER_M);
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (0b1000 << 13);
  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (1<<29);


  *(volatile uint32_t*) TIMG_T0ALARMLO_REG(0) = 10000000;  // reload at this count
  *(volatile uint32_t*) TIMG_T0ALARMHI_REG(0) = 0;

  *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (1<<10);
  //uint64_t threshold = 10000000; 
  //*(volatile uint32_t*) TIMG_T0ALARMLO_REG(0) = threshold & 0xFFFFFFFF; 
  //*(volatile uint32_t*) TIMG_T0ALARMHI_REG(0) = threshold >>32;


  PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO);
 *(volatile uint32_t*)GPIO_ENABLE_REG |= (1<<GPIO_PIN);


  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
    bool ledState = false;

    if (*(volatile uint32_t*) TIMG_INT_RAW_TIMERS_REG(0) & (1 << 0)) {
    ledState = !ledState;
    Serial.print("triggered");
    
    //*(volatile uint32_t*) GPIO_OUT_REG ^= (1 << GPIO_PIN);
    *(volatile uint32_t*) TIMG_INT_CLR_TIMERS_REG(0) |= (1 << 0); // clear flag
    *(volatile uint32_t*) TIMG_T0CONFIG_REG(0) |= (1 << 10);      // re-arm alarm
    if (ledState){*(volatile uint32_t*) GPIO_OUT_REG ^= (1 << GPIO_PIN);}
    else{
      *(volatile uint32_t*) GPIO_OUT_REG &= ~(1 << GPIO_PIN);
    }
    }
}
/* *(volatile uint32_t*) TIMG_T0UPDATE_REG(0) = 1;
  uint32_t count = *(volatile uint32_t*) TIMG_T0LO_REG(0);

  if(*(volatile uint32_t*) TIMG_T0LO_REG(0)>=10000000){
     *(volatile uint32_t*) GPIO_OUT_REG ^= (1<<GPIO_PIN);
  }*/
