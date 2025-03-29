/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Ctrl.h"
#include "Calculate.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int Watch;
int adc_initializer;
int adc_flag=0;//Used as flag for ADC INIT
int emergencyCnt=0,rstCnt=0,adcCnt=0,usartCnt=0;
int count=0;
int init=0;
DataPacket packet;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t buff[4];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	HAL_ADC_Start(&hadc1);     
	HAL_ADC_PollForConversion(&hadc1, 20);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)		
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim2.Instance) 
	{	
//		//快速双击触发（已替换
//		switch(emergencySuspensionFlag){
//			case 0:{
//				if(BOTTOM_7==1){
//					break;
//				}
//				else{
//					emergencySuspensionFlag=1;
//					break;
//				}
//			}
//			case 1:{
//				if(BOTTOM_7==0){
//					if(emergencySuspensionTimer>=80){emergencySuspensionFlag=0;emergencySuspensionTimer=0;} 
//					else emergencySuspensionTimer++;
//					break;
//				}
//				else{
//					if(emergencySuspensionTimer>=80){
//						emergencySuspensionTimer=0;
//						emergencySuspensionFlag=0;
//					}
//					else{
//						emergencySuspensionFlag=2;
//						emergencySuspensionTimer=0;
//					}
//				}
//				break;
//			}
//			case 2:{
//				if(BOTTOM_7==1){
//					if(emergencySuspensionTimer>=80){emergencySuspensionFlag=0;emergencySuspensionTimer=0;} 
//					else emergencySuspensionTimer++;
//					break;
//				}
//				else{
//					if(emergencySuspensionTimer>=80){
//						emergencySuspensionTimer=0;
//						emergencySuspensionFlag=0;
//					}
//					else{
//						emergencySuspensionFlag=3;
//						emergencySuspensionTimer=0;
//					}
//					break;
//				}
//			}	
//			case 3:{
//				if (emergencySuspensionTimer==0){
//					if(emergencySuspend==0xFF) emergencySuspend=0x00;
//					else emergencySuspend=0xFF;
//					emergencySuspensionTimer++;
//				}
//				else if(emergencySuspensionTimer>=80){
//					emergencySuspensionFlag=0;
//					emergencySuspensionTimer=0;
//				}
//				else{
//					emergencySuspensionTimer++;
//				}
//				break;
//			}
//			default:break;
//			}
		if(BOTTOM_6==0) {
			emergencySuspend|=0x0F;
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);
			emergencyCnt=200;}
		else if (emergencyCnt!=0) emergencyCnt--;
		else {
			emergencySuspend&=0xF0;
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);}
		if(BOTTOM_7==0) {
			emergencySuspend|=0xF0;
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);rstCnt=200;}
		else if (emergencyCnt!=0) 
			emergencyCnt--;
		else {
			emergencySuspend&=0x0F;
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);}
		HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Value,8);
		Update_BOTTOM();
		Update_ADC();	

	}
	
		if(htim->Instance == htim3.Instance){	
			Watch=SWITCH_4;
			if(adc_flag==0){
				 if(adcCnt<=100){
						adcCnt++;
						init_ADC_data();
				 }
				 else{
						init_ADC_MaxMin();
				 }
				 if(SWITCH_4!=adc_initializer){
						adc_flag=1;
				 }
			}
			else{
				Flags_clear();
				packData(&packet, TXData, sizeof(TXData));
				switch(SWITCH_4){
				case 0:
						if(usartCnt==3){
							HAL_UART_Transmit_DMA(&huart1,(uint8_t *)&packet,sizeof(packet));
							
							usartCnt=0;
						}
						else usartCnt++;
						break;
				case 1:HAL_UART_Transmit_DMA(&huart2,(uint8_t *)&packet,sizeof(packet)); break;
				default:break;
					}      
				}
//	HAL_UART_Transmit_IT(&huart1, (uint8_t *)&packet, 14);			
//		HAL_UART_Transmit(&huart1, (uint8_t*)&packet,sizeof(packet),0xffff);			
//			HAL_UART_Transmit(&huart1, (uint8_t*)&buff,sizeof(buff),0xffff);				
	}
		
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
