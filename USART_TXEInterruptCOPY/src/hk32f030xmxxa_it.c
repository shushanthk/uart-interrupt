/**
  ******************************************************************************
  * @file    hk32f030xmxxa_it.c 
  * @author  Alexander
  * @version V1.0.0
  * @date    04-January-2023
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 HKMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hk32f030xmxxa_it.h"
/** @addtogroup HK32F030xMxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_TXEInterrupt
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern USART_IT_TX_Def Usart1TxBuffer;
extern USART_RxBuf_Def Usart1RxBuffer;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*             HK32F030xMxxA Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (KEIL_startup_hk32f030xmxxa.s).                                      */
/******************************************************************************/
/**
  * @brief  This function handles USART1 interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
	// receving interrupt
{
    // Receiving interrupt 
		if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET )
	{
		
		
	    if( Usart1RxBuffer.Index < Usart1RxBuffer.Len )
		{
			/* receving Data */
			Usart1RxBuffer.Data[Usart1RxBuffer.Index++] = USART1->RDR & (uint16_t)0x01FF;
			Usart1RxBuffer.Index ++;
      USART_ClearITPendingBit(USART1, USART_IT_RXNE);			 
		}
		else
		{
			Usart1RxBuffer.Index = 0;
			Usart1RxBuffer.Len = 0;
			USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);  
			
		}
	}
	
	
//    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//    {
//        if(Usart1RxBuffer.Index < Usart1RxBuffer.Len)
//        {
//            // Receiving Data
//            Usart1RxBuffer.Data[Usart1RxBuffer.Index++] = USART1->RDR;
//            USART_ClearITPendingBit(USART1, USART_IT_RXNE);			 
//        }
//        else
//        {
//            // Buffer overflow, handle it as necessary
//            Usart1RxBuffer.Index = 0;
//            Usart1RxBuffer.Len = 0;
//            USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  
//        }
//    }
		
}
	

    
/* USART1 transfer empty interrupt handle */
	if( USART_GetITStatus(USART1, USART_IT_TXE) != RESET )
	{
		USART_ClearITPendingBit(USART1, USART_IT_TXE);
		
		if( Usart1TxBuffer.Index < Usart1TxBuffer.Len )
		{
			/* Transmit Data */
			USART1->TDR = (Usart1TxBuffer.Data[Usart1TxBuffer.Index] & (uint16_t)0x01FF);
			Usart1TxBuffer.Index ++;
		}
		else
		{
			Usart1TxBuffer.Index = 0;
			Usart1TxBuffer.Len = 0;
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);  
			USART_ITConfig(USART1, USART_IT_TC, ENABLE);
		}
	}
    
	/* USART1 transfer complete interrupt handle */
	if( USART_GetITStatus(USART1, USART_IT_TC) != RESET )
	{
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		USART_ITConfig(USART1, USART_IT_TC, DISABLE); 
		Usart1TxBuffer.FinishedFlag = SET;
    
	}
	
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */
