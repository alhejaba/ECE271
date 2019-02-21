;********************************************************************************************************
; file:     main.c
; author:   xxxx, your-email@maine.edu
; date:     mmm-dd-2015
; version:  1.0
; compiler: MDK 5.12
; note:     Warning: L6314W: No section matches pattern *(InRoot$$Sections).
;           It is because this program does not execute the compiler's basic run-time support library. 
; hardware: Discovery kit with STM32L152RCT6 MCU
; description: xxxx
;********************************************************************************************************

;********************************************************************************************************
; STM32L1 Discovery Kit Pin Connections (STM32L152RBT6 or STM32L152RCT6)
;  USER Pushbutton  <------>  PA.0 (clock: RCC_AHBENR_GPIOAEN)
;  RESET Pushbutton <------>  RESET
;  Green LED (LD3)  <------>  PB.7 (clock: RCC_AHBENR_GPIOBEN)
;  Blue LED (LD4)   <------>  PB.6 (clock: RCC_AHBENR_GPIOBEN)
;  Touch Sensors    <------>  6 pins, PA.6,7 (group 2), PB.0,1 (group 3), PC.4,5 (group 9)
;  LCD (24 segments)<------>  28 pins, PA.1,2,3,8,9,10,15, 
;                                      PB.3,4,5,8,9,10,11,12,13,14,15
;                                      PC.0,1,2,3,6,7,8,9,10,11 
;  ST Link          <------>  PA.13,14
;  Boot 1           <------>  PB.2
;  Freely available pins: PA.5, PA.11, PA.12, PC.12, PD.2 
;  A GPIO pin is 5V tolerant and can sink or source up to 8 mA
;********************************************************************************************************


		INCLUDE stm32l1xx_constants.s       ; Load Constant Definitions
		INCLUDE stm32l1xx_tim_constants.s   ; TIM Constants

;********************************************************************************************************
;                                      CODE AREA
;********************************************************************************************************
		AREA main, CODE, READONLY
		EXPORT __main                       ; make __main visible to linker
		ENTRY


;********************************************************************************************************
;                                      MAIN FUNCTION
; Description  : xxxxxx
; C prototype  : void main (void)
; Note         : Has a dead loop and never exit
; Argument(s)  : none
; Return value : none
;********************************************************************************************************
__main	PROC

		LDR  r0, =array

stop	B    stop                         ; dead loop & program hangs here

		ENDP
		ALIGN

;********************************************************************************************************
;                                      DATA AREA
;********************************************************************************************************
		AREA myData, DATA, READWRITE
		ALIGN
array	DCD 1, 2, 3, 4

;********************************************************************************************************
;                                      ASSEMBLY FILE END
;********************************************************************************************************
		END
