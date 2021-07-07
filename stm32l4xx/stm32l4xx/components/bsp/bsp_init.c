/**
 **************************************************************************************************
 * @file        bsp_init.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_init.h"
#include "stm32_bsp_conf.h"
#include "main.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_led.h"
/**
 * @addtogroup    bsp_init_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_init_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_init_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_init_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_init_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**s
 * @}
 */
void SystemClock_Config(void);

/**
 * @defgroup      bsp_init_Functions 
 * @brief         
 * @{  
 */

void Board_Init(void)
{
	DEBUG("BoardInit\r\n");

	DEBUG("SysClockFreq:%d\r\n",HAL_RCC_GetSysClockFreq());
	DEBUG("HCLKFreq:%d\r\n",HAL_RCC_GetHCLKFreq());
	DEBUG("PCLK1Freq:%d CLK2Freq:%d\r\n",HAL_RCC_GetPCLK1Freq(),HAL_RCC_GetPCLK2Freq());

	BSP_Systick_Init();  // open the 1ms systick ...
	SystemClock_Config(); //  Reconf the MCU Clock ...  notice :the func must be call after the Systick open ,and the HAL_Tick is inc.
	
	DEBUG("SysClockFreq:%d\r\n",HAL_RCC_GetSysClockFreq());
	DEBUG("HCLKFreq:%d\r\n",HAL_RCC_GetHCLKFreq());
	DEBUG("PCLK1Freq:%d CLK2Freq:%d\r\n",HAL_RCC_GetPCLK1Freq(),HAL_RCC_GetPCLK2Freq());
}
void BSP_Init(void)
{
	Bsp_LedInit();
}

void SystemClock_Config(void)
{
	  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	  /** Initializes the CPU, AHB and APB busses clocks 
	  */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
	  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	  RCC_OscInitStruct.PLL.PLLM = 1;
	  RCC_OscInitStruct.PLL.PLLN = 10;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
		Error_Handler();
	  }
	  /** Initializes the CPU, AHB and APB busses clocks 
	  */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	  {
		Error_Handler();
	  }
	  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART2;
	  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	  {
		Error_Handler();
	  }
	  /** Configure the main internal regulator output voltage 
	  */
	  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	  {
		Error_Handler();
	  }
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

