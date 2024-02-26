/**
  ******************************************************************************
  * @file    HK32F030xMxxA_StdPeriph_Templates/main.h 
  * @author  Alexander
  * @version V1.0.0
  * @date    04-January-2023
  * @brief   Header for main.c module
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "hk32f030xmxxa.h"

#ifdef USE_HK32F0301MG6P7A_EVAL
#include "hk32f0301mg6p7a_eval.h"
#endif /* USE_HK32F0301MG6P7A_EVAL */

/* Exported types ------------------------------------------------------------*/
typedef struct 
{
  uint8_t Data[512];
  uint8_t Len;
  uint8_t Index;
	uint8_t FinishedFlag;
}USART_IT_TX_Def;


typedef struct
{
  uint8_t Data[512];
  uint8_t Index;
  uint8_t Len;
  uint8_t FinishedFlag;
}USART_RxBuf_Def;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

