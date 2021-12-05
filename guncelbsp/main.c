#include "stm32g0xx.h"
void delay_ms(volatile unsigned int);


int main(void) {

	system_init();
	timer1_init();

	for(;;);

	while(1){

	}


 return 0;
}
void delay_ms(volatile unsigned int s){
for(int i=s; i>0; i--){
SysTick_Config(SystemCoreClock / 1000);
}
}
