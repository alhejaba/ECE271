#include <stdint.h>

//******************************************************************************************
//* The following definitions are copied from stm32l1xx.h 
//******************************************************************************************

#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

//Reset and Clock Control
typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t ICSCR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t AHBRSTR;
  __IO uint32_t APB2RSTR;
  __IO uint32_t APB1RSTR;
  __IO uint32_t AHBENR;
  __IO uint32_t APB2ENR;
  __IO uint32_t APB1ENR;
  __IO uint32_t AHBLPENR;
  __IO uint32_t APB2LPENR;
  __IO uint32_t APB1LPENR;      
  __IO uint32_t CSR;    
} RCC_TypeDef;

// General Purpose IO
typedef struct
{
  __IO uint32_t MODER;
  __IO uint16_t OTYPER;
  uint16_t RESERVED0;
  __IO uint32_t OSPEEDR;
  __IO uint32_t PUPDR;
  __IO uint16_t IDR;
  uint16_t RESERVED1;
  __IO uint16_t ODR;
  uint16_t RESERVED2;
  __IO uint16_t BSRRL; /* BSRR register is split to 2 * 16-bit fields BSRRL */
  __IO uint16_t BSRRH; /* BSRR register is split to 2 * 16-bit fields BSRRH */
  __IO uint32_t LCKR;
  __IO uint32_t AFR[2];
} GPIO_TypeDef;

#define  RCC_AHBENR_GPIOBEN   ((uint32_t)0x00000002) /*!< GPIO port B clock enable */

// Peripheral memory map
#define FLASH_BASE            ((uint32_t)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE             ((uint32_t)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */
#define SRAM_BB_BASE          ((uint32_t)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        ((uint32_t)0x42000000) /*!< Peripheral base address in the bit-band region */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define RCC_BASE              (AHBPERIPH_BASE + 0x3800)
#define RCC                   ((RCC_TypeDef *) RCC_BASE)

#define GPIOA_BASE            (AHBPERIPH_BASE + 0x0000)
#define GPIOB_BASE            (AHBPERIPH_BASE + 0x0400)
#define GPIOC_BASE            (AHBPERIPH_BASE + 0x0800)
#define GPIOD_BASE            (AHBPERIPH_BASE + 0x0C00)
#define GPIOE_BASE            (AHBPERIPH_BASE + 0x1000)
#define GPIOH_BASE            (AHBPERIPH_BASE + 0x1400)

#define GPIOA                 ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB                 ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC                 ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD                 ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE                 ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOH                 ((GPIO_TypeDef *) GPIOH_BASE)
