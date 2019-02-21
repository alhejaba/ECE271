/*
*********************************************************************************************************
* file:     main.c
* author:   Mohammed Al-Sayegh, mohammed.h.alsayegh@maine.edu
* date:     1-20-2015
* version:  1.0
* compiler: MDK 5.12
* hardware: Discovery kit with STM32L152RCT6 MCU
* description: The flash bouncing LED when press
*********************************************************************************************************
*/

#include "stm32l1xx.h"

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

void command()
{
	int i;

	while(1){
		if ((GPIOA->IDR & (0x01)))
     {
			GPIOB->ODR ^= GPIO_OTYPER_ODR_6;					 
			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;				
			 
			for(i = 0; i<60000; i++); //A short delay
 			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;	
			 
			for(i = 0; i<60000; i++); //A short delay
			GPIOB->ODR ^=GPIO_OTYPER_ODR_6;					 
			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;	
			
			for(i = 0; i<60000; i++); //A short delay
 			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;	
			 
			for(i = 0; i<60000; i++); //A short delay
			GPIOB->ODR ^= GPIO_OTYPER_ODR_6;					 
			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;
			 
						GPIOB->ODR ^= GPIO_OTYPER_ODR_6;					 
			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;				
			 
			for(i = 0; i<60000; i++); //A short delay
 			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;	
			 
			for(i = 0; i<60000; i++); //A short delay
			GPIOB->ODR ^=GPIO_OTYPER_ODR_6;					 
			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;	
			
			for(i = 0; i<60000; i++); //A short delay
 			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;	
			 
			for(i = 0; i<60000; i++); //A short delay
			GPIOB->ODR ^= GPIO_OTYPER_ODR_6;					 
			GPIOB->ODR ^= GPIO_OTYPER_ODR_7;	
			}
     }
}

void configuration()
{
	RCC->AHBENR  |= 0x00000003;   
	
	//GPIOB
	
	GPIOB->MODER &= ~(GPIO_MODER_MODER6);
	GPIOB->MODER &= ~(GPIO_MODER_MODER7);

	GPIOB->MODER |= GPIO_MODER_MODER6_0;
	GPIOB->MODER |= GPIO_MODER_MODER7_0;
	
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_6);
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_7);

	GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR6);
	GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR7);
	
	GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR6_1);
	GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR7_1);

		
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR6);
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR7);

			
	//GPIOA
		
	GPIOA->MODER  &= ~(0x0F) ;   // set PA0 and PA1 as Input
	
	GPIOA->PUPDR 	&= ~(0x0F) ;   // set PA0 and PA1 as No Pull-up No Pull-down			
}

int main(void){
	
	// Enable the clock to GPIO Port B	
	configuration();
	command();
}


