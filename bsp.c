/*
 * bsp.c
 *
 *  Created on: Dec 1, 2021
 *      Author: antih
 */
#include "stm32g0xx.h"
#include "bsp.h"

#define LEDDELAY    160000


void system_init(){
	clock_init();
	onboardLed_Set();
	button_set();
	led_Set();
	systicktimer_init();
}

//INITILIZE ONBOARD LED CONNECTED TO PC6 PIN AND CONFIGURATION
void onboardLed_Set(){
    /* Enable GPIOC clock */
    RCC->IOPENR |= (1U << 2);
    /* Setup PC6 as output for onboard led*/
    GPIOC->MODER &= ~(3U << 2*6);
    GPIOC->MODER |= (1U << 2*6);
}
void onboardLed_TurnOn(){
    /* Turn on LED */
    GPIOC->ODR |= (1U << 6);
}
void onboardLed_TurnOff(){
    /* Turn on LED */
    GPIOC->BRR |= (1U << 6);
}
void onboardLed_Toggle(){
    /* Turn on LED */
    GPIOC->ODR ^= (1U << 6);
}



//INITILIZE BUTTON CONNECTED TO PA5 PIN

void button_set(){
    /* Enable GPIOA clock */
    RCC->IOPENR |= (1U << 0);
	//Set PA5 as input
	GPIOA->MODER &= ~(3U << 2*5);
}
//RETURNS 1 IF BUTTONS PRESSED
int button_read(){
	int b = ((GPIOA->IDR >>5 ) & 0X1);
	if(b)
		return 0;
	else return 1;
}

//BUTTON WITH EXTERNAL INTERRUPTS
void button_interrupt(){
	//Set PA5 as input
	EXTI->RTSR1 |= (1U << 5);
	EXTI->EXTICR[5] |= (1U << 8*5);
	EXTI->IMR1 |= (1U << 5);

	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

//INITILIZATION AND CONFIGURATION OF LED THAT CONNECTED TO PB5
void led_Set(){
    /* Enable GPIOB clock */
    RCC->IOPENR |= (1U << 1);
    /* Setup PC6 as output for onboard led*/
    GPIOB->MODER &= ~(3U << 2*5);
    GPIOB->MODER |= (1U << 2*5);
}
void led_TurnOn(){
    /* Turn on LED */
    GPIOB->ODR |= (1U << 5);
}
void led_TurnOff(){
    /* Turn off LED */
    GPIOB->BRR |= (1U << 5);
}
void led_Toggle(){
    /* Turn off LED */
    GPIOB->ODR ^= (1U << 5);
}


//SYSTICK TIMER OPERATIONS

void clock_init(){
	SystemCoreClockUpdate();
}
void systicktimer_init(){
	SysTick_Config(SystemCoreClock / 1000);
}

//TIMER OPERATIONS

void TIM1_BRK_UP_TRG_COM_IRQHandler(void){

	onboardLed_Toggle();
	TIM1->SR &= ~(1U << 0); // CLEAR UPDATE STATUS REGISTER

}
void timer1_init(){
	RCC->APBENR2 |= (1U << 11); //enable tim1 module clock
	TIM1->CR1 = 0; //ZERO OUT THE CONTROL REGISTER
	TIM1->CR1 |= (1 << 7); //ARPE MODE
	TIM1->CNT = 0;

  	//1 SECOND INTERRUPT
  	TIM1->PSC = 999; //her 999da bir 16000lık cylce bu da 16mhz
  	TIM1->ARR = 16000;

  	TIM1->DIER |= (1 << 0); //UPDATE INTERRUPT ENABLE
  	TIM1->CR1 |= (1 << 0); //TIM1 ENABLE

	NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1);
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
}


