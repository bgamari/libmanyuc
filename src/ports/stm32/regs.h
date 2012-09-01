#pragma once

#include <stdint.h>
#include "core_cm3.h"

typedef struct {
  __IO uint32_t CR;
  __IO uint32_t CSR;
} PWR_TypeDef;

typedef struct {
  __IO uint32_t CR;
  __IO uint32_t PLLCFGR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t AHB1RSTR;
  __IO uint32_t AHB2RSTR;
  __IO uint32_t AHB3RSTR;
  uint32_t reserved1;
  __IO uint32_t APB1RSTR;
  __IO uint32_t APB2RSTR;
  uint32_t reserved2;
  uint32_t reserved3;
  __IO uint32_t AHB1ENR;
  __IO uint32_t AHB2ENR;
  __IO uint32_t AHB3ENR;
  uint32_t reserved4;
  __IO uint32_t APB1ENR;
  __IO uint32_t APB2ENR;
  uint32_t reserved5;
  uint32_t reserved6;
  __IO uint32_t AHB1LPENR;
  __IO uint32_t AHB2LPENR;
  __IO uint32_t AHB3LPENR;
  uint32_t reserved7;
  __IO uint32_t APB1LPENR;
  __IO uint32_t APB2LPENR;
  uint32_t reserved8;
  uint32_t reserved9;
  __IO uint32_t BDCR;
  __IO uint32_t CSR;
  uint32_t reserved10;
  uint32_t reserved11;
  __IO uint32_t SSCGR;
  __IO uint32_t PLLI2SCFGR;
} STM32_RCC_TypeDef;

const uint32_t RCC_CR_PLLRDY = 1<<25;
const uint32_t RCC_CR_PLLON  = 1<<24;
const uint32_t RCC_CR_HSERDY = 1<<17;
const uint32_t RCC_CR_HSEON  = 1<<16;

const uint32_t RCC_PLLCFGR_PLLSRC = 1<<22;

typedef struct {
  _IO uint32_t CR1;
  _IO uint32_t CR2;
  _IO uint32_t SMCR;
  _IO uint32_t DIER;
  _IO uint32_t SR;
  _O uint32_t EGR;
  _IO uint32_t CCMR1;
  _IO uint32_t CCMR2;
  _IO uint32_t CCER;
  _IO uint32_t CNT;
  _IO uint32_t PSC;
  _IO uint32_t ARR;
  _IO uint32_t RCR;
  _IO uint32_t CCR[4];
  _IO uint32_t BDTR;
  _IO uint32_t DCR;
  _IO uint32_t DMAR;
} STM32_TIM18_TypeDef;

typedef struct {
  __IO uint32_t MODER;
  __IO uint32_t OTYPER;
  __IO uint32_t OSPEEDER;
  __IO uint32_t PUPDR;
  __I uint32_t IDR;
  __IO uint32_t ODR;
  __O uint32_t BSSR;
  __IO uint32_t LCKR;
  __IO uint32_t AFRL;
  __IO uint32_t AFRH;
} STM32_GPIO_TypeDef;

typedef struct {
  __IO uint32_t SR;
  __IO uint32_t DR;
  __IO uint32_t BRR;
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t CR3;
  __IO uint32_t GTPR;
} STM32_USART_TypeDef;

typedef struct {
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SR;
  __IO uint32_t DR;
  __IO uint32_t CRCPR;
  __I uint32_t RXCRCR;
  __I uint32_t TXCRCR;
  __IO uint32_t I2SCFGR;
  __IO uint32_t I2SPR;
} STM32_SPI_TypeDef;

typedef struct {
  __I uint32_t LISR;
  __I uint32_t HISR;
  __IO uint32_t LIFCR;
  __IO uint32_t HIFCR;
  struct DMA_Stream_Regs {
    __IO uint32_t CR;
    __IO uint32_t DTR;
    __IO uint32_t PAR;
    __IO uint32_t M0AR;
    __IO uint32_t M1AR;
    __IO uint32_t FCR;
  } S[8];
} STM32_DMA_TypeDef;

typedef struct {
  __IO uint32_t SR;
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SMPR1;
  __IO uint32_t SMPR2;
  __IO uint32_t JOFR[4];
  __IO uint32_t HTR;
  __IO uint32_t LTR;
  __IO uint32_t SQR[3];
  __IO uint32_t JSQR;
  __I uint32_t JDR[4];
  __I uint32_t DR;
  __I uint32_t CSR;
  __IO uint32_t CCR;
  __I uint32_t CDR;
} STM32_ADC_TypeDef;

typedef struct {
  __IO uint32_t CR;
  __IO uint32_t SWTRIGR;
  __IO uint32_t DHR12R1;
  __IO uint32_t DHR12R1;
  __IO uint32_t DHR8R1;
  __IO uint32_t DHR12R2;
  __IO uint32_t DHR12L2;
  __IO uint32_t DHR8R2;
  __IO uint32_t DHR12RD;
  __IO uint32_t DHR12LD;
  __IO uint32_t DHR8RD;
  __IO uint32_t DOR1;
  __IO uint32_t DOR2;
  __IO uint32_t SR;
} STM32_DAC_TypeDef;

#ifdef STM32F405

#define STM32_CORTEX_BASE               (0xe0000000UL)
#define STM32_AHB3_BASE                 (0x60000000UL)
#define STM32_AHB2_BASE                 (0x50050000UL)
#define STM32_AHB1_BASE                 (0x40020000UL)
#define STM32_APB2_BASE                 (0x40010000UL)
#define STM32_APB2_BASE                 (0x40000000UL)

#define STM32_FSMC_CTRL_BASE            (STM32_AHB3_BASE + 0x40000000UL)
#define STM32_FSMC4_BASE                (STM32_AHB3_BASE + 0x30000000UL)
#define STM32_FSMC3_BASE                (STM32_AHB3_BASE + 0x20000000UL)
#define STM32_FSMC2_BASE                (STM32_AHB3_BASE + 0x10000000UL)
#define STM32_FSMC1_BASE                (STM32_AHB3_BASE + 0x00000000UL)

#define STM32_RNG_BASE                  (STM32_AHB2_BASE + 0x00800UL)
#define STM32_DCMI_BASE                 (STM32_AHB2_BASE + 0x00000UL)

#define STM32_USB_OTG_HS_BASE           (STM32_AHB1_BASE + 0x20000UL)
#define STM32_ETHERNET_MAC_BASE         (STM32_AHB1_BASE + 0x09000UL)
#define STM32_DMA2_BASE                 (STM32_AHB1_BASE + 0x03800UL)
#define STM32_DMA1_BASE                 (STM32_AHB1_BASE + 0x03800UL)
#define STM32_BKPSRAM_BASE              (STM32_AHB1_BASE + 0x04000UL)
#define STM32_FLASH_BASE                (STM32_AHB1_BASE + 0x03c00UL)
#define STM32_RCC_BASE                  (STM32_AHB1_BASE + 0x03800UL)
#define STM32_CRC_BASE                  (STM32_AHB1_BASE + 0x03000UL)
#define STM32_GPIOI_BASE                (STM32_AHB1_BASE + 0x02000UL)
#define STM32_GPIOH_BASE                (STM32_AHB1_BASE + 0x01c00UL)
#define STM32_GPIOG_BASE                (STM32_AHB1_BASE + 0x01800UL)
#define STM32_GPIOF_BASE                (STM32_AHB1_BASE + 0x01400UL)
#define STM32_GPIOE_BASE                (STM32_AHB1_BASE + 0x01000UL)
#define STM32_GPIOD_BASE                (STM32_AHB1_BASE + 0x00c00UL)
#define STM32_GPIOC_BASE                (STM32_AHB1_BASE + 0x00800UL)
#define STM32_GPIOB_BASE                (STM32_AHB1_BASE + 0x00400UL)
#define STM32_GPIOA_BASE                (STM32_AHB1_BASE + 0x00000UL)

#define STM32_TIM11_BASE                (STM32_APB2_BASE + 0x04800UL)
#define STM32_TIM10_BASE                (STM32_APB2_BASE + 0x04400UL)
#define STM32_TIM9_BASE                 (STM32_APB2_BASE + 0x04000UL)
#define STM32_EXTI_BASE                 (STM32_APB2_BASE + 0x03c00UL)
#define STM32_SYSCFG_BASE               (STM32_APB2_BASE + 0x03800UL)
#define STM32_SPI1_BASE                 (STM32_APB2_BASE + 0x03000UL)
#define STM32_SDIO_BASE                 (STM32_APB2_BASE + 0x02c00UL)
#define STM32_ADC_BASE                  (STM32_APB2_BASE + 0x02000UL)
#define STM32_USART6_BASE               (STM32_APB2_BASE + 0x01400UL)
#define STM32_USART1_BASE               (STM32_APB2_BASE + 0x01000UL)
#define STM32_TIM8_BASE                 (STM32_APB2_BASE + 0x00400UL)
#define STM32_TIM1_BASE                 (STM32_APB2_BASE + 0x00000UL)

#define STM32_DAC_BASE                  (STM32_APB1_BASE + 0x07400UL)
#define STM32_PWR_BASE                  (STM32_APB1_BASE + 0x07000UL)
#define STM32_CAN2_BASE                 (STM32_APB1_BASE + 0x06800UL)
#define STM32_CAN1_BASE                 (STM32_APB1_BASE + 0x06400UL)
#define STM32_I2C3_BASE                 (STM32_APB1_BASE + 0x05c00UL)
#define STM32_I2C2_BASE                 (STM32_APB1_BASE + 0x05800UL)
#define STM32_I2C1_BASE                 (STM32_APB1_BASE + 0x05400UL)
#define STM32_UART5_BASE                (STM32_APB1_BASE + 0x05000UL)
#define STM32_UART4_BASE                (STM32_APB1_BASE + 0x04c00UL)
#define STM32_USART3_BASE               (STM32_APB1_BASE + 0x04800UL)
#define STM32_USART2_BASE               (STM32_APB1_BASE + 0x04400UL)
#define STM32_I2S3_BASE                 (STM32_APB1_BASE + 0x04000UL)
#define STM32_SPI3_BASE                 (STM32_APB1_BASE + 0x03c00UL)
#define STM32_SPI2_BASE                 (STM32_APB1_BASE + 0x03800UL)
#define STM32_I2S2_BASE                 (STM32_APB1_BASE + 0x03400UL)
#define STM32_IWDG_BASE                 (STM32_APB1_BASE + 0x03000UL)
#define STM32_WWDG_BASE                 (STM32_APB1_BASE + 0x02c00UL)
#define STM32_RTC_BASE                  (STM32_APB1_BASE + 0x02800UL)
#define STM32_TIM14_BASE                (STM32_APB1_BASE + 0x02000UL)
#define STM32_TIM13_BASE                (STM32_APB1_BASE + 0x01c00UL)
#define STM32_TIM12_BASE                (STM32_APB1_BASE + 0x01800UL)
#define STM32_TIM7_BASE                 (STM32_APB1_BASE + 0x01400UL)
#define STM32_TIM6_BASE                 (STM32_APB1_BASE + 0x01000UL)
#define STM32_TIM5_BASE                 (STM32_APB1_BASE + 0x00c00UL)
#define STM32_TIM4_BASE                 (STM32_APB1_BASE + 0x00800UL)
#define STM32_TIM3_BASE                 (STM32_APB1_BASE + 0x00400UL)
#define STM32_TIM2_BASE                 (STM32_APB1_BASE + 0x00000UL)

#define STM32_DMA1            ((STM32_DMA_TypeDef       *) STM32_DMA1_BASE     )
#define STM32_DMA2            ((STM32_DMA_TypeDef       *) STM32_DMA2_BASE     )
#define STM32_RCC             ((STM32_RCC_TypeDef       *) STM32_RCC_BASE      )
#define STM32_GPIOI           ((STM32_GPIO_TypeDef      *) STM32_GPIOI_BASE    )
#define STM32_GPIOH           ((STM32_GPIO_TypeDef      *) STM32_GPIOH_BASE    )
#define STM32_GPIOG           ((STM32_GPIO_TypeDef      *) STM32_GPIOG_BASE    )
#define STM32_GPIOF           ((STM32_GPIO_TypeDef      *) STM32_GPIOF_BASE    )
#define STM32_GPIOE           ((STM32_GPIO_TypeDef      *) STM32_GPIOE_BASE    )
#define STM32_GPIOD           ((STM32_GPIO_TypeDef      *) STM32_GPIOD_BASE    )
#define STM32_GPIOC           ((STM32_GPIO_TypeDef      *) STM32_GPIOC_BASE    )
#define STM32_GPIOB           ((STM32_GPIO_TypeDef      *) STM32_GPIOB_BASE    )
#define STM32_GPIOA           ((STM32_GPIO_TypeDef      *) STM32_GPIOA_BASE    )

#define STM32_TIM11           ((STM32_TIM_TypeDef       *)   STM32_TIM11_BASE  )
#define STM32_TIM10           ((STM32_TIM_TypeDef       *)   STM32_TIM10_BASE  )
#define STM32_TIM9            ((STM32_TIM_TypeDef       *)   STM32_TIM9_BASE   )
#define STM32_SPI1            ((STM32_SPI_TypeDef       *)   STM32_SPI1_BASE   )
#define STM32_ADC1            ((STM32_ADC_TypeDef       *)   STM32_ADC_BASE    )
#define STM32_USART6          ((STM32_USART_TypeDef     *)   STM32_USART6_BASE )
#define STM32_USART1          ((STM32_USART_TypeDef     *)   STM32_USART1_BASE )
#define STM32_TIM8            ((STM32_TIM18_TypeDef     *)   STM32_TIM8_BASE   )
#define STM32_TIM1            ((STM32_TIM18_TypeDef     *)   STM32_TIM1_BASE   )
                                                                               
#define STM32_PWR             ((STM32_PWR_TypeDef       *)   STM32_PWR_BASE    )
#define STM32_UART5           ((STM32_USART_TypeDef     *)   STM32_UART5_BASE  )
#define STM32_UART4           ((STM32_USART_TypeDef     *)   STM32_UART4_BASE  )
#define STM32_USART3          ((STM32_USART_TypeDef     *)   STM32_UART3_BASE  )
#define STM32_USART2          ((STM32_USART_TypeDef     *)   STM32_UART2_BASE  )
#define STM32_SPI3            ((STM32_SPI_TypeDef       *)   STM32_SPI3_BASE   )
#define STM32_SPI2            ((STM32_SPI_TypeDef       *)   STM32_SPI2_BASE   )
#define STM32_TIM14           ((STM32_TIM_TypeDef       *)   STM32_TIM14_BASE  )
#define STM32_TIM13           ((STM32_TIM_TypeDef       *)   STM32_TIM13_BASE  )
#define STM32_TIM12           ((STM32_TIM_TypeDef       *)   STM32_TIM12_BASE  )
#define STM32_TIM7            ((STM32_TIM_TypeDef       *)   STM32_TIM7_BASE   )
#define STM32_TIM6            ((STM32_TIM_TypeDef       *)   STM32_TIM6_BASE   )
#define STM32_TIM5            ((STM32_TIM_TypeDef       *)   STM32_TIM5_BASE   )
#define STM32_TIM4            ((STM32_TIM_TypeDef       *)   STM32_TIM4_BASE   )
#define STM32_TIM3            ((STM32_TIM_TypeDef       *)   STM32_TIM3_BASE   )
#define STM32_TIM2            ((STM32_TIM_TypeDef       *)   STM32_TIM2_BASE   )

#endif /* STM32F405 */
