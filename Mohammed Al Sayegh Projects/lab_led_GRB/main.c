/*
*********************************************************************************************************
* file:     main.c
* author:   Mohammed H. Al-Sayegh
* date:     04/30/2015
* version:  1.0
* compiler: MDK 5.12
* hardware: Discovery kit with STM32L152RCT6 MCU
* description: RGB LED
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
//
typedef uint8_t   int8bit;
typedef uint16_t  int16bit;


void HSI_Init(void);
void GPIO_Init(void);
void setcolor(int color);


int i,k,j;
const double a = 1;
const int color1 = 0xF;
//const int color2 = 0xF;
//const int color3 = 0xF;
//const int color4 = 0xF;

int main(void){
	
	// start configuration
	
	HSI_Init();
	GPIO_Init();
	
	//Function setcolor, there are 7 cases
	//csae 0: is off
	//csae 1: is the green
	//csae 2: is the red
	//csae 3: is the blue
	//csae 4: is the green and red
	//csae 5: is the red and blue
	//csae 6: is green, red and blue which equial to white

			setcolor(0);
			setcolor(2);
			setcolor(2);
			setcolor(0);

}

void HSI_Init(void){
	//Set system clock as HSI to 16 MHz
	RCC->CR				|= RCC_CR_HSION;
	RCC->CFGR			&= ~RCC_CFGR_SW;
	RCC->CFGR			|= RCC_CFGR_SW_HSI;
	while((RCC->CR & (RCC_CR_HSIRDY)) != RCC_CR_HSIRDY);
}
void GPIO_Init(void){
	//configuration of set the output pin for the signial
	RCC->AHBENR		|=	RCC_AHBENR_GPIOBEN;
	RCC->AHBENR		|=	RCC_AHBENR_GPIOAEN;

	GPIOB->MODER	&=	~(GPIO_MODER_MODER6);
	GPIOB->MODER	|=	GPIO_MODER_MODER6_0;		
	GPIOB->OSPEEDR |=	GPIO_OSPEEDER_OSPEEDR6;
	GPIOB->PUPDR	&=	~GPIO_PUPDR_PUPDR6;
	GPIOB->OTYPER	&=	~GPIO_OTYPER_OT_6;
	
	//GPIOA	
	GPIOA->MODER  &= ~(0x03) ;   // set PA0 and PA1 as Input
	GPIOA->PUPDR 	&= ~(0x03) ;   // set PA0 and PA1 as No Pull-up No Pull-down		
}


void setcolor(int color)
{
	switch(color){
	
		case 1:
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		break;
	  //-------------------------------------------------------------
		case 2:

		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}

		break;
    //-------------------------------------------------------------
		case 3:

		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		
		break;
		//-------------------------------------------------------------
		case 4:
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		
		break;
		//-------------------------------------------------------------
		case 5:
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}

		break;
		//-------------------------------------------------------------
		case 6:

		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				for(k = 0; k<1;k++);
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		//-------------------------------------------------------------
		case 0:

		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		for(i = 0; i<8; i++)
		{
				GPIOB->ODR = GPIO_OTYPER_ODR_6;
				GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		}
		
		break;	
	  }

		/*
			//-----------------------------------------------
	
	//Bit 0:
	if(color1 && (0x01))
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	//for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}

	//-----------------------------------------------
	
	//Bit 1:
	if((color1<<1) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}	

	//-----------------------------------------------
	
	//Bit 2:
	if((color1<<2) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}	
	
	//-----------------------------------------------
	
	//Bit 3:
	if((color1<<3) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 4:
	if((color1<<4) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 5:
	if((color1<<5) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 6:
	if((color1<<6) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 7:
	if((color1<<0x7) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 8:
	if((color1<<0x8) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 9:
	if((color1<<9) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 10:
	if((color1<<10) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 11:
	if((color1<<11) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
		
	//-----------------------------------------------
	
	//Bit 12:
	if((color1<<12) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 13:
	if((color1<<0x13) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 14:
	if((color1<<14) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 15:
	if((color1<<15) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 16:
	if((color1<<16) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 17:
	if((color1<<0x17) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 18:
	if((color1<<18) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}

	//-----------------------------------------------
	
	//Bit 19:
	if((color1<<19) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 20:
	if((color1<<20) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 21:
	if((color1<<21) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 22:
	if((color1<<22) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	//-----------------------------------------------
	
	//Bit 23:
	if((color1<<23) &&0x01)
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	for(k = 0; k<1;k++);
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	else
	{
	GPIOB->ODR = GPIO_OTYPER_ODR_6;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
	}
	
	
	}*/

}
