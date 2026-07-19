#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_periph.h"
#include "soc/timer_group_reg.h"
#define GPIO_PIN  5// GPIO5
void setup() {
 PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_PIN], PIN_FUNC_GPIO);
 *(volatile uint32_t*)GPIO_ENABLE_REG |= (1<<GPIO_PIN);
 Serial.begin(115200);
 unsigned long cur = micros();
  for (int i =0; i<1000; i++){
  *(volatile uint32_t*) GPIO_OUT_REG |= (1<<GPIO_PIN);
  *(volatile uint32_t*) GPIO_OUT_REG &= ~(1<<GPIO_PIN);
  }
  unsigned long now = micros()-cur;
  Serial.print(now);
}
void loop() {

}
