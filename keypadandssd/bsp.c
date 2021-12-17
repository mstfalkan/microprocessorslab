/*
 * bsp.c
 *
 *  Created on: Dec 1, 2021
 *      Author: antih
 */
#include "stm32g0xx.h"
#include "bsp.h"

#define LEDDELAY    160000

static volatile uint32_t tick = 0;

void system_init(){
	initKeypad();
	EXTI0_1_IRQHandler();
	EXTI4_15_IRQHandler();
	initSSD();
	setRowsKeypad();
	clearSSD();
}



// D1 = PB4 D2= PB5 D3= PB3 D4= PA15

//SSD SET UP
void initSSD(void){
	//ENABLE GPIOA AND GPIOB PINS
		RCC->IOPENR	|= (1U<<0);
		RCC->IOPENR	|= (1U<<1);
	//SETUP SSD, CONNECTED TO PA1,PA4,PA5,PA12,PA11,PA6,PA7
		GPIOA->MODER &= ~(3U << 2*1);
		GPIOA->MODER |= (1U << 2*1); //PA1

		GPIOA->MODER &= ~(3U << 2*4);
		GPIOA->MODER |= (1U << 2*4); //PA4

		GPIOA->MODER &= ~(3U << 2*5);
		GPIOA->MODER |= (1U << 2*5); //PA5

		GPIOA->MODER &= ~(3U << 2*12);
		GPIOA->MODER |= (1U << 2*12); //PA12

		GPIOA->MODER &= ~(3U << 2*11);
		GPIOA->MODER |= (1U << 2*11); //PA11

		GPIOA->MODER &= ~(3U << 2*6);
		GPIOA->MODER |= (1U << 2*6); //PA6

		GPIOA->MODER &= ~(3U << 2*7);
		GPIOA->MODER |= (1U << 2*7); //PA7

		//D1 D2 D3 & D4 IN ORDER

		GPIOB->MODER &= ~(3U << 2*4);
		GPIOB->MODER |= (1U << 2*4); //PB4

		GPIOB->MODER &= ~(3U << 2*5);
		GPIOB->MODER |= (1U << 2*5); //PB5

		GPIOB->MODER &= ~(3U << 2*3);
		GPIOB->MODER |= (1U << 2*3); //PB3

		GPIOA->MODER &= ~(3U << 2*15);
		GPIOA->MODER |= (1U << 2*15); //PA15

}
void clearSSD(void){
	//clear all pins that connected for ssd
	GPIOA->BRR |= (1U << 1);	//A
	GPIOA->BRR |= (1U << 4);	//B
	GPIOA->BRR |= (1U << 5);	//C
	GPIOA->BRR |= (1U << 12);	//D
	GPIOA->BRR |= (1U << 11);	//E
	GPIOA->BRR |= (1U << 6);	//F
	GPIOA->BRR |= (1U << 7);	//G
	//GPIOA->BRR |= (1U << 15);	//D4
	//GPIOB->BRR |= (1U << 4);	//D1
	//GPIOB->BRR |= (1U << 5);	//D2
	//GPIOB->BRR |= (1U << 3);	//d3


}


void setSSD(int x){
	clearSSD();
	switch(x){
	case 0:
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 12);
		GPIOA->ODR |= (1U << 11);
		GPIOA->ODR |= (1U << 6);
		break;
	case 1:
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		break;

	case 2:
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 12);
		GPIOA->ODR |= (1U << 11);
		GPIOA->ODR |= (1U << 7);
		break;
	case 3:
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 12);
		GPIOA->ODR |= (1U << 7);
		break;
	case 4:
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 6);
		GPIOA->ODR |= (1U << 7);
		break;
	case 5:
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 12);
		GPIOA->ODR |= (1U << 6);
		GPIOA->ODR |= (1U << 7);
		break;
	case 6:
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 12);
		GPIOA->ODR |= (1U << 11);
		GPIOA->ODR |= (1U << 6);
		GPIOA->ODR |= (1U << 7);
		break;
	case 7:
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		break;
	case 8:
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 12);
		GPIOA->ODR |= (1U << 11);
		GPIOA->ODR |= (1U << 6);
		GPIOA->ODR |= (1U << 7);
		break;
	case 9:
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 6);
		GPIOA->ODR |= (1U << 7);
		break;
	case 10: //A
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 11);
		GPIOA->ODR |= (1U << 6);
		GPIOA->ODR |= (1U << 7);
		break;
	case 11: //B
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 11);
		GPIOA->ODR |= (1U << 12);
		GPIOA->ODR |= (1U << 6);
		GPIOA->ODR |= (1U << 7);
		break;
	case 12: //C
		GPIOA->ODR |= (1U << 1);
		GPIOA->ODR |= (1U << 11);
		GPIOA->ODR |= (1U << 12);
		GPIOA->ODR |= (1U << 6);
		break;
	case 13: //*
		GPIOA->ODR |= (1U << 7);
		break;
	case 14: //#
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 11);
		GPIOA->ODR |= (1U << 6);
		GPIOA->ODR |= (1U << 7);
		break;
	case 15: //D
		GPIOA->ODR |= (1U << 4);
		GPIOA->ODR |= (1U << 5);
		GPIOA->ODR |= (1U << 12);
		GPIOA->ODR |= (1U << 11);
		GPIOA->ODR |= (1U << 7);
		break;
		//A= PA1 B=PA4 C= PA5 D= PA12 E= PA11 F=PA6 G=PA7
	}
}


//KEYPAD SETUP
void initKeypad(void){
	//ENABLE GPIOA AND GPIOB PINS
		RCC->IOPENR	|= (1U<<0);
		RCC->IOPENR	|= (1U<<1);

		//SET PB9 PA8 PB8 PB2 AS OUTPUT (ROWS)
		//PA8
		GPIOA->MODER &= ~(3U << 2*8);
		GPIOA->MODER |= (1U << 2*8);
		//PB2
		GPIOB->MODER &= ~(3U << 2*2);
		GPIOB->MODER |= (1U << 2*2);
		//PB8
		GPIOB->MODER &= ~(3U << 2*8);
		GPIOB->MODER |= (1U << 2*8);
		//PB9
		GPIOB->MODER &= ~(3U << 2*9);
		GPIOB->MODER |= (1U << 2*9);

		//SET PB0 PA9 PA10 PB1 AS INPUT (COLS)
		//PA8
		GPIOA->MODER &= ~(3U << 2*9);
		GPIOA->PUPDR |= (2U << 2*9);
		//PA10
		GPIOA->MODER &= ~(3U << 2*10);
		GPIOA->PUPDR |= (2U << 2*10);
		//PB0
		GPIOB->MODER &= ~(3U << 2*0);
		GPIOB->PUPDR |= (2U << 2*0);
		//PB1
		GPIOB->MODER &= ~(3U << 2*1);
		GPIOB->PUPDR |= (2U << 2*1);


		//SETUP INTERREUPTS FOR INPUTS
		//PA9
		EXTI->EXTICR[2] |= (0U << 8*1); // EXTICR[2] FOR 8,9,10,11 pins -- 0U for A pins -- 8*1 for 9th pins
		//PA10
		EXTI->EXTICR[2] |= (0U << 8*2); // EXTICR[2] FOR 8,9,10,11 pins -- 0U for A pins -- 8*2 for 10th pins
		//PB0
		EXTI->EXTICR[0] |= (1U << 8*0); // EXTICR[2] FOR 0,1,2,3 pins -- 1U for B pins -- 8*0 for 0th pins
		//PB1
		EXTI->EXTICR[0] |= (1U << 8*1); // EXTICR[2] FOR 0,1,2,3 pins -- 1U for B pins -- 8*0 for 1ST pins

		EXTI -> RTSR1 |= (1U << 9);
		EXTI -> RTSR1 |= (1U << 10);
		EXTI -> RTSR1 |= (1U << 0);
		EXTI -> RTSR1 |= (1U << 1);

		EXTI -> IMR1 |= (1U << 9);
		EXTI -> IMR1 |= (1U << 10);
		EXTI -> IMR1 |= (1U << 0);
		EXTI -> IMR1 |= (1U << 1);

		NVIC_SetPriority(EXTI0_1_IRQn, 0);
		NVIC_EnableIRQ(EXTI0_1_IRQn);
		NVIC_SetPriority(EXTI4_15_IRQn, 0);
		NVIC_EnableIRQ(EXTI4_15_IRQn);

}


void clearRowsKeypad(void){
	GPIOA->BRR |= (1U << 8); //PA8
	GPIOB->BRR |= (1U << 2); //PB2
	GPIOB->BRR |= (1U << 8); //PB8
	GPIOB->BRR |= (1U << 9); //PB9
}
void setRowsKeypad(void){
	GPIOA->ODR |= (1U << 8); //PA8
	GPIOB->ODR |= (1U << 2); //PB2
	GPIOB->ODR |= (1U << 8); //PB8
	GPIOB->ODR |= (1U << 9); //PB9
}

void EXTI0_1_IRQHandler(void){
	if ( (EXTI-> RPR1 >> 0) & 1){
		//INTERRUPT FOR PB0
			clearRowsKeypad();

			GPIOB->ODR ^= (1U << 9); //PB9
			if ((GPIOB->IDR >> 0 ) & 1){
				// 1
				setSSD(1);
			}
			GPIOB->ODR ^= (1U << 9); //PB9

			GPIOB->ODR ^= (1U << 8); //PB8
				if ((GPIOB->IDR >> 0 ) & 1){
					// 7
				setSSD(7);
				}
			GPIOB->ODR ^= (1U << 8); //PB8

			GPIOB->ODR ^= (1U << 2); //PB2
				if ((GPIOB->IDR >> 0 ) & 1){
					// *
					setSSD(13);
				}
			GPIOB->ODR ^= (1U << 2); //PB2

			GPIOA->ODR ^= (1U << 8); //PA8
				if ((GPIOB->IDR >> 0 ) & 1){
					// 4
					setSSD(4);
				}
			GPIOA->ODR ^= (1U << 8); //PB9


			EXTI->RPR1 |= (1U << 0);
			setRowsKeypad();
	}
	if ( (EXTI-> RPR1 >> 1) & 1){
			//INTERRUPT FOR PB1
				clearRowsKeypad();

				GPIOB->ODR ^= (1U << 9); //PB9
				if ((GPIOB->IDR >> 1 ) & 1){
					// A
					setSSD(10);
				}
				GPIOB->ODR ^= (1U << 9); //PB9

				GPIOB->ODR ^= (1U << 8); //PB8
					if ((GPIOB->IDR >> 1 ) & 1){
						// C
					setSSD(12);
					}
				GPIOB->ODR ^= (1U << 8); //PB8

				GPIOB->ODR ^= (1U << 2); //PB2
					if ((GPIOB->IDR >> 1 ) & 1){
						// D
						setSSD(15);
					}
				GPIOB->ODR ^= (1U << 2); //PB2

				GPIOA->ODR ^= (1U << 8); //PA8
					if ((GPIOB->IDR >> 1 ) & 1){
						// B
						setSSD(11);
					}
				GPIOA->ODR ^= (1U << 8); //PB9


				EXTI->RPR1 |= (1U << 0);
				setRowsKeypad();
		}

}

void EXTI4_15_IRQHandler(void){
	if (( EXTI->RPR1 >> 9 ) &1 ){
		//INTERRUPT FOR PA9
			clearRowsKeypad();

			GPIOB->ODR ^= (1U << 9); //PB9
			if ((GPIOA->IDR >> 9 ) & 1){
				// 2
				setSSD(2);
			}
			GPIOB->ODR ^= (1U << 9); //PB9

			GPIOB->ODR ^= (1U << 8); //PB8
				if ((GPIOA->IDR >> 9 ) & 1){
					// 8
				setSSD(8);
				}
			GPIOB->ODR ^= (1U << 8); //PB8

			GPIOB->ODR ^= (1U << 2); //PB2
				if ((GPIOA->IDR >> 9 ) & 1){
					// 0
					setSSD(0);
				}
			GPIOB->ODR ^= (1U << 2); //PB2

			GPIOA->ODR ^= (1U << 8); //PA8
				if ((GPIOA->IDR >> 9 ) & 1){
					// 5
					setSSD(5);
				}
				GPIOA->ODR ^= (1U << 8); //PB9
				setRowsKeypad();

	}
	if (( EXTI->RPR1 >> 10 ) &1 ){
		//INTERRUPT FOR PA10
			clearRowsKeypad();

			GPIOB->ODR ^= (1U << 9); //PB9
			if ((GPIOA->IDR >> 10 ) & 1){
				// 3
				setSSD(3);
			}
			GPIOB->ODR ^= (1U << 9); //PB9

			GPIOB->ODR ^= (1U << 8); //PB8
				if ((GPIOA->IDR >> 10 ) & 1){
					// 9
				setSSD(9);
				}
			GPIOB->ODR ^= (1U << 8); //PB8

			GPIOB->ODR ^= (1U << 2); //PB2
				if ((GPIOA->IDR >> 10 ) & 1){
					// #
					setSSD(14);
				}
			GPIOB->ODR ^= (1U << 2); //PB2

			GPIOA->ODR ^= (1U << 8); //PA8
				if ((GPIOA->IDR >> 10 ) & 1){
					// 6
					setSSD(6);
				}
				GPIOA->ODR ^= (1U << 8); //PB9
				setRowsKeypad();

	}
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
void SysTick_Handler(void){

	if(tick > 0){
		--tick;
	}
}

void delay_ms(uint32_t s){
	tick = s;
	while(tick);
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
  	TIM1->PSC = 999; //her 999da bir 16000lÄ±k cylce bu da 16mhz
  	TIM1->ARR = 16000;

  	TIM1->DIER |= (1 << 0); //UPDATE INTERRUPT ENABLE
  	TIM1->CR1 |= (1 << 0); //TIM1 ENABLE

	NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1);
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
}

