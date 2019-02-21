/*
*********************************************************************************************************
* file:     main.c
* author:   Mohammed H. Al-Sayegh, mohammed.h.alsayegh@maine.edu
* date:     01-23-2015
* version:  1.0
* compiler: MDK 5.12
* hardware: Discovery kit with STM32L152RCT6 MCU
* description: This Code print sting santance with time delay after finish print last name access memory  
*********************************************************************************************************
*/

#include "stm32l1xx.h"
#include <stdint.h>
#include <stdio.h>

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


#define bool _Bool

void LCD_Clock_Init(void);
void LCD_PIN_Init(void);
void LCD_Configure(void);
void LCD_Clear(void);
void LCD_DisplayString(uint8_t* ptr);
void LCD_bar(void);
void LCD_WriteChar(uint8_t* ch, bool point, bool colon, uint8_t position);
static void LCD_Conv_Char_Seg(uint8_t* c, bool point, bool colon, uint8_t* digit);
void LCD_Display_Name(void);
void GPIO_Pin_Init();
void DO();

// LCD_Clock_Init() is provided to you for both Lab Part 1 and Part 2.
void LCD_Clock_Init(void){
  // Note from STM32L Reference Manual:   
  // After reset, the RTC Registers (RTC registers and RTC backup registers) are protected
  // against possible stray write accesses. To enable access to the RTC Registers, proceed as
  // follows:
  // 1. Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR register.
  // 2. Set the DBP bit in the PWR_CR register (see Section 4.4.1).
  // 3. Select the RTC clock source through RTCSEL[1:0] bits in RCC_CSR register.
  // 4. Enable the RTC clock by programming the RTCEN bit in the RCC_CSR register.
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;  // Power interface clock enable
  PWR->CR      |= PWR_CR_DBP;          // Disable Backup Domain write protection
  RCC->CSR      |= RCC_CSR_RTCSEL_LSI;  // LSI oscillator clock used as RTC clock
  //LSI clock varies due to frequency dispersion
  //RCC->CSR     |= RCC_CSR_RTCSEL_LSE;  // LSE oscillator clock used as RTC clock
  RCC->CSR     |= RCC_CSR_RTCEN;      // RTC clock enable
  
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;          // RTC write protection register (WPR)
  RTC->WPR = 0x53;          // Write "0xCA" and "0x53" to unlock the write protection
  
  // Wait until MSI clock ready
  while((RCC->CR & RCC_CR_MSIRDY) == 0); // MSI Ready Flag is set by hardware
  
  /* Enable comparator clock LCD */
  RCC->APB1ENR |= RCC_APB1ENR_LCDEN;
  
  /* Enable SYSCFG */
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  
  RCC->CSR |= RCC_CSR_LSION;
  while( (RCC->CSR & RCC_CSR_LSIRDY) == 0 );
  
  /* Select LSI as LCD Clock Source */
  RCC->CSR &= ~RCC_CSR_RTCSEL_LSI;  
  RCC->CSR |= RCC_CSR_RTCSEL_LSI;    // LSI oscillator clock used as RTC and LCD clock   
  RCC->CSR |= RCC_CSR_RTCEN;  
	
}

int main(void) {
  LCD_Clock_Init();
  LCD_PIN_Init();
  LCD_Configure();
	GPIO_Pin_Init();
	DO();
	
  while(1);
}

/**************************************************************************************/
/*    Lab Part 1: Display your name                                                   */
/**************************************************************************************/
// This part is to display the first characters of your last name on the LCD. 
void LCD_PIN_Init(void){  
  
	// Implement your code here
  RCC->AHBENR |= 0x07;

	//GPIOA, LCD Pin 1, 2, 3, 8, 9, 10, and 15
	
	//GPIOA->MODER  &= ~(0x7<<(2*13));
	GPIOA->MODER  |= (0x802A00A8);
	
	GPIOA->AFR[0] |= (0xBBB0); 
	GPIOA->AFR[1] |= (0xB0000BBB);
	
	GPIOA->OSPEEDR &= ~(0xFFFFFFFF);
	GPIOA->PUPDR &= ~(0xFFFFFFFF); // set it to zero
	GPIOA->OTYPER &= ~(0xFFFFFFFF); // set it to zero
	
	
	//GPIOB 

	GPIOB->MODER  &= ~(0xFFFFFFFF);
	
	GPIOB->MODER  |= (0x2A<<(2*3)) ;   // Clear pin 6 and 7
	GPIOB->MODER  |= (0xAAAA<<(2*8)) ;   // Clear pin 6 and 7
	
	
	GPIOB->AFR[0] |= ((0xBBB) << (4*3)); //Pin PB 6 as alternative function 2 (TIM4)
	
	GPIOB->AFR[1] |= (0xBBBBBBBB); //Pin PB 6 as alternative function 2 (TIM4)  

	GPIOB->OSPEEDR &= ~(0xFFFFFFFF);

	//GPIOC   
	
	GPIOC->MODER  &= ~(0xFFFFFFF);
	GPIOC->MODER  |= (0x00AAA0AA) ;
	
	//GPIOC->AFR[0] &= ~(0xFFFFFFF);
	//GPIOC->AFR[1] &= ~(0xFFFFFFF);
	
	GPIOC->AFR[0] |= (0xBB00BBBB); //Pin PB 6 as alternative function
	GPIOC->AFR[1] |= (0xBBBB); //Pin PB 6 as alternative function  
	
	GPIOC->OSPEEDR &= ~(0xFFFFFFFF);
	
}

void LCD_Configure(void) { 
  // Implement your code here
	LCD->CR |= (0x013)<<(2);
	LCD->FCR |= (0x03)<<(10);
	LCD->CR |= (0x01)<<(7);
	LCD->CR &= ~((0x01)<<(1));
	
	LCD->FCR |= 0x7<<4;
	
	while(1){
		if ((LCD->SR & ((0x01)<<5)))
		{
			LCD->CR |= (0x01);
			if ((LCD->CR & 0x01)){
		if ((LCD->SR & ((0x01)<<5))) break;
			}
		}
	}
	
}

void LCD_Display_Name(void){
  // Implement your code here
  // Note: your are required to program LCD_RAM directly. Therefore, you cannot use 
  // LCD_WriteChar() and LCD_Conv_Char_Seg();
	//int i;
	LCD->RAM[0] = 0x2C23FC86;
	LCD->RAM[2] = 0x3C3DB483;
	LCD->RAM[4] = 0x01000100;
	LCD->RAM[6] = 0x2000000;
	LCD->SR |= 0x01<<2;
	//for(i = 0; i<200000; i++); //A short delay
}

/**************************************************************************************/
/*    Lab Part 2: Generic Display Function                                            */
/**************************************************************************************/

void LCD_DisplayString(uint8_t* ptr) {
  // Implement your code here
  // You should use use LCD_WriteChar().
	
	LCD_WriteChar(ptr,0,0,1);
	LCD_WriteChar(ptr+1,0,0,2);
	LCD_WriteChar(ptr+2,0,0,3);
	LCD_WriteChar(ptr+3,0,0,4);
	LCD_WriteChar(ptr+4,0,0,5);
	LCD_WriteChar(ptr+5,0,0,6);
}

void LCD_Clear(void) {  
  // Implement your code here
}

/**************************************************************************************/
/*    The following definitions and functions are provide for you for Part 2          */
/**************************************************************************************/

/* Macros used for set/reset bar LCD bar */
#define BAR0_ON  t_bar[1] |= 8
#define BAR0_OFF t_bar[1] &= ~8
#define BAR1_ON  t_bar[0] |= 8
#define BAR1_OFF t_bar[0] &= ~8
#define BAR2_ON  t_bar[1] |= 2
#define BAR2_OFF t_bar[1] &= ~2
#define BAR3_ON  t_bar[0] |= 2 
#define BAR3_OFF t_bar[0] &= ~2 

/* code for 'µ' character */
#define C_UMAP 0x6084

/* code for 'm' character */
#define C_mMap 0xb210

/* code for 'n' character */
#define C_nMap 0x2210

/* constant code for '*' character */
#define star 0xA0DD

/* constant code for '-' character */
#define C_minus 0xA000

/* constant code for '/' */
#define C_slatch  0x00c0

/* constant code for ° */
#define C_percent_1 0xec00

/* constant code  for small o */
#define C_percent_2 0xb300

#define C_full 0xffdd

/* LCD BAR status: We don't write directly in LCD RAM for save the bar setting */
uint8_t t_bar[2]={0x0,0x0};
    
/*  =========================================================================
                                 LCD MAPPING
    =========================================================================
      A
     _  ----------
COL |_| |\   |J  /|
       F| H  |  K |B
     _  |  \ | /  |
COL |_| --G-- --M--
        |   /| \  |
       E|  Q |  N |C
     _  | /  |P  \|   
DP  |_| -----------  
      D         

 An LCD character coding is based on the following matrix:
      { E , D , P , N   }
      { M , C , COL , DP}
      { B , A , K , J   }
      { G , F , Q , H   }

 The character 'A' for example is:
  -------------------------------
LSB   { 1 , 0 , 0 , 0   }
      { 1 , 1 , 0 , 0   }
      { 1 , 1 , 0 , 0   }
MSB   { 1 , 1 , 0 , 0   }
      -------------------
  'A' =  F    E   0   0 hex

*/

/* Constant table for cap characters 'A' --> 'Z' */
const uint16_t CapLetterMap[26] = {
  /* A      B      C      D      E      F      G      H      I  */
  0xFE00,0x6714,0x1d00,0x4714,0x9d00,0x9c00,0x3f00,0xfa00,0x0014,
  /* J      K      L      M      N      O      P      Q      R  */
  0x5300,0x9841,0x1900,0x5a48,0x5a09,0x5f00,0xFC00,0x5F01,0xFC01,
  /* S      T      U      V      W      X      Y      Z  */
  0xAF00,0x0414,0x5b00,0x18c0,0x5a81,0x00c9,0x0058,0x05c0
};

/* Constant table for number '0' --> '9' */
const uint16_t NumberMap[10] = {
  /* 0      1      2      3      4      5      6      7      8      9  */
  0x5F00,0x4200,0xF500,0x6700,0xEa00,0xAF00,0xBF00,0x04600,0xFF00,0xEF00
};

void LCD_WriteChar(uint8_t* ch, bool point, bool colon, uint8_t position) {
  uint8_t digit[4];     /* Digit frame buffer */
   
  // Convert displayed character in segment in array digit 
  LCD_Conv_Char_Seg(ch, point, colon, digit);

  // Wait until LCD Ready */  
  while ((LCD->SR & LCD_SR_UDR) != 0); // Wait for Update Display Request Bit
  
  switch (position) {
    /* Position 1 on LCD (Digit 1)*/
    case 1:
      LCD->RAM[0] &= 0xcffffffc;
      LCD->RAM[2] &= 0xcffffffc;
      LCD->RAM[4] &= 0xcffffffc;
      LCD->RAM[6] &= 0xcffffffc;

      LCD->RAM[0] |= ((digit[0]& 0x0c) << 26 ) | (digit[0]& 0x03) ; // 1G 1B 1M 1E      
      LCD->RAM[2] |= ((digit[1]& 0x0c) << 26 ) | (digit[1]& 0x03) ; // 1F 1A 1C 1D 
      LCD->RAM[4] |= ((digit[2]& 0x0c) << 26 ) | (digit[2]& 0x03) ; // 1Q 1K 1Col 1P                                                                                                                                    
      LCD->RAM[6] |= ((digit[3]& 0x0c) << 26 ) | (digit[3]& 0x03) ; // 1H 1J 1DP 1N

      break;
    
    /* Position 2 on LCD (Digit 2)*/
    case 2:
      LCD->RAM[0] &= 0xf3ffff03;
      LCD->RAM[2] &= 0xf3ffff03;      
      LCD->RAM[4] &= 0xf3ffff03;
      LCD->RAM[6] &= 0xf3ffff03;
      
      LCD->RAM[0] |= ((digit[0]& 0x0c) << 24 )|((digit[0]& 0x02) << 6 )|((digit[0]& 0x01) << 2 ) ; // 2G 2B 2M 2E    
      LCD->RAM[2] |= ((digit[1]& 0x0c) << 24 )|((digit[1]& 0x02) << 6 )|((digit[1]& 0x01) << 2 ) ; // 2F 2A 2C 2D
      LCD->RAM[4] |= ((digit[2]& 0x0c) << 24 )|((digit[2]& 0x02) << 6 )|((digit[2]& 0x01) << 2 ) ; // 2Q 2K 2Col 2P
      LCD->RAM[6] |= ((digit[3]& 0x0c) << 24 )|((digit[3]& 0x02) << 6 )|((digit[3]& 0x01) << 2 ) ; // 2H 2J 2DP 2N
      
      break;
    
    /* Position 3 on LCD (Digit 3)*/
    case 3:
      LCD->RAM[0] &= 0xfcfffcff;
      LCD->RAM[2] &= 0xfcfffcff;
      LCD->RAM[4] &= 0xfcfffcff;
      LCD->RAM[6] &= 0xfcfffcff;

      LCD->RAM[0] |= ((digit[0]& 0x0c) << 22 ) | ((digit[0]& 0x03) << 8 ) ; // 3G 3B 3M 3E  
      LCD->RAM[2] |= ((digit[1]& 0x0c) << 22 ) | ((digit[1]& 0x03) << 8 ) ; // 3F 3A 3C 3D
      LCD->RAM[4] |= ((digit[2]& 0x0c) << 22 ) | ((digit[2]& 0x03) << 8 ) ; // 3Q 3K 3Col 3P
      LCD->RAM[6] |= ((digit[3]& 0x0c) << 22 ) | ((digit[3]& 0x03) << 8 ) ; // 3H 3J 3DP 3N
      
      break;
    
    /* Position 4 on LCD (Digit 4)*/
    case 4:
      LCD->RAM[0] &= 0xffcff3ff;
      LCD->RAM[2] &= 0xffcff3ff;
      LCD->RAM[4] &= 0xffcff3ff;
      LCD->RAM[6] &= 0xffcff3ff;
      
      LCD->RAM[0] |= ((digit[0]& 0x0c) << 18 ) | ((digit[0]& 0x03) << 10 ) ; // 4G 4B 4M 4E  
      LCD->RAM[2] |= ((digit[1]& 0x0c) << 18 ) | ((digit[1]& 0x03) << 10 ) ; // 4F 4A 4C 4D
      LCD->RAM[4] |= ((digit[2]& 0x0c) << 18 ) | ((digit[2]& 0x03) << 10 ) ; // 4Q 4K 4Col 4P
      LCD->RAM[6] |= ((digit[3]& 0x0c) << 18 ) | ((digit[3]& 0x03) << 10 ) ; // 4H 4J 4DP 4N
      
      break;
    
    /* Position 5 on LCD (Digit 5)*/
    case 5:
      LCD->RAM[0] &= 0xfff3cfff;
      LCD->RAM[2] &= 0xfff3cfff;
      LCD->RAM[4] &= 0xfff3efff;
      LCD->RAM[6] &= 0xfff3efff;

      LCD->RAM[0] |= ((digit[0]& 0x0c) << 16 ) | ((digit[0]& 0x03) << 12 ) ; // 5G 5B 5M 5E  
      LCD->RAM[2] |= ((digit[1]& 0x0c) << 16 ) | ((digit[1]& 0x03) << 12 ) ; // 5F 5A 5C 5D
      LCD->RAM[4] |= ((digit[2]& 0x0c) << 16 ) | ((digit[2]& 0x01) << 12 ) ; // 5Q 5K   5P 
      LCD->RAM[6] |= ((digit[3]& 0x0c) << 16 ) | ((digit[3]& 0x01) << 12 ) ; // 5H 5J   5N
      
      break;
    
    /* Position 6 on LCD (Digit 6)*/
    case 6:
      LCD->RAM[0] &= 0xfffc3fff;
      LCD->RAM[2] &= 0xfffc3fff;
      LCD->RAM[4] &= 0xfffc3fff;
      LCD->RAM[6] &= 0xfffc3fff;

      LCD->RAM[0] |= ((digit[0]& 0x04) << 15 ) | ((digit[0]& 0x08) << 13 ) | ((digit[0]& 0x03) << 14 ) ; // 6B 6G 6M 6E  
      LCD->RAM[2] |= ((digit[1]& 0x04) << 15 ) | ((digit[1]& 0x08) << 13 ) | ((digit[1]& 0x03) << 14 ) ; // 6A 6F 6C 6D
      LCD->RAM[4] |= ((digit[2]& 0x04) << 15 ) | ((digit[2]& 0x08) << 13 ) | ((digit[2]& 0x01) << 14 ) ; // 6K 6Q    6P 
      LCD->RAM[6] |= ((digit[3]& 0x04) << 15 ) | ((digit[3]& 0x08) << 13 ) | ((digit[3]& 0x01) << 14 ) ; // 6J 6H   6N
      
      break;
    
     default:
      break;
  }

  // Refresh LCD bar
  LCD_bar();

  // Update the LCD display
  // Set the Update Display Request.
  // Each time software modifies the LCD_RAM it must set the UDR bit to transfer the updated
  // data to the second level buffer. The UDR bit stays set until the end of the update and during
  // this time the LCD_RAM is write protected.
  LCD->SR |= LCD_SR_UDR; 
  while ((LCD->SR & LCD_SR_UDD) == 0);
}



// Setting bar on LCD, writes bar value in LCD frame buffer 
void LCD_bar(void) {
        
  LCD->RAM[4] &= 0xffff5fff;
  LCD->RAM[6] &= 0xffff5fff;
  
  /* bar 1, bar 3 */
  LCD->RAM[4] |= (uint32_t)(t_bar[0]<<12);
  
  /* bar 0, bar 2 */
  LCD->RAM[6] |= (uint32_t)(t_bar[1]<<12);
}

// Converts an ascii char to the a LCD digit
static void LCD_Conv_Char_Seg(uint8_t* c, bool point, bool colon, uint8_t* digit) {
  uint16_t ch = 0 ;
  uint8_t i,j;
  
  switch (*c) {
    case ' ' : 
      ch = 0x00;
      break;
    
    case '*':
      ch = star;
      break;
                  
    case '?':
      ch = C_UMAP;
      break;
    
    case 'm' :
      ch = C_mMap;
      break;
                  
    case 'n' :
      ch = C_nMap;
      break;          
                  
    case '-' :
      ch = C_minus;
      break;
      
    case '/' :
      ch = C_slatch;
      break;  
      
//  case '?':
//    ch = C_percent_1;
//    break;  

    case '%' :
      ch = C_percent_2; 
      break;
      
    case 255 :
      ch = C_full;
      break ;
    
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':      
      ch = NumberMap[*c-0x30];    
      break;
          
    default:
      /* The character c is one letter in upper case*/
      if ( (*c < 0x5b) && (*c > 0x40) ) {
        ch = CapLetterMap[*c - 'A'];
      }
      /* The character c is one letter in lower case*/
      if ( (*c <0x7b) && ( *c> 0x60) ) {
        ch = CapLetterMap[*c - 'a'];
      }
      break;
  }
       
  /* Set the digital point can be displayed if the point is on */
  if (point) {
    ch |= 0x0002;
  }

  /* Set the "COL" segment in the character that can be displayed if the colon is on */
  if (colon) {
    ch |= 0x0020;
  }    

  for (i = 12,j=0; j<4; i-=4,j++) {
    digit[j] = (ch >> i) & 0x0f; //To isolate the less signifiant dibit
  }
}

	void GPIO_Pin_Init()
	{
	//GPIOA
	GPIOA->MODER  &= ~(0x03) ;   // set PA0 and PA1 as Input
	GPIOA->PUPDR 	&= ~(0x03) ;   // set PA0 and PA1 as No Pull-up No Pull-down		
	}
	
	void DO()
	{
			while(1){
			int i;
			LCD_Display_Name();

			if ((GPIOA->IDR & (0x01)))
     {
			LCD_DisplayString("This");
			for(i = 0; i<400000; i++); //A short delay
		  			 
			 LCD_DisplayString("Class");
			for(i = 0; i<400000; i++); //A short delay
						 
			LCD_DisplayString("IS    ");
			for(i = 0; i<400000; i++); //A short delay
						 
			LCD_DisplayString("Cool");
			for(i = 0; i<400000; i++); //A short delay
		 }
	 }
	}
