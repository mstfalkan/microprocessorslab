
#ifndef BSP_H_
#define BSP_H_
#include "stm32g0xx.h"
#include <math.h>


enum states {	MOD0 = 0, MOD1 = 1000, MOD2 = 500, MOD3 = 100, MOD4 = 10,
						MOD5 = 1	};

void BSP_systemInit();

void BSP_initializeOnBoardLed();
void BSP_setOnBoardLed();
void BSP_resetOnBoardLed();
void BSP_toggleOnBoardLed();

void BSP_initializeAndConfigClock();
void BSP_initializeAndConfigSysTickTimer(uint32_t );
void SysTick_Handler();

void BSP_initializeButton();
void BSP_initializeInterruptForButton();

void BSP_Timer3_Config(uint32_t);
void BSP_Timer2_Config();

void resetAllSSDDigits();
void setSSDDigit(uint8_t );
void dispNumberDigitInSSD(uint8_t , uint8_t);
void setMODERForSSD();
void delay(volatile uint32_t);
void setRCCForSSD();
void setMODERForSSD();

void setRCCForKeypad();
void setMODERForKeypad();
void setInterruptForKeypad();
void clearAllKeypadRows();
void setAllKeypadRows();
void setKeypadRow(uint8_t);

#endif /* BSP_H_ */
