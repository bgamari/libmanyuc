/* STM32F4xx Startup Script */

.syntax unified
.thumb

.section ".interrupt_vector_table"
.global __interrupt_vector_table
/* This interrupt vector table gets pulled in by the linker script
 * into flash right before the startup code */
__interrupt_vector_table:
.long _end_stack
.long Reset_Handler
.long NMI_Handler
.long HardFault_Handler
.long MemManage_Handler
.long BusFault_Handler
.long UsageFault_Handler
.long 0
.long 0
.long 0
.long 0
.long SVC_Handler
.long DebugMon_Handler
.long 0
.long PendSV_Handler
.long SysTick_Handler
/* External interrupts */
.long WWDG_IRQHandler
.long PVD_IRQHandler
.long TAMP_STAMP_IRQHandler
.long RTC_WKUP_IRQHandler
.long FLASH_IRQHandler
.long RCC_IRQHandler
.long EXTI0_IRQHandler
.long EXTI1_IRQHandler
.long EXTI2_IRQHandler
.long EXTI3_IRQHandler
.long EXTI4_IRQHandler
.long DMA1_STREAM0_IRQHandler
.long DMA1_STREAM1_IRQHandler
.long DMA1_STREAM2_IRQHandler
.long DMA1_STREAM3_IRQHandler
.long DMA1_STREAM4_IRQHandler
.long DMA1_STREAM5_IRQHandler
.long DMA1_STREAM6_IRQHandler
.long ADC_IRQHandler
.long CAN1_TX_IRQHandler
.long CAN1_RX0_IRQHandler
.long CAN1_RX1_IRQHandler
.long CAN1_SCE_IRQHandler
.long EXTI9_5_IRQHandler
.long TIM1_BRK_TIM9_IRQHandler
.long TIM1_BRK_TIM10_IRQHandler
.long TIM1_TRG_COM_TIM11_IRQHandler
.long TIM1_CC_IRQHandler
.long TIM2_IRQHandler
.long TIM3_IRQHandler
.long TIM4_IRQHandler
.long I2C1_EV_IRQHandler
.long I2C1_ER_IRQHandler
.long I2C2_EV_IRQHandler
.long I2C2_ER_IRQHandler
.long SPI1_IRQHandler
.long SPI2_IRQHandler
.long USART1_IRQHandler
.long USART2_IRQHandler
.long USART3_IRQHandler
.long EXTI15_10_IRQHandler
.long OTG_FS_WKUP_IRQHandler
.long TIM8_BRK_TIM12_IRQHandler
.long TIM8_UP_TIM13_IRQHandler
.long TIM8_CC_IRQHandler
.long DMA1_Stream7_IRQHandler
.long FSMC_IRQHandler
.long SDIO_IRQHandler
.long TIM5_IRQHandler
.long SPI3_IRQHandler
.long UART4_IRQHandler
.long UART5_IRQHandler
.long TIM6_DAC_IRQHandler
.long TIM7_IRQHandler
.long DMA2_Stream0_IRQHandler
.long DMA2_Stream1_IRQHandler
.long DMA2_Stream2_IRQHandler
.long DMA2_Stream3_IRQHandler
.long DMA2_Stream4_IRQHandler
.long ETH_IRQHandler
.long ETH_WKUP_IRQHandler
.long CAN2_TX_IRQHandler
.long CAN2_RX0_IRQHandler
.long CAN2_RX1_IRQHandler
.long CAN2_SCE_IRQHandler
.long OTG_FS_IRQHandler
.long DMA2_Stream5_IRQHandler
.long DMA2_Stream6_IRQHandler
.long DMA2_Stream7_IRQHandler
.long USART6_IRQHandler
.long I2C3_EV_IRQHandler
.long I2C3_ER_IRQHandler
.long OTG_HS_EP1_OUT_IRQHandler
.long OTG_HS_EP1_IN_IRQHandler
.long OTG_HS_WKUP_IRQHandler
.long OTG_HS_IRQHandler
.long DCMI_IRQHandler
.long CRYP_IRQHandler
.long HASH_RNG_IRQHandler
.long FPU_IRQHandler

/* Addresses for all of the interrupts handlers above, can be pointed to a
 * real IRQ handler instead of falling through to the startup code. */
    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler: 

    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
MemManage_Handler: 

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler: 

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:

    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
DebugMon_Handler:

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:

    .weak   WWDG_IRQHandler
    .type   WWDG_IRQHandler, %function
WWDG_IRQHandler:

    .weak   PVD_IRQHandler
    .type   PVD_IRQHandler, %function
PVD_IRQHandler:

    .weak   TAMP_STAMP_IRQHandler
    .type   TAMP_STAMP_IRQHandler, %function
TAMP_STAMP_IRQHandler:

    .weak   RTC_WKUP_IRQHandler
    .type   RTC_WKUP_IRQHandler, %function
RTC_WKUP_IRQHandler:

    .weak   FLASH_IRQHandler
    .type   FLASH_IRQHandler, %function
FLASH_IRQHandler:

    .weak   RCC_IRQHandler
    .type   RCC_IRQHandler, %function
RCC_IRQHandler:

    .weak   EXTI0_IRQHandler
    .type   EXTI0_IRQHandler, %function
EXTI0_IRQHandler:

    .weak   EXTI1_IRQHandler
    .type   EXTI1_IRQHandler, %function
EXTI1_IRQHandler:

    .weak   EXTI2_IRQHandler
    .type   EXTI2_IRQHandler, %function
EXTI2_IRQHandler:

    .weak   EXTI3_IRQHandler
    .type   EXTI3_IRQHandler, %function
EXTI3_IRQHandler:

    .weak   EXTI4_IRQHandler
    .type   EXTI4_IRQHandler, %function
EXTI4_IRQHandler:

    .weak   DMA1_STREAM0_IRQHandler
    .type   DMA1_STREAM0_IRQHandler, %function
DMA1_STREAM0_IRQHandler:

    .weak   DMA1_STREAM1_IRQHandler
    .type   DMA1_STREAM1_IRQHandler, %function
DMA1_STREAM1_IRQHandler:

    .weak   DMA1_STREAM2_IRQHandler
    .type   DMA1_STREAM2_IRQHandler, %function
DMA1_STREAM2_IRQHandler:

    .weak   DMA1_STREAM3_IRQHandler
    .type   DMA1_STREAM3_IRQHandler, %function
DMA1_STREAM3_IRQHandler:

    .weak   DMA1_STREAM4_IRQHandler
    .type   DMA1_STREAM4_IRQHandler, %function
DMA1_STREAM4_IRQHandler:

    .weak   DMA1_STREAM5_IRQHandler
    .type   DMA1_STREAM5_IRQHandler, %function
DMA1_STREAM5_IRQHandler:

    .weak   DMA1_STREAM6_IRQHandler
    .type   DMA1_STREAM6_IRQHandler, %function
DMA1_STREAM6_IRQHandler:

    .weak   ADC_IRQHandler
    .type   ADC_IRQHandler, %function
ADC_IRQHandler:

    .weak   CAN1_TX_IRQHandler
    .type   CAN1_TX_IRQHandler, %function
CAN1_TX_IRQHandler:

    .weak   CAN1_RX0_IRQHandler
    .type   CAN1_RX0_IRQHandler, %function
CAN1_RX0_IRQHandler:

    .weak   CAN1_RX1_IRQHandler
    .type   CAN1_RX1_IRQHandler, %function
CAN1_RX1_IRQHandler:

    .weak   CAN1_SCE_IRQHandler
    .type   CAN1_SCE_IRQHandler, %function
CAN1_SCE_IRQHandler:

    .weak   EXTI9_5_IRQHandler
    .type   EXTI9_5_IRQHandler, %function
EXTI9_5_IRQHandler:

    .weak   TIM1_BRK_TIM9_IRQHandler
    .type   TIM1_BRK_TIM9_IRQHandler, %function
TIM1_BRK_TIM9_IRQHandler:

    .weak   TIM1_BRK_TIM10_IRQHandler
    .type   TIM1_BRK_TIM10_IRQHandler, %function
TIM1_BRK_TIM10_IRQHandler:

    .weak   TIM1_TRG_COM_TIM11_IRQHandler
    .type   TIM1_TRG_COM_TIM11_IRQHandler, %function
TIM1_TRG_COM_TIM11_IRQHandler:

    .weak   TIM1_CC_IRQHandler
    .type   TIM1_CC_IRQHandler, %function
TIM1_CC_IRQHandler:

    .weak   TIM2_IRQHandler
    .type   TIM2_IRQHandler, %function
TIM2_IRQHandler:

    .weak   TIM3_IRQHandler
    .type   TIM3_IRQHandler, %function
TIM3_IRQHandler:

    .weak   TIM4_IRQHandler
    .type   TIM4_IRQHandler, %function
TIM4_IRQHandler:

    .weak   I2C1_EV_IRQHandler
    .type   I2C1_EV_IRQHandler, %function
I2C1_EV_IRQHandler:

    .weak   I2C1_ER_IRQHandler
    .type   I2C1_ER_IRQHandler, %function
I2C1_ER_IRQHandler:

    .weak   I2C2_EV_IRQHandler
    .type   I2C2_EV_IRQHandler, %function
I2C2_EV_IRQHandler:

    .weak   I2C2_ER_IRQHandler
    .type   I2C2_ER_IRQHandler, %function
I2C2_ER_IRQHandler:

    .weak   SPI1_IRQHandler
    .type   SPI1_IRQHandler, %function
SPI1_IRQHandler:

    .weak   SPI2_IRQHandler
    .type   SPI2_IRQHandler, %function
SPI2_IRQHandler:

    .weak   USART1_IRQHandler
    .type   USART1_IRQHandler, %function
USART1_IRQHandler:

    .weak   USART2_IRQHandler
    .type   USART2_IRQHandler, %function
USART2_IRQHandler:

    .weak   USART3_IRQHandler
    .type   USART3_IRQHandler, %function
USART3_IRQHandler:

    .weak   EXTI15_10_IRQHandler
    .type   EXTI15_10_IRQHandler, %function
EXTI15_10_IRQHandler:

    .weak   OTG_FS_WKUP_IRQHandler
    .type   OTG_FS_WKUP_IRQHandler, %function
OTG_FS_WKUP_IRQHandler:

    .weak   TIM8_BRK_TIM12_IRQHandler
    .type   TIM8_BRK_TIM12_IRQHandler, %function
TIM8_BRK_TIM12_IRQHandler:

    .weak   TIM8_UP_TIM13_IRQHandler
    .type   TIM8_UP_TIM13_IRQHandler, %function
TIM8_UP_TIM13_IRQHandler:

    .weak   TIM8_CC_IRQHandler
    .type   TIM8_CC_IRQHandler, %function
TIM8_CC_IRQHandler:

    .weak   DMA1_Stream7_IRQHandler
    .type   DMA1_Stream7_IRQHandler, %function
DMA1_Stream7_IRQHandler:

    .weak   FSMC_IRQHandler
    .type   FSMC_IRQHandler, %function
FSMC_IRQHandler:

    .weak   SDIO_IRQHandler
    .type   SDIO_IRQHandler, %function
SDIO_IRQHandler:

    .weak   TIM5_IRQHandler
    .type   TIM5_IRQHandler, %function
TIM5_IRQHandler:

    .weak   SPI3_IRQHandler
    .type   SPI3_IRQHandler, %function
SPI3_IRQHandler:

    .weak   UART4_IRQHandler
    .type   UART4_IRQHandler, %function
UART4_IRQHandler:

    .weak   UART5_IRQHandler
    .type   UART5_IRQHandler, %function
UART5_IRQHandler:

    .weak   TIM6_DAC_IRQHandler
    .type   TIM6_DAC_IRQHandler, %function
TIM6_DAC_IRQHandler:

    .weak   TIM7_IRQHandler
    .type   TIM7_IRQHandler, %function
TIM7_IRQHandler:

    .weak   DMA2_Stream0_IRQHandler
    .type   DMA2_Stream0_IRQHandler, %function
DMA2_Stream0_IRQHandler:

    .weak   DMA2_Stream1_IRQHandler
    .type   DMA2_Stream1_IRQHandler, %function
DMA2_Stream1_IRQHandler:

    .weak   DMA2_Stream2_IRQHandler
    .type   DMA2_Stream2_IRQHandler, %function
DMA2_Stream2_IRQHandler:

    .weak   DMA2_Stream3_IRQHandler
    .type   DMA2_Stream3_IRQHandler, %function
DMA2_Stream3_IRQHandler:

    .weak   DMA2_Stream4_IRQHandler
    .type   DMA2_Stream4_IRQHandler, %function
DMA2_Stream4_IRQHandler:

    .weak   ETH_IRQHandler
    .type   ETH_IRQHandler, %function
ETH_IRQHandler:

    .weak   ETH_WKUP_IRQHandler
    .type   ETH_WKUP_IRQHandler, %function
ETH_WKUP_IRQHandler:

    .weak   CAN2_TX_IRQHandler
    .type   CAN2_TX_IRQHandler, %function
CAN2_TX_IRQHandler:

    .weak   CAN2_RX0_IRQHandler
    .type   CAN2_RX0_IRQHandler, %function
CAN2_RX0_IRQHandler:

    .weak   CAN2_RX1_IRQHandler
    .type   CAN2_RX1_IRQHandler, %function
CAN2_RX1_IRQHandler:

    .weak   CAN2_SCE_IRQHandler
    .type   CAN2_SCE_IRQHandler, %function
CAN2_SCE_IRQHandler:

    .weak   OTG_FS_IRQHandler
    .type   OTG_FS_IRQHandler, %function
OTG_FS_IRQHandler:

    .weak   DMA2_Stream5_IRQHandler
    .type   DMA2_Stream5_IRQHandler, %function
DMA2_Stream5_IRQHandler:

    .weak   DMA2_Stream6_IRQHandler
    .type   DMA2_Stream6_IRQHandler, %function
DMA2_Stream6_IRQHandler:

    .weak   DMA2_Stream7_IRQHandler
    .type   DMA2_Stream7_IRQHandler, %function
DMA2_Stream7_IRQHandler:

    .weak   USART6_IRQHandler
    .type   USART6_IRQHandler, %function
USART6_IRQHandler:

    .weak   I2C3_EV_IRQHandler
    .type   I2C3_EV_IRQHandler, %function
I2C3_EV_IRQHandler:

    .weak   I2C3_ER_IRQHandler
    .type   I2C3_ER_IRQHandler, %function
I2C3_ER_IRQHandler:

    .weak   OTG_HS_EP1_OUT_IRQHandler
    .type   OTG_HS_EP1_OUT_IRQHandler, %function
OTG_HS_EP1_OUT_IRQHandler:

    .weak   OTG_HS_EP1_IN_IRQHandler
    .type   OTG_HS_EP1_IN_IRQHandler, %function
OTG_HS_EP1_IN_IRQHandler:

    .weak   OTG_HS_WKUP_IRQHandler
    .type   OTG_HS_WKUP_IRQHandler, %function
OTG_HS_WKUP_IRQHandler:

    .weak   OTG_HS_IRQHandler
    .type   OTG_HS_IRQHandler, %function
OTG_HS_IRQHandler:

    .weak   DCMI_IRQHandler
    .type   DCMI_IRQHandler, %function
DCMI_IRQHandler:

    .weak   CRYP_IRQHandler
    .type   CRYP_IRQHandler, %function
CRYP_IRQHandler:

    .weak   HASH_RNG_IRQHandler
    .type   HASH_RNG_IRQHandler, %function
HASH_RNG_IRQHandler:

    .weak   FPU_IRQHandler
    .type   FPU_IRQHandler, %function
FPU_IRQHandler:


.section ".startup","x",%progbits
.thumb_func
.global _startup
.global Reset_Handler

Reset_Handler:
_startup:
	/* Clear the BSS section */ 
	mov r0, #0
	ldr r1, = _start_bss
	ldr r2, = _end_bss
	sub r2, #1
_loop:	cmp r1, r2
	str r0, [r1, #0]
	add r1, #4
	blo _loop 

	/* Jump to init() */
	ldr r0, =init
	blx r0

	/* Jump to main() */
	ldr r0, =main
	bx r0
	
.end
