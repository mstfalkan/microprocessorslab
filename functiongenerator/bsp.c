/*
 * bsp.c
 *
 *  Created on: Dec 1, 2021
 *      Author: antih
 */
#include "stm32g0xx.h"
#include <math.h>
#include "bsp.h"

static int arr[255]={0x1f40,0x2004,0x20c8,0x218c,0x2250,0x2313,0x23d5,0x2497,0x2558,0x2618,0x26d7,0x2795,0x2852,0x290d,0x29c6,0x2a7e,0x2b35,0x2be9,0x2c9c,0x2d4c,0x2dfa,0x2ea6,0x2f50,0x2ff7,0x309c,0x313e,0x31dd,0x3279,0x3312,0x33a9,0x343c,0x34cb,0x3558,0x35e1,0x3667,0x36e9,0x3767,0x37e2,0x3859,0x38cc,0x393b,0x39a6,0x3a0d,0x3a70,0x3ace,0x3b29,0x3b7f,0x3bd1,0x3c1e,0x3c67,
		0x3cab,0x3ceb,0x3d27,0x3d5d,0x3d8f,0x3dbd,0x3de5,0x3e09,0x3e28,0x3e43,0x3e58,0x3e69,0x3e75,0x3e7d,0x3e7f,0x3e7d,0x3e75,0x3e69,0x3e58,0x3e43,0x3e28,0x3e09,0x3de5,0x3dbd,0x3d8f,0x3d5d,0x3d27,0x3ceb,0x3cab,0x3c67,0x3c1e,0x3bd1,0x3b7f,0x3b29,0x3ace,0x3a70,0x3a0d,0x39a6,0x393b,0x38cc,0x3859,0x37e2,0x3767,0x36e9,0x3667,0x35e1,0x3558,0x34cb,0x343c,0x33a9,
		0x3312,0x3279,0x31dd,0x313e,0x309c,0x2ff7,0x2f50,0x2ea6,0x2dfa,0x2d4c,0x2c9c,0x2be9,0x2b35,0x2a7e,0x29c6,0x290d,0x2852,0x2795,0x26d7,0x2618,0x2558,0x2497,0x23d5,0x2313,0x2250,0x218c,0x20c8,0x2004,0x1f40,0x1e7b,0x1db7,0x1cf3,0x1c2f,0x1b6c,0x1aaa,0x19e8,0x1927,0x1867,0x17a8,0x16ea,0x162d,0x1572,0x14b9,0x1401,0x134a,0x1296,0x11e3,0x1133,0x1085,0xfd9,
		0xf2f,0xe88,0xde3,0xd41,0xca2,0xc06,0xb6d,0xad6,0xa43,0x9b4,0x927,0x89e,0x818,0x796,0x718,0x69d,0x626,0x5b3,0x544,0x4d9,0x472,0x40f,0x3b1,0x356,0x300,0x2ae,0x261,0x218,0x1d4,0x194,0x158,0x122,0xf0,0xc2,0x9a,0x76,0x57,0x3c,0x27,0x16,0xa,0x2,0x0,0x2,0xa,0x16,0x27,0x3c,0x57,0x76,
		0x9a,0xc2,0xf0,0x122,0x158,0x194,0x1d4,0x218,0x261,0x2ae,0x300,0x356,0x3b1,0x40f,0x472,0x4d9,0x544,0x5b3,0x626,0x69d,0x718,0x796,0x818,0x89e,0x927,0x9b4,0xa43,0xad6,0xb6d,0xc06,0xca2,0xd41,0xde3,0xe88,0xf2f,0xfd9,0x1085,0x1133,0x11e3,0x1296,0x134a,0x1401,0x14b9,0x1572,0x162d,0x16ea,0x17a8,0x1867,0x1927,0x19e8,
		0x1aaa,0x1b6c,0x1c2f,0x1cf3,0x1db7,0x1e7b,0x1f40};
static int freq={50};

#define LEDDELAY    160000;

void BSP_systemInit(void){
	setRCCForSSD();
	setMODERForSSD();
	setRCCForKeypad();
	setMODERForKeypad();
	setInterruptForKeypad();
	setAllKeypadRows();
	resetAllSSDDigits();
}


void TIM2_IRQHandler(void){

	TIM2->SR &= ~(1U << 0);
}

void init_pwm2(){
	//WORKING WITH PB3 PIN'S AF2 FUNCTION AS TIM2_CH2
	//enable gpiob
	RCC->IOPENR |= (1U << 1);
	//enable tim2 clock
	RCC->APBENR1 |= RCC_APBENR1_TIM2EN;


	//select AF from moder
	GPIOB->MODER &= ~(3U << 2*3);
	GPIOB->MODER |= (2U << 2*3);
	//set alternate function 2 // 0010 FOR AF2
	GPIOB->AFR[0] &= ~(0XFU << 4*3);
	GPIOB->AFR[0] |= (2U << 4*3);



    // zero out the control register just in case
	TIM2->CR1 = 0;

    // Select PWM Mode 1
    TIM2->CCMR1 |= (6U << 12);
    // Preload Enable
    TIM2->CCMR1 |= TIM_CCMR1_OC2PE;

    // Capture compare ch2 enable
    TIM2->CCER |= TIM_CCER_CC2E;

    // zero out counter
    TIM2->CNT = 0;
    // 1 ms interrupt
    TIM2->PSC = 63;// 16 bit;
    TIM2->ARR = 4999;

    // zero out duty


    	for(int i =  0; i<258; i++){

    		TIM2->CCR2 = i;
    }

    // Update interrupt enable
    TIM2->DIER |= (1 << 0);

    // TIM1 Enable
    TIM2->CR1 |= TIM_CR1_CEN;

    NVIC_SetPriority(TIM2_IRQn, 1);
    NVIC_EnableIRQ(TIM2_IRQn);

}


//SEVEN SEGMENT


void resetAllSSDDigits() {
	GPIOA -> ODR |= ((uint32_t) (0x80));
	GPIOB -> ODR |= ((uint32_t) (0x8));
	GPIOA -> ODR |= ((uint32_t) (0x400));
	GPIOB -> ODR |= ((uint32_t) (0x2));
}

void setSSDDigit(uint8_t digit) {
   /*
    * 		   D1	=>	PA7
	* 		   D2	=>	PB3
	* 		   D3	=>	PA10
	* 		   D4	=>	PB1
    */

	// Ã¶nce hepsini kapat
	resetAllSSDDigits();
	// ** //

	switch(digit) {
	case 1:
		GPIOA -> ODR &= ~((uint32_t) (0x80)); //1000 0000
		break;
	case 2:
		GPIOB -> ODR &= ~((uint32_t) (0x8)); // 1000
		break;
	case 3:
		GPIOA -> ODR &= ~((uint32_t) (0x400)); // 0100 0000 0000
		break;
	case 4:
		GPIOB -> ODR &= ~((uint32_t) (0x2)); //0010
		break;
	default:
		break;
	}
}

void dispNumberDigitInSSD(uint8_t zeroToFifteen, uint8_t SSDDigit) {
	setSSDDigit(SSDDigit);

	//CLEAR
		GPIOA->ODR &= ~(1U << 0); //PA0    A
		GPIOA->ODR &= ~(1U << 1); //PA1    B
		GPIOA->ODR &= ~(1U << 4); //PA4    F
		GPIOA->ODR &= ~(1U << 5); //PA5    G
		GPIOA->ODR &= ~(1U << 12); //PA12  C
		GPIOA->ODR &= ~(1U << 11); //PA11  E
		GPIOA->ODR &= ~(1U << 6); //PA6    D
		GPIOB->ODR &= ~(1U << 6); //PB6    .

		switch(zeroToFifteen){
			case 0:
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 12); //PA12  C
				GPIOA->ODR |= (1U << 6); //PA6    D
				GPIOA->ODR |= (1U << 11); //PA11  E
				GPIOA->ODR |= (1U << 4); //PA4    F
				break;
			case 1:
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 12); //PA12  C
				break;
			case 2:
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 11); //PA11  E
				GPIOA->ODR |= (1U << 6); //PA6    D
				GPIOA->ODR |= (1U << 5); //PA5    G
				break;
			case 3:
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 12); //PA12  C
				GPIOA->ODR |= (1U << 6); //PA6    D
				GPIOA->ODR |= (1U << 5); //PA5    G
				break;
			case 4:
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 11); //PA11  E
				GPIOA->ODR |= (1U << 4); //PA4    F
				GPIOA->ODR |= (1U << 5); //PA5    G
				break;
			case 5:
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 12); //PA12  C
				GPIOA->ODR |= (1U << 6); //PA6    D
				GPIOA->ODR |= (1U << 4); //PA4    F
				GPIOA->ODR |= (1U << 5); //PA5    G
				break;
			case 6:
				GPIOA->ODR |= (1U << 0); //PA0    A
			    GPIOA->ODR |= (1U << 12); //PA12  C
			    GPIOA->ODR |= (1U << 6); //PA6    D
			    GPIOA->ODR |= (1U << 11); //PA11  E
			    GPIOA->ODR |= (1U << 4); //PA4    F
			    GPIOA->ODR |= (1U << 5); //PA5    G
				break;
			case 7:
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 12); //PA12  C
				break;
			case 8:
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 4); //PA4    F
				GPIOA->ODR |= (1U << 5); //PA5    G
				GPIOA->ODR |= (1U << 12); //PA12  C
				GPIOA->ODR |= (1U << 11); //PA11  E
				GPIOA->ODR |= (1U << 6); //PA6    D
				break;
			case 9:
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 4); //PA4    F
				GPIOA->ODR |= (1U << 5); //PA5    G
				GPIOA->ODR |= (1U << 12); //PA12  C
				GPIOA->ODR |= (1U << 6); //PA6    D
				break;
			case 10: //A
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 4); //PA4    F
				GPIOA->ODR |= (1U << 5); //PA5    G
				GPIOA->ODR |= (1U << 12); //PA12  C
				GPIOA->ODR |= (1U << 11); //PA11  E
				break;
			case 11: //B
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 4); //PA4    F
				GPIOA->ODR |= (1U << 5); //PA5    G
				GPIOA->ODR |= (1U << 12); //PA12  C
				GPIOA->ODR |= (1U << 11); //PA11  E
				GPIOA->ODR |= (1U << 6); //PA6    D
				break;
			case 12: //C
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 6); //PA6    D
				GPIOA->ODR |= (1U << 11); //PA11  E
				GPIOA->ODR |= (1U << 4); //PA4    F
				break;

			case 13: //D
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 12); //PA12  C
				GPIOA->ODR |= (1U << 6); //PA6    D
				GPIOA->ODR |= (1U << 11); //PA11  E
				GPIOA->ODR |= (1U << 4); //PA4    F
				break;

			case 14: //#
				GPIOA->ODR |= (1U << 0); //PA0    A
				GPIOA->ODR |= (1U << 1); //PA1    B
				GPIOA->ODR |= (1U << 5); //PA5    G
				GPIOA->ODR |= (1U << 4); //PA4    F
				break;

			case 15: //*
				GPIOA->ODR |= (1U << 6); //PA6    D

				break;

			}
		}


void delay(volatile uint32_t s) {
    for(; s>0; s--);
}

// PINLERE GORE AYARLAMAN LAZIM
void setRCCForSSD() {
	// A ve B pinlerini aÃ§
	RCC -> IOPENR |= (3U);
}

// PINLERE GORE AYARLAMAN LAZIM
void setMODERForSSD() {
	// A iÃ§in (SADECE SSD PINLERI)
	// 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
	// xx xx xx 01 01 01 xx xx 01 01 01 01 xx xx 01 01  lazÄ±m
	// 00 00 00	01 01 01 00 00 01 01 01 01 00 00 01 01 = 0x1505505  orlamak iÃ§in
	// 11 11 11	01 01 01 11 11 01 01 01 01 11 11 01 01 = 0xFD5F55F5 andlemek iÃ§in
	GPIOA -> MODER |= (uint32_t) (0x1505505);
	GPIOA -> MODER &= (uint32_t) (0xFD5F55F5);

	// B iÃ§in (SADECE SSD PINLERI)
	// 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
	// xx xx xx xx xx xx xx xx xx xx xx xx 01 xx 01 xx
	// 	  								   01 00 01 00 = 0x44 orlamak iÃ§in
	// 11 11 11 11 11 11 11 11 11 01 11 11 11 11 01 11 = 0xFFFFFF77 andlemek iÃ§in
	GPIOB -> MODER |= (uint32_t) (0x404);
	GPIOB -> MODER &= (uint32_t) (0xFFFFDFF7);
}






//KEYPAD

typedef enum keypadButton{keypadBut0 = 0, keypadBut1, keypadBut2, keypadBut3, keypadBut4,
	keypadBut5, keypadBut6, keypadBut7, keypadBut8, keypadBut9, keypadButA,
	keypadButB, keypadButC, keypadButD, keypadButHash, keypadButAst, none} keypadBut_t;


void setRCCForKeypad() {
	// A ve B pinlerini aÃ§
	RCC -> IOPENR |= (3U);
}

void setMODERForKeypad() {
	// ROW AYARLARI
	GPIOB -> MODER &= ~(3U << 4*2);
	GPIOB -> MODER |= (1U << 4*2);

	GPIOB -> MODER &= ~(3U << 5*2);
	GPIOB -> MODER |= (1U << 5*2);

	GPIOB -> MODER &= ~(3U << 9*2);
	GPIOB -> MODER |= (1U << 9*2);

	GPIOB -> MODER &= ~(3U << 8*2);
	GPIOB -> MODER |= (1U << 8*2);

	//COLUMN (INPUT) AYARLARI
	GPIOB -> MODER &= ~(3U << 8*2);
	GPIOB -> MODER &= ~(3U << 2*2);
	GPIOB -> MODER &= ~(3U << 0*2);
	GPIOA -> MODER &= ~(3U << 9*2);

	//COLUMN PUPDR AYARLARI
	GPIOB -> PUPDR |= (2U << 8*2);
	GPIOB -> PUPDR |= (2U << 2*2);
	GPIOB -> PUPDR |= (2U << 0*2);
	GPIOA -> PUPDR |= (2U << 9*2);
}

void setInterruptForKeypad(){
	// C1 -> PB8
	EXTI -> EXTICR[2] |= (1U << 0*8);

	// C2 -> PB2
	EXTI -> EXTICR[0] |= (1U << 2*8);

	// C3 -> PB0
	EXTI -> EXTICR[0] |= (1U << 0*8);

	// C4 -> PA9
	EXTI -> EXTICR[2] |= (0U << 1*8);

	EXTI -> RTSR1 |= (1U << 9);
	EXTI -> RTSR1 |= (1U << 0);
	EXTI -> RTSR1 |= (1U << 2);
	EXTI -> RTSR1 |= (1U << 8);

	EXTI -> IMR1 |= (1U << 9);
	EXTI -> IMR1 |= (1U << 0);
	EXTI -> IMR1 |= (1U << 2);
	EXTI -> IMR1 |= (1U << 8);

	NVIC_SetPriority(EXTI0_1_IRQn, 0);
	NVIC_EnableIRQ(EXTI0_1_IRQn);

	NVIC_SetPriority(EXTI2_3_IRQn, 0);
	NVIC_EnableIRQ(EXTI2_3_IRQn);

	NVIC_SetPriority(EXTI4_15_IRQn, 0);
	NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void clearAllKeypadRows() {
	GPIOB -> ODR &= ~((0x10U));
	GPIOB -> ODR &= ~((0x20U));
	GPIOB -> ODR &= ~((0x200U));
	GPIOB -> ODR &= ~((0x100U));
}

void setAllKeypadRows() {
	GPIOB -> ODR |= ((uint16_t) (0x10));
	GPIOB -> ODR |= ((uint16_t) (0x20));
	GPIOB -> ODR |= ((uint16_t) (0x200));
	GPIOB -> ODR |= ((uint16_t) (0x100));
}

keypadBut_t detectButton() {
	clearAllKeypadRows();
	keypadBut_t button = none;

	// sadece R1 aÃ§Ä±k
	setKeypadRow(1);
	if(GPIOB -> IDR & ((uint16_t) (0x100))) {
		//1
		button = keypadBut1;
	} else if(GPIOB -> IDR & ((uint16_t) (0x4))) {
		//2
		button = keypadBut2;
	} else if(GPIOB -> IDR & ((uint16_t) (0x1))) {
		//3
		button = keypadBut3;
	} else if(GPIOA -> IDR & ((uint16_t) (0x200))) {
		//A
		button = keypadButA;
	}

	// sadece R2 aÃ§Ä±k
	setKeypadRow(2);
	if(GPIOB -> IDR & ((uint16_t) (0x100))) {
		//4
		button = keypadBut4;
	} else if(GPIOB -> IDR & ((uint16_t) (0x4))) {
		//5
		button = keypadBut5;
	} else if(GPIOB -> IDR & ((uint16_t) (0x1))) {
		//6
		button = keypadBut6;
	} else if(GPIOA -> IDR & ((uint16_t) (0x200))) {
		//B
		button = keypadButB;
	}

	// sadece R3 aÃ§Ä±k
	setKeypadRow(3);
	if(GPIOB -> IDR & ((uint16_t) (0x100))) {
		//7
		button = keypadBut7;
	} else if(GPIOB -> IDR & ((uint16_t) (0x4))) {
		//8
		button = keypadBut8;
	} else if(GPIOB -> IDR & ((uint16_t) (0x1))) {
		//9
		button = keypadBut9;
	} else if(GPIOA -> IDR & ((uint16_t) (0x200))) {
		//C
		button = keypadButC;
	}

	// sadece R4 aÃ§Ä±k
	setKeypadRow(4);
	if(GPIOB -> IDR & ((uint16_t) (0x100))) {
		//*
		button = keypadButAst;
	} else if(GPIOB -> IDR & ((uint16_t) (0x4))) {
		//0
		button = keypadBut0;
	} else if(GPIOB -> IDR & ((uint16_t) (0x1))) {
		//#
		button = keypadButHash;
	} else if(GPIOA -> IDR & ((uint16_t) (0x200))) {
		//D
		button = keypadButD;
	}

	setAllKeypadRows();

	return button;
}

void setKeypadRow(uint8_t key) {
	clearAllKeypadRows();

	switch(key){
	case 1:
		GPIOB -> ODR |= ((uint16_t) (0x10));
		break;
	case 2:
		GPIOB -> ODR |= ((uint16_t) (0x20));
		break;
	case 3:
		GPIOB -> ODR |= ((uint16_t) (0x200));
		break;
	case 4:
		GPIOB -> ODR |= ((uint16_t) (0x100));
		break;
	default:

		break;
	}
}
