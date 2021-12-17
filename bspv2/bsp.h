#ifndef BSP_H_
#define BSP_H_

#include "stm32g0xx.h"
#include <stdlib.h>

/* ONBOARD LED  PC6
 * BUTTON  PA5
 * LED PB5
 *
 * SSD => A= PA1 B= PA4 C= PA5 D= PA12 E= PA11 F= PA6 G= PA7	D1 = PB4 D2= PB5 D3= PB3 D4= PA15
 * KEYPAD => R1= PB9 R2= PA8 R3= PB8 R4= PB2 C1= PB0 C2= PA9 C3= PA10 C4= PB1
 */


void system_init();


//SEVEN SEGMENT DISPLAY
void initSSD(void);
void clearSSD(void);
void setSSD(int x);


//KEYPAD
void initKeypad(void);
void clearRowsKeypad(void);
void setRowsKeypad(void);
void EXTI0_1_IRQHandler(void);
void EXTI4_15_IRQHandler(void);


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
void SysTick_Handler(void);
void delay_ms(uint32_t s);

void timer1_init();
void TIM1_BRK_UP_TRG_COM_IRQHandler(void);
void TIM2_IRQHandler(void);
void init_pwm2();
void IWDG_init(void);


void USART2_IRQHandler(void);
void printChar(uint8_t);
void UART_init(uint32_t);
void _print(int , char *, int );
void print(char *);




#endif
