/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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
#include "cmsis_os.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "my_plc.h"
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
I2C_HandleTypeDef hi2c1;

osThreadId ProcessUSBdataHandle;
osThreadId myBTN1Handle;
osThreadId myLED1Handle;
osThreadId myBTN2Handle;
osThreadId myBTN3Handle;
osThreadId myBTN4Handle;
osThreadId myLED2Handle;
osThreadId myLED3Handle;
osThreadId myLED4Handle;
osThreadId mySyncHandle;
osThreadId myI2CHandle;
osThreadId myTransmitUSBHandle;
osMessageQId SyncQueueHandle;
osMessageQId I2C_QueueHandle;
osMutexId mutexI2CHandle;
osSemaphoreId userDataRecievedHandle;
osSemaphoreId usrSendBufAvailHandle;
/* USER CODE BEGIN PV */
extern EventGroupHandle_t xMyEventGroup;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
void StartProcessUSBdata(void const * argument);
extern void StartButtons(void const * argument);
extern void StartLED(void const * argument);
extern void StartSync(void const * argument);
extern void StartI2C(void const * argument);
extern void StartTransmitUSB(void const * argument);

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Create the mutex(es) */
  /* definition and creation of mutexI2C */
  osMutexDef(mutexI2C);
  mutexI2CHandle = osMutexCreate(osMutex(mutexI2C));

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of userDataRecieved */
  osSemaphoreDef(userDataRecieved);
  userDataRecievedHandle = osSemaphoreCreate(osSemaphore(userDataRecieved), 1);

  /* definition and creation of usrSendBufAvail */
  osSemaphoreDef(usrSendBufAvail);
  usrSendBufAvailHandle = osSemaphoreCreate(osSemaphore(usrSendBufAvail), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of SyncQueue */
  osMessageQDef(SyncQueue, 3, QDATA_T);
  SyncQueueHandle = osMessageCreate(osMessageQ(SyncQueue), NULL);

  /* definition and creation of I2C_Queue */
  osMessageQDef(I2C_Queue, 3, QDATA_T);
  I2C_QueueHandle = osMessageCreate(osMessageQ(I2C_Queue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
	xMyEventGroup = xEventGroupCreate();
	if (xMyEventGroup == NULL) {
		/* The event group was not created because there was insufficient
		 FreeRTOS heap available. */
	} else {
		/* The event group was created. */
	}
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of ProcessUSBdata */
  osThreadDef(ProcessUSBdata, StartProcessUSBdata, osPriorityNormal, 0, 256);
  ProcessUSBdataHandle = osThreadCreate(osThread(ProcessUSBdata), NULL);

  /* definition and creation of myBTN1 */
  osThreadDef(myBTN1, StartButtons, osPriorityBelowNormal, 0, 64);
  myBTN1Handle = osThreadCreate(osThread(myBTN1), (void*) 1);

  /* definition and creation of myLED1 */
  osThreadDef(myLED1, StartLED, osPriorityLow, 0, 64);
  myLED1Handle = osThreadCreate(osThread(myLED1), (void*) 1);

  /* definition and creation of myBTN2 */
  osThreadDef(myBTN2, StartButtons, osPriorityBelowNormal, 0, 64);
  myBTN2Handle = osThreadCreate(osThread(myBTN2), (void*) 2);

  /* definition and creation of myBTN3 */
  osThreadDef(myBTN3, StartButtons, osPriorityNormal, 0, 64);
  myBTN3Handle = osThreadCreate(osThread(myBTN3), (void*) 3);

  /* definition and creation of myBTN4 */
  osThreadDef(myBTN4, StartButtons, osPriorityIdle, 0, 64);
  myBTN4Handle = osThreadCreate(osThread(myBTN4), (void*) 4);

  /* definition and creation of myLED2 */
  osThreadDef(myLED2, StartLED, osPriorityLow, 0, 64);
  myLED2Handle = osThreadCreate(osThread(myLED2), (void*) 2);

  /* definition and creation of myLED3 */
  osThreadDef(myLED3, StartLED, osPriorityLow, 0, 64);
  myLED3Handle = osThreadCreate(osThread(myLED3), (void*) 3);

  /* definition and creation of myLED4 */
  osThreadDef(myLED4, StartLED, osPriorityLow, 0, 64);
  myLED4Handle = osThreadCreate(osThread(myLED4), (void*) 4);

  /* definition and creation of mySync */
  osThreadDef(mySync, StartSync, osPriorityBelowNormal, 0, 140);
  mySyncHandle = osThreadCreate(osThread(mySync), NULL);

  /* definition and creation of myI2C */
  osThreadDef(myI2C, StartI2C, osPriorityAboveNormal, 0, 96);
  myI2CHandle = osThreadCreate(osThread(myI2C), NULL);

  /* definition and creation of myTransmitUSB */
  osThreadDef(myTransmitUSB, StartTransmitUSB, osPriorityNormal, 0, 92);
  myTransmitUSBHandle = osThreadCreate(osThread(myTransmitUSB), NULL);

  /* USER CODE BEGIN RTOS_THREADS */

	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : BTN1_Pin BTN2_Pin BTN3_Pin BTN4_Pin */
  GPIO_InitStruct.Pin = BTN1_Pin|BTN2_Pin|BTN3_Pin|BTN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartProcessUSBdata */
/**
 * @brief  Function implementing the ProcessUSBdata thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartProcessUSBdata */
__weak void StartProcessUSBdata(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 5 */

  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM11 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM11)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
