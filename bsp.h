#ifndef BSP_H_
#define BSP_H_

#include "stm32g0xx.h"
#include <stdlib.h>

/* ONBOARD LEDİ  PC6
 * BUTTON  PA5
 * LED PB5
 */



void system_init();

void onboardLed_Set();
void onboardLed_TurnOn();
void onboardLed_TurnOff();
void onboardLed_Toggle();

void button_set();
int button_read();
void button_interrupt();

void led_Set();
void led_TurnOn();
void led_TurnOff();
void led_Toggle();


void clock_init();
void systicktimer_init();
void timer1_init();
void TIM1_BRK_UP_TRG_COM_IRQHandler(void);


#endif /* SEVENSEGMENT_H_ */
