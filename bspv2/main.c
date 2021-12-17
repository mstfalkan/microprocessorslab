#include "stm32g0xx.h"
#include "bsp.h"

#define LEDDELAY    1600000
void delay(volatile uint32_t);

int main(void) {

	system_init();


	for(;;){

		print("Hello from lec9 ELEC334\n\r");
		delay(LEDDELAY);
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
