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
; Description  : PWM coding using assabmble
; C prototype  : void main (void)
; Note         : Has a dead loop and never exit
; Argument(s)  : none
; Return value : none
;********************************************************************************************************
__main	PROC

		
		;Configuration timer for GPIO A,B,C
		;Sitting of timmer
		LDR r7, =RCC_BASE
		LDR r1, [r7, #RCC_AHBENR]	 ; r1 = RCC->AHBENR
		ORR r1, r1, #RCC_AHBENR_GPIOAEN		 ; set bit 2 of AHBENR
		ORR r1, r1, #RCC_AHBENR_GPIOBEN		 ; set bit 2 of AHBENR
		ORR r1, r1, #RCC_AHBENR_GPIOCEN		 ; set bit 2 of AHBENR
		STR r1, [r7, #RCC_AHBENR]	 ; GPIO port B clock enable

		; Set pin 6 I/O direction as General-purpose Output

		LDR r7, =GPIOB_BASE			 ; Load GPIO port B base address
		LDR r1, [r7, #GPIO_MODER]	 ; r1 = GPIOB->MODER
		BIC r1, r1, #(0x03 << 12)	 ; Set mode as 0b01
		ORR r1, r1, #(0x02 << 12)
		STR r1, [r7, #GPIO_MODER]	 ; Save the mode

		; Set pin 7 I/O direction as General-purpose Output

		LDR r7, =GPIOB_BASE			 ; Load GPIO port B base address
		LDR r1, [r7, #GPIO_MODER]	 ; r1 = GPIOB->MODER
		BIC r1, r1, #GPIO_MODER_MODER7	 ; Set mode as 0b01
		ORR r1, r1, #GPIO_MODER_MODER7_1
		STR r1, [r7, #GPIO_MODER]	 ; Save the mode
		
		; Set pin 6 the push-pull mode for the output type
		
		LDR r1, [r7, #GPIO_OTYPER]	 ; r1 = GPIOB->OTYPER
		BIC r1,  r1, #(GPIO_OTYPER_IDR_6)		; Push-pull(0, reset)
		STR r1, [r7, #GPIO_OTYPER]	 ; Save output type

		; Set pin 7 the push-pull mode for the output type
		
		LDR r1, [r7, #GPIO_OTYPER]	 ; r1 = GPIOB->OTYPER
		BIC r1,  r1, #(GPIO_OTYPER_IDR_7)		; Push-pull(0, reset)
		STR r1, [r7, #GPIO_OTYPER]	 ; Save output type
		
		; Set I/O output Speed  value as 2Mhz
		
		LDR r1, [r7, #GPIO_OSPEEDR] ; r1 = GPIOB->GPIO_OSPEEDER ; r1 = GPIOB->OSPEEDER
		BIC r1, r1, #(0x03<<12)		 ; Speed mask for bit 6
		ORR r1, r1, #(0x03<<12)		 ; 400KHz (00), 2Mhz (01), 10MHz (10), 40Mhz (11)
		STR r1, [r7, #GPIO_OSPEEDR] ; Save ouput speed

		; Set I/O output Speed  value as 2Mhz
		
		LDR r1, [r7, #GPIO_OSPEEDR] ; r1 = GPIOB->GPIO_OSPEEDER ; r1 = GPIOB->OSPEEDER
		BIC r1, r1, #(0x03<<14)		 ; Speed mask for bit 6
		ORR r1, r1, #(0x03<<14)		 ; 400KHz (00), 2Mhz (01), 10MHz (10), 40Mhz (11)
		STR r1, [r7, #GPIO_OSPEEDR] ; Save ouput speed
		
		; Set I/O AFR Alternative Function
		
		LDR r1, [r7, #GPIO_AFR0]	 ; r1 = GPIOB->AFR[0]
		BIC r1, r1, #(GPIO_AFRL_AFRL6) 	 ; PUPDR mask for bit6 : set to zero
		ORR r1, r1, #(0x02<<24)		 ; 400KHz (00), 2Mhz (01), 10MHz (10), 40Mhz (11)
		STR r1, [r7, #GPIO_AFR0]	 ; Save AFR0 setting

		; Set I/O AFR Alternative Function
		
		LDR r1, [r7, #GPIO_AFR0]	 ; r1 = GPIOB->AFR[0]
		BIC r1, r1, #(GPIO_AFRL_AFRL7) 	 ; PUPDR mask for bit6 : set to zero
		ORR r1, r1, #(0x02<<28)		 ; 400KHz (00), 2Mhz (01), 10MHz (10), 40Mhz (11)
		STR r1, [r7, #GPIO_AFR0]	 ; Save AFR0 setting


		; Set I/O as no pull-up no pull-down
		
		LDR r1, [r7, #GPIO_PUPDR]	 ; r1 = GPIOB->PUPDR
		BIC r1, r1, #(GPIO_PUPDR_PUPDR6) 	 ; PUPDR mask for bit6 : set to zero
		STR r1, [r7, #GPIO_PUPDR]	 ; Save pull-up and pull-down setting
	
		; Set I/O as no pull-up no pull-down
		
		LDR r1, [r7, #GPIO_PUPDR]	 ; r1 = GPIOB->PUPDR
		BIC r1, r1, #(GPIO_PUPDR_PUPDR7) 	 ; PUPDR mask for bit6 : set to zero
		STR r1, [r7, #GPIO_PUPDR]	 ; Save pull-up and pull-down setting
	
		;Enable clock on timer 4
		
		LDR r7, =RCC_BASE
		LDR r0, [r7, #RCC_APB1ENR]
		BIC r0, r0, #RCC_APB1ENR_TIM4EN
		ORR r0, r0, #RCC_APB1ENR_TIM4EN
		STR r0, [r7, #RCC_APB1ENR]
		LDR r7, =TIM4_BASE
		
		;set the prescaler
		
		LDR r0, [r7, #TIM_PSC]
		LDR r1, =TIM_PSC_PSC
		BIC r0, r0, r1
		STR r0, [r7, #TIM_PSC]

		;set auto-reload value
		
		LDR r0, [r7, #TIM_ARR]
		LDR r1, =TIM_ARR_ARR
		BIC r0, r0, r1
		ORR r0, r0, #199
		STR r0, [r7, #TIM_ARR] ;counts from 0 to 199 (200 steps)
		
		;Set PWM mode on channel 1
		
		LDR r0, [r7, #TIM_CCMR1]
		BIC r0, r0, #TIM_CCMR1_OC1M
		ORR r0, r0, #TIM_CCMR1_OC1M_2
		ORR r0, r0, #TIM_CCMR1_OC1M_1

		;Enable output preload on channel 1
		
		BIC r0, r0, #TIM_CCMR1_OC1PE
		ORR r0, r0, #TIM_CCMR1_OC1PE
		STR r0, [r7, #TIM_CCMR1]

		;Enable auto-reload preload on channel 1
		
		LDR r0, [r7, #TIM_CR1]
		BIC r0, r0, #TIM_CR1_ARPE
		ORR r0, r0, #TIM_CR1_ARPE
		STR r0, [r7, #TIM_CR1]
		
		;Enable output on channel 1
		
		LDR r0, [r7, #TIM_CCER]
		ORR r0, r0, #TIM_CCER_CC1E
		STR r0, [r7, #TIM_CCER]
		
		;Enable outut compare register for channel 1

		LDR r0, [r7, #TIM_CCR1]
		LDR r1, =TIM_CCR1_CCR1
		BIC r0, r0, r1
		ORR r0, r0, #0XFF
		STR r0, [r7, #TIM_CCR1]

		;Enable counter in channel 1
		
		LDR r0, [r7, #TIM_CR1]
		ORR r0, r0, #TIM_CR1_CEN
		STR r0, [r7, #TIM_CR1]	
		
		;LDR r0,
		
		MOV r5, #1
		MOV r6, #1
		
point_a	MOV r3, #0					 ; i
		MOV r4, #0					 ; sum
		MOV r8, #0

		CMP r5, #200
		BGE point_c
point_b CMP r5, #0
		BEQ point_c
		B point_d
point_c RSB	r6, r6, #0
point_d ADD r5, r5, r6

		;Enable outut compare register for channel 1

		LDR r0, [r7, #TIM_CCR1]
		LDR r1, =TIM_CCR1_CCR1
		BIC r0, r0, r1
		ORR r0, r0, r5
		STR r0, [r7, #TIM_CCR1]

		
			
loop 	ADD r4, r4, r3
		ADD r3, r3, #1
        CMP r3, #1000
		BLT loop
endloop
				

		B point_a		
		
		;CMP r5, #199
    	;BEQ then
		;BNE Pass
;then	MOV r6, #1
		
		
		;CMP r5, #0
		;BEQ flop
;flop	MOV r6, #0

;pass
		;ADD r5, #1
	    ;SUB




stop	B    stop                         ; dead loop & program hangs here

		ENDP
		ALIGN

;********************************************************************************************************
;                                      DATA AREA
;********************************************************************************************************
		AREA myData, DATA, READWRITE
		ALIGN
;array	DCD 1, 2, 3, 4

;********************************************************************************************************
;                                      ASSEMBLY FILE END
;********************************************************************************************************
		END
