/*
*********************************************************************************************************
* file:     main.c
* author:   xxxx, your-email@maine.edu
* date:     mmm-dd-2015
* version:  1.0
* compiler: MDK 5.12
* hardware: Discovery kit with STM32L152RCT6 MCU
* description: xxxx
*********************************************************************************************************
*/

#include "stm32l1xx.h"
#include "core_cm3.h"

/*
*********************************************************************************************************
* STM32L1 Discovery Kit Pin Connections (STM32L152RBT6 or STM32L152RCT6)
*  USER Pushbutton  <------>  PA.0 (clock: RCC_AHBENR_GPIOAEN)
*  RESET Pushbutton <------>  RESET
*  Green LED (LD3)  <------>  PB.7 (clock: RCC_AHBENR_GPIOBEN)
*  Blue LED (LD4)   <------>  PB.6 (clock: RCC_AHBENR_GPIOBEN)
*  Touch Sensors    <------>  6 pins, PA.6,7 (group 2), PB.0,1 (group 3), PC.4,5 (group 9)
*  LCD (24 segments)<------>  28 pins, PA.1,2,3,8,9,10,15, 
*                                      PB.3,4,5,8,9,10,11,12,13,14,15
*                                      PC.0,1,2,3,6,7,8,9,10,11 
*  ST Link          <------>  PA.13,14
*  Boot 1           <------>  PB.2
*  Freely available pins: PA.5, PA.11, PA.12, PC.12, PD.2 
*  A GPIO pin is 5V tolerant and can sink or source up to 8 mA
*********************************************************************************************************
*/


/**
  * @brief  xxxxxx
  * @note   Has a dead loop and never exit
  * @param  None
  * @retval None
  */
int main(void){

	// Enable the clock to GPIO Port B	
	RCC->AHBENR		|= 0x00000002;   

	GPIOB->MODER  &= ~(0x03<<(2*6)) ;   // Clear bit 13 and bit 12

	// Dead loop & program hangs here
	while(1);
}


