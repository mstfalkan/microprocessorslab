#include "stm32g0xx.h"
#include <math.h>
#include "bsp.h"

int button;
void delay(volatile uint32_t);
volatile int counter = 0;
int buttonx[4];

void EXTI0_1_IRQHandler() {
	button = detectButton();
	EXTI -> RPR1 |= (1 << 0);
}

void EXTI2_3_IRQHandler() {
		button = detectButton();
		EXTI -> RPR1 |= (1 << 2);
}

void EXTI4_15_IRQHandler() {
	//Burda Ã¶nce A mÄ± B mi ona bakacaz
	button = detectButton();
	EXTI -> RPR1 |= (1 << 8);
	EXTI -> RPR1 |= (1 << 9);
}



int main(void) {
	BSP_systemInit();

	int genlik,freq;
	button = detectButton();
	if(button==10){

		genlik = number();
		init_pwm2();
		while(1){
			for(int i=0; i<258; i++){
			    		TIM2->CCR2 = i;
			    		setting1();
			    }
		}


	}
	else if(button==11){
		freq = number();

		init_pwm2();
		TIM2->PSC = (3200/freq)-1;
		setting();
	}

    return 0;
}

int number(void){
	int i=0;
	int j;
	button = -1;
	for( i = 1 ; i < 5 ; i++){
		button = detectButton();
	if(button == 0 || button == 1 || button == 2 || button == 3 || button == 4 || button == 5 || button == 6 || button == 7 || button == 8 || button == 9 || button == 10 || button == 11|| button == 12 || button == 13 || button == 14 || button == 15){
			buttonx[i-1] = detectButton();
			delay(1000000);
			dispNumberDigitInSSD((uint8_t) button, (uint8_t) i );
			delay(1000000);
			button = -1;
			if(buttonx[i] == 14){
				goto a1;
			}
	}
	}
			if(i >= 4){

		for(j = 1; j < 5; j++){
						dispNumberDigitInSSD((uint8_t) buttonx[j], (uint8_t) j );
						delay(1000);

		}
		}
 a1:
	return ((buttonx[0] * 10^0) + (buttonx[1] * 10^1) + (buttonx[2] * 10^2) + (buttonx[3] * 10^3));
}

void setting(){
	while(1){
		int j;
		for(j = 1; j < 5; j++){
						dispNumberDigitInSSD((uint8_t) buttonx[j], (uint8_t) j );
						delay(1000);
		}
	}
}
void setting1(){

		int j;
		for(j = 1; j < 5; j++){
						dispNumberDigitInSSD((uint8_t) buttonx[j], (uint8_t) j );
						delay(1000);
	}
}
