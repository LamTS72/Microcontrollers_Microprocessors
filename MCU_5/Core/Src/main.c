/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "scheduler.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void togglePA4(){
	HAL_GPIO_TogglePin(GPIOA, PA4_Pin);
}
void togglePA5(){
	HAL_GPIO_TogglePin(GPIOA, PA5_Pin);
}

void togglePA6(){
	HAL_GPIO_TogglePin(GPIOA, PA6_Pin);
}
void togglePA7(){
	HAL_GPIO_TogglePin(GPIOA, PA7_Pin);
}
void togglePA8(){
	HAL_GPIO_TogglePin(GPIOA, PA8_Pin);
}

#define MAX_CMD_SIZE 5
#define MAX_BUFFER_SIZE 30
#define INIT 0
#define HANDLE 1
#define SERVING 2
#define RST 1
#define OK 2

uint8_t temp_byte;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t cmd_flag = 0;
uint8_t cmd_data[MAX_CMD_SIZE];
uint8_t cmd_data_index = 0;
int ADC_value = 0;
int mode = 0;

void reset_buffer(){
	for(int i=0; i < MAX_BUFFER_SIZE; i++){
		buffer[i] = ' ';
	}
	index_buffer = 0;
	//cmd_data_index = 0;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if (huart->Instance == USART2){
		HAL_UART_Transmit(&huart2, &temp_byte, 1, 500);
		buffer[index_buffer++] = temp_byte;
		if (index_buffer == MAX_BUFFER_SIZE) {
			index_buffer = 0;
		}

		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2, &temp_byte, 1);
	}
}

int check_RST(uint8_t str[]){
	if (str[0] == 'R' && str[1] == 'S' && str[2] == 'T'){
		return 1;
	}
	else return 0;
}

int check_OK(uint8_t str[]){
	if (str[0] == 'O' && str[1] == 'K'){
		return 1;
	}
	else return 0;
}

void cmd_parser_fsm(){
	switch(mode){
	case INIT:
		if(temp_byte == '!'){
			reset_buffer();
			mode = HANDLE;
		}
		reset_buffer();
		break;
	case HANDLE:
		if(index_buffer == 0){
			mode = INIT;
		}
		else if(temp_byte == '#'){
			memcpy(cmd_data, buffer, sizeof(cmd_data));
			cmd_flag = 1;
			mode = INIT;
		}
		else if(temp_byte == '!'){
			reset_buffer();
		}
		break;
	}
}

void uart_communication(){
	char str[50];
	if(cmd_flag == 1){
		if(check_RST(cmd_data) == 1){
			ADC_value = HAL_ADC_GetValue(&hadc1);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!ADC=%d#\r\n",ADC_value), 500);
		}
		else if(check_OK(cmd_data) == 1){
			ADC_value = -1;
			cmd_flag = 0;
		}
	}
}



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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  SCH_Init();
  //HAL_GPIO_WritePin(GPIOA, PA4_Pin |PA5_Pin | PA6_Pin |PA7_Pin |PA8_Pin, SET);
  SCH_Add_Task(togglePA4, 50, 100);
  SCH_Add_Task(togglePA5, 100, 100);
  SCH_Add_Task(togglePA6, 150, 100);
  SCH_Add_Task(togglePA7, 200, 100);
  SCH_Add_Task(togglePA8, 300, 0);
  SCH_Add_Task(togglePA8, 300, 0);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  SCH_Dispatch_Tasks();
//	  togglePA4();
//	  HAL_Delay(2000);
//	  togglePA5();
//	  HAL_Delay(2000);
//	  togglePA6();
//	  HAL_Delay(2000);
//	  togglePA7();
//	  HAL_Delay(2000);
//	  togglePA8();
//	  HAL_Delay(2000);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, PA4_Pin|PA5_Pin|PA6_Pin|PA7_Pin
                          |PA8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4_Pin PA5_Pin PA6_Pin PA7_Pin
                           PA8_Pin */
  GPIO_InitStruct.Pin = PA4_Pin|PA5_Pin|PA6_Pin|PA7_Pin
                          |PA8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	SCH_Update();
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
