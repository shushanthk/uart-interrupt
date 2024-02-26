/**
  ******************************************************************************
  * @file    main.c 
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
#include "main.h"

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
uint32_t arr[10] = {0x01234567, 0x89ABCDEF, 0x76543210, 0xFEDCBA98, 0x13579BDF,
                       0x2468ACE0, 0xBDF13579, 0xECA86420, 0xA1B2C3D4, 0xF0E9D8C7};
//  uint32_t arr2[10] = {0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00, 0x10203040,
//                       0x50607080, 0x90A0B0C0, 0xD0E0F000, 0xABCDEF12, 0x3456789A};
//  uint32_t arr3[10] = {0x1F2F3F4F, 0x5F6F7F8F, 0x9FAFBFCF, 0xDFEFF0F0, 0x1F2F3F4F,
//                       0x5F6F7F8F, 0x9FAFBFCF, 0xDFEFF0F0, 0x1F2F3F4F, 0x5F6F7F8F};
//  uint32_t arr4[10] = {0xA1B2C3D4, 0xE5F6F7F8, 0x9FAFBFCF, 0x1F2F3F4F, 0x5F6F7F8F,
//                       0x9FAFBFCF, 0xDFEFF0F0, 0x1F2F3F4F, 0x5F6F7F8F, 0x9FAFBFCF};
USART_IT_TX_Def Usart1TxBuffer;
USART_RxBuf_Def Usart1RxBuffer;
/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void USART1_IT_Send(uint8_t *pData, uint16_t len);
static void USART1_IT_Receive(uint8_t *pData, uint16_t len);
char buffer[120]="hello";
uint8_t Tx_buffer=0x11;
uint8_t Rx_buffer[200];
char Rx_buffer1[7];

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (KEIL_startup_hk32f030xmxxa.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_hk32f030xmxxa.c file
     */
	/* Initialize LEDs available on STM320518-EVAL board ************************/
//	HK_EVAL_LEDInit(LED1);
	
  /* USART configuration */
  USART_Config();
	
	/* Set USART1 TxBuffer Status */
	Usart1TxBuffer.FinishedFlag = SET;
	 sprintf(buffer,"AT+DTRX=1,2,50,%02X%02X%02X%02X%02X%02X%02X%02X\r\n",
		arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],arr[7]);
	while(1)
	{
		/* Test */
		if( Usart1TxBuffer.FinishedFlag == SET )
		{
			

			USART1_IT_Send((uint8_t*)&buffer,sizeof(&buffer));
			for(int i=0;i<20000;i++)
			__NOP();
		  USART1_IT_Receive((uint8_t*)Rx_buffer,sizeof(Rx_buffer));
			__NOP();__NOP();
		}
		
		
		}
		for(int i=0;i<20000;i++)
			__NOP();
	}
/**
  * @brief Configure the USART Device
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable GPIO clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);
	
	/* Enable USART clock */
	RCC_APBPeriph2ClockCmd(RCC_APBPeriph2_USART1, ENABLE); 
	
	  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_1);
  
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /* USARTx configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - Stop Bit = 1 Stop Bit
  - Parity = No Parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  
	/* Configre NVIC */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable USART */
  USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  Start Bit Method to USART AutoBaudRate.
  * @param  None
  * @retval None
  */
static void USART1_IT_Send(uint8_t *pData, uint16_t len)
{ 
 uint8_t i;
	  
	Usart1TxBuffer.Len = len;
	Usart1TxBuffer.Index = 0;
	Usart1TxBuffer.FinishedFlag = RESET;
	
	/* Copy data to transfer buffer */
	for( i = 0; i < len; i ++ )
	{
		Usart1TxBuffer.Data[i] = *(pData ++ );
	}
	
	/* Enable transfer empty interrupt */
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  

  /* Enable transfer complete interrupt */  
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);
}
static void USART1_IT_Receive(uint8_t *pData, uint16_t len)
{ 
 uint8_t i;
	  
	Usart1RxBuffer.Len = len;
	Usart1RxBuffer.Index = 0;
	Usart1RxBuffer.FinishedFlag = RESET;
	
	/* Copy data to transfer buffer */
	for( i = 0; i < len; i ++ )
	{
		*(pData ++ )=Usart1RxBuffer.Data[i];
	}
	
	/* Enable transfer empty interrupt */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  

  /* Enable transfer complete interrupt */  
	USART_ITConfig(USART1, USART_IT_TC, DISABLE);
}
//static void USART1_IT_Receive(uint8_t *pData, uint16_t len)
//{ 
//    uint8_t i;
//    
//    Usart1RxBuffer.Len = len;
//    Usart1RxBuffer.Index = 0;
//    Usart1RxBuffer.FinishedFlag = RESET;
//    
//    /* Copy data to transfer buffer */
//    for (i = 0; i < len; i++)
//    {
//        pData[i] = Usart1RxBuffer.Data[i];
//    }
//    
//    /* Enable transfer empty interrupt */
//    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  

//    /* Enable transfer complete interrupt */  
//    USART_ITConfig(USART1, USART_IT_TC, ENABLE);
//}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */
