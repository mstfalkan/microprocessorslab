#include "stm32g0xx.h"
#include "bsp.h"

#define LEDDELAY    1600000
void delay(volatile uint32_t);

int main(void) {

	system_init();


	while(1){
/*		GPIOA->BRR |= (1U << 15);	//D4
		GPIOB->BRR |= (1U << 4);	//D1
		GPIOB->BRR |= (1U << 5);	//D2
		GPIOB->BRR |= (1U << 3);	//d3
		setSSD(10);
		delay(LEDDELAY);
		GPIOA->BRR |= (1U << 15);	//D4
		GPIOB->BRR |= (1U << 4);	//D1
		GPIOB->BRR |= (1U << 5);	//D2
		GPIOB->BRR |= (1U << 3);	//d3
		setSSD(14);
		delay(LEDDELAY);
*/
	}




 return 0;

}
void delay(volatile uint32_t s){
	for(; s>0; s--);

}


/*
void delay_ms(volatile unsigned int s){
for(int i=s; i>0; i--){
SysTick_Config(SystemCoreClock / 1000);
}
}
*/
