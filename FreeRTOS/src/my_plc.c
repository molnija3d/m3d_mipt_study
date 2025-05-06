/*
 * my_plc.c
 *
 *  Created on: Apr 30, 2025
 *      Author: EZ-GPRO
 */

#include "cmsis_os.h"
#include "usb_device.h"

#include <inttypes.h>
#include <limits.h>
#include "usbd_cdc_if.h"
#include "EEPROM.h"
#include "my_plc.h"

/*USB buffer*/
char pcUBuf[usrBUF];

/*Commands buffer*/
static char *pxCommand[] = { "Save", "Load", "Show", "Check", "Reset" };
/*USB answer buffer*/
static char pcAnswer[64] = { 0 };

/*Tasks Handler array*/
osThreadId *myLED[] = { &myLED1Handle, &myLED2Handle, &myLED3Handle,
		&myLED4Handle };

EventGroupHandle_t xMyEventGroup;

HightStack_T xUserStack;
/**
 * @brief Just printing a header
 * @param argument: Not used
 * @retval None
 */
void vUserPrintHelp(void) {

	/*checking if Transmit buffer is available*/
	if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
		sprintf(pcAnswer, "\nWRONG PARAMS\n");
		/*Sending a notify to the Transmission Task*/
		xTaskNotifyGive(myTransmitUSBHandle);
	}

	if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
		sprintf(pcAnswer, "LED[0-3] BUTTON MASK[0x1-0xFF] AND/OR[0-1]\n");
		xTaskNotifyGive(myTransmitUSBHandle);
	}
	if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
		sprintf(pcAnswer, "example:[0 0x9 1]\n");
		xTaskNotifyGive(myTransmitUSBHandle);
	}

	if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
		sprintf(pcAnswer, "Available commands: \n");
		xTaskNotifyGive(myTransmitUSBHandle);
	}
	if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
		sprintf(pcAnswer, "[Save], [Load], [Show], [Reset], [Check]\n");
		xTaskNotifyGive(myTransmitUSBHandle);
	}

}

/* USER CODE BEGIN tartTransmitUSB */
/**
 * @brief  Function implementing the ProcessUSBdata thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END tartTransmitUSB */
void StartTransmitUSB(void const *argument) {
	/* USER CODE BEGIN StartTransmitUSB */
	/* Infinite loop */

	xUserStack.TransmitUSB = uxTaskGetStackHighWaterMark( NULL);
	size_t uLen = 0;
	for (;;) {
		/*Checking if there is any new data available*/
		if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY)) {
			uLen = strlen(pcAnswer);
			if (uLen) {
				CDC_Transmit_FS((uint8_t*) pcAnswer, uLen);
			}
			/*unlocking transmission buffer*/
			xSemaphoreGive(usrSendBufAvailHandle);
		}
		osDelay(1);
		/*Checking high stack watermark*/
		xUserStack.TransmitUSB = uxTaskGetStackHighWaterMark( NULL);
	}
	/* USER CODE END StartTransmitUSB */
}
/* USER CODE BEGIN Header_StartProcessUSBdata */
/**
 * @brief  Function implementing the ProcessUSBdata thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartProcessUSBdata */
void StartProcessUSBdata(void const *argument) {
	/* init code for USB_DEVICE */
	MX_USB_DEVICE_Init();
	/* USER CODE BEGIN 5 */
	Parameters_T xBuff;
	QDATA_T xData;

	xUserStack.ProcessUSBdata = uxTaskGetStackHighWaterMark( NULL);

	/* Infinite loop */
	for (;;) {

		xSemaphoreTake(userDataRecievedHandle, portMAX_DELAY);
		xBuff = (Parameters_T ) { 0, 0, 0 };
		sscanf(pcUBuf, "%hu %hu %hu", &xBuff.id, &xBuff.mask, &xBuff.and);
		if (xBuff.id < 4 && xBuff.mask > 0) {
			xData.cmd = C_SET;
			xData.data = (uint32_t*) &xBuff;
			xData.size = sizeof(xBuff);
			xQueueSend(SyncQueueHandle, (const void* )&xData, 10);

			/*If transission buffer is available fill it with new data*/
			if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
				sprintf(pcAnswer, "LED= %hu | MASK= %hu | AND= %hu\n", xBuff.id,
						xBuff.mask, xBuff.and);
			}

		} else {
			for (int i = 0; i < userCOMMANDS; i++) {
				if (strncmp(pcUBuf, pxCommand[i], strlen(pxCommand[i])) == 0) {
					switch (i) {
					case 0: //"Save"
						xData.cmd = C_SAVE;
						/*If transission buffer is available fill it with new data*/
						if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
							sprintf(pcAnswer, "Saving config...\n");
						}
						goto gFinish;

					case 1: //"Load"
						xData.cmd = C_LOAD;
						/*If transmission buffer is available fill it with new data*/
						if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
							sprintf(pcAnswer, "Loading config...\n");
						}
						goto gFinish;

					case 2: //"Restore"
						xData.cmd = C_SHOW;
						/*If transmission buffer is available fill it with new data*/
						if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
							sprintf(pcAnswer, "Current settings are:\n");
						}
						goto gFinish;

					case 3: //"Check"
						xData.cmd = C_CHECK;
						/*If transmission buffer is available fill it with new data*/
						if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
							sprintf(pcAnswer, "Checking config...\n");
						}

						goto gFinish;
					case 4: //"Reset"
						xData.cmd = C_RESET;
						HAL_NVIC_SystemReset();
						goto gFinish;

					}
				}
			}
			xData.cmd = C_NONE;
			/*Printing a header*/
			vUserPrintHelp();
		}

		gFinish: if (xData.cmd != C_NONE) {
			xQueueSend(SyncQueueHandle, (const void* )&xData, 1);
		}

		/*Buffer is ready, notifying the Transmission Task*/
		xTaskNotifyGive(myTransmitUSBHandle);

	}
	xUserStack.ProcessUSBdata = uxTaskGetStackHighWaterMark( NULL);
	osDelay(1);

}
/* USER CODE END 5 */

/* USER CODE BEGIN Header_StartButtons */
/**
 * @brief Function implementing the myBTN1 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartButtons */
void StartButtons(void const *argument) {
	/* USER CODE BEGIN StartButtons */
	/* Infinite loop */
	GPIO_TypeDef *pxPort;
	uint16_t uPin;
	uint16_t uBtnStatus = 0;
	EventBits_t mask = 0;
	/*argument == Button port number*/
	int sButton = (int) ((const int*) argument);
	mask = 1 << (sButton - 1);
	switch (sButton) {
	case 1:
		pxPort = usrBtnPort(1);
		uPin = usrBtnPin(1);

		break;
	case 2:
		pxPort = usrBtnPort(2);
		uPin = usrBtnPin(2);

		break;
	case 3:
		pxPort = usrBtnPort(3);
		uPin = usrBtnPin(3);

		break;
	case 4:
		pxPort = usrBtnPort(4);
		uPin = usrBtnPin(4);

		break;
	default:
		pxPort = usrBtnPort(1);
		uPin = usrBtnPin(1);
		mask = 0xF;
	}
	xUserStack.Buttons = uxTaskGetStackHighWaterMark( NULL);
	for (;;) {
		/*Debounce*/
		uBtnStatus <<= 1;
		if (HAL_GPIO_ReadPin(pxPort, uPin) == GPIO_PIN_SET) {
			uBtnStatus |= 1;
		} else {
			//button_status = 0;
		}
		/*Event group management*/
		if (uBtnStatus > 0xFF) {
			xEventGroupSetBits(xMyEventGroup, mask);
		}
		if (uBtnStatus == 0) {
			xEventGroupClearBits(xMyEventGroup, mask);
		}
		osDelay(5);
		xUserStack.Buttons = uxTaskGetStackHighWaterMark( NULL);
	}
	/* USER CODE END StartButtons */
}

/* USER CODE BEGIN Header_StartLED */
/**
 * @brief Function implementing the myLED1 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartLED */
void StartLED(void const *argument) {
	/* USER CODE BEGIN StartLED */
	/* Infinite loop */
	GPIO_TypeDef *pxPort;
	uint16_t uPin;
	uint32_t xResult;
	uint32_t pulNotificationValue;

	/*argument == LED port number*/
	int led = (int) ((const int*) argument);
	switch (led) {
	case 1:
		pxPort = usrLedPort(1);
		uPin = usrLedPin(1);

		break;
	case 2:
		pxPort = usrLedPort(2);
		uPin = usrLedPin(2);

		break;
	case 3:
		pxPort = usrLedPort(3);
		uPin = usrLedPin(3);

		break;
	case 4:
		pxPort = usrLedPort(4);
		uPin = usrLedPin(4);
		break;
	default:

		pxPort = usrLedPort(1);
		uPin = usrLedPin(1);
	}
	xUserStack.LED = uxTaskGetStackHighWaterMark( NULL);
	for (;;) {
		xResult = xTaskNotifyWait(pdFALSE, ULONG_MAX, &pulNotificationValue,
		portMAX_DELAY);
		if (xResult == pdPASS) {
			if (pulNotificationValue == 0x1) {
				HAL_GPIO_WritePin(pxPort, uPin, GPIO_PIN_RESET);
			}
			if (pulNotificationValue == 0x2) {
				HAL_GPIO_WritePin(pxPort, uPin, GPIO_PIN_SET);
			}
		}

		osDelay(5);
		xUserStack.LED = uxTaskGetStackHighWaterMark( NULL);
	}
	/* USER CODE END StartLED */
}

/* USER CODE BEGIN Header_StartSync */
/**
 * @brief Function implementing the mySync thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSync */
void StartSync(void const *argument) {
	/* USER CODE BEGIN StartSync */
	/* Infinite loop */
	EventBits_t uxBits;
	Parameters_T *pxData, xSynParam[usrPORT_CNT] = { 0 };
	QDATA_T xQParcel, xQBuf;
	uint8_t i = 0;
	BaseType_t qResult;
	xUserStack.Sync = uxTaskGetStackHighWaterMark( NULL);
	for (i = 0; i < usrPORT_CNT; i++) {
		xSynParam[i].mask = 1 << i;
	}
	for (;;) {
		qResult = xQueueReceive(SyncQueueHandle, (void* const ) &xQParcel, 1);
		if (qResult == pdTRUE) {
			pxData = (Parameters_T*) xQParcel.data;

			switch (xQParcel.cmd) {
			case C_SET:
				if (pxData->id < usrPORT_CNT) {
					xSynParam[pxData->id].mask = pxData->mask;
					xSynParam[pxData->id].and = !pxData->and;
				}
				break;
			case C_SAVE:
				/*Using mutex to lock access to I2C*/

				if (xSemaphoreTake(mutexI2CHandle, 0) == pdTRUE) {
					xQParcel.data = (uint32_t*) &xSynParam;
					xQParcel.size = sizeof(xSynParam);
					xQParcel.cmd = C_SAVE;
					xQueueSend(I2C_QueueHandle, (const void* )&xQParcel, 5);
					/*Release mutex*/
					xSemaphoreGive(mutexI2CHandle);
				}
				break;
			case C_LOAD:
				/*Mutex to lock access to I2C*/
				if (xSemaphoreTake(mutexI2CHandle, 0) == pdTRUE) {
					xQBuf.cmd = C_LOAD;
					xQueueSend(I2C_QueueHandle, (const void* )&xQBuf, 5);

					qResult = xQueueReceive(SyncQueueHandle, &xQParcel, 100);
					if (qResult == pdTRUE) {
						pxData = (Parameters_T*) xQParcel.data;
						for (i = 0; i < usrPORT_CNT; i++) {
							xSynParam[i].mask = pxData[i].mask;
							xSynParam[i].and = pxData[i].and;
						}
					}
					/*Release mutex*/
					xSemaphoreGive(mutexI2CHandle);
				}
				break;
			case C_SHOW:

				for (i = 0; i < usrPORT_CNT; i++) {
					/*If transmission buffer is available fill it with new data*/
					if (xSemaphoreTake(usrSendBufAvailHandle, 10)) {
						sprintf(pcAnswer, "LED= %hu MASK= %hu AND= %hu\n", i,
								xSynParam[i].mask, !xSynParam[i].and & 0x1);
						/*Buffer is ready, notifying Transmission Task*/
						xTaskNotifyGive(myTransmitUSBHandle);
					}
				}
				break;
			}
		}
		/*Checking events and sync outputs (LED)*/
		uxBits = xEventGroupWaitBits(xMyEventGroup, 0xFF, pdFALSE, pdFALSE, 0);
		for (i = 0; i < usrPORT_CNT; i++) {
			if (uxBits == xSynParam[i].mask
					|| (xSynParam[i].and && uxBits & xSynParam[i].mask)) {
				xTaskNotify(*myLED[i], 1, eSetBits);
			} else {
				xTaskNotify(*myLED[i], 2, eSetBits);
			}
		}
		osDelay(5);
		xUserStack.Sync = uxTaskGetStackHighWaterMark( NULL);
	}

	/* USER CODE END StartSync */
}

/* USER CODE BEGIN Header_StartI2C */
/**
 * @brief Function implementing the myI2C thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartI2C */
void StartI2C(void const *argument) {
	/* USER CODE BEGIN StartI2C */
	/* Infinite loop */
	BaseType_t qResult;
	xUserStack.I2C = uxTaskGetStackHighWaterMark( NULL);
	for (;;) {
//S_Param_T check;
		QDATA_T xCMD;
		Parameters_T xEepromData[usrPORT_CNT] = { 0 };

		qResult = xQueueReceive(I2C_QueueHandle, (void* const ) &xCMD,
		portMAX_DELAY);
		if (qResult == pdTRUE) {
			switch (xCMD.cmd) {
			case C_SAVE:
				/*Writing data size*/
				EEPROM_Write(0, 0, (uint8_t*) &xCMD.size, 1);
				/*Writing data*/
				EEPROM_Write(0, 1, (uint8_t*) xCMD.data, xCMD.size);
				break;

			case C_LOAD:
				/*Reading data size*/
				EEPROM_Read(0, 0, (uint8_t*) &xCMD.size, 1);
				/*Reading data*/
				EEPROM_Read(0, 1, (uint8_t*) &xEepromData, xCMD.size);
				if (xEepromData->mask) {
					xCMD.data = (uint32_t*) &xEepromData;
					xQueueSend(SyncQueueHandle, (const void* )&xCMD, 1);
				}
				break;
			case C_SHOW:
				break;
			case C_CHECK:
				break;
			case C_RESET:
				break;
			}
		}
		osDelay(10);
		xUserStack.I2C = uxTaskGetStackHighWaterMark( NULL);
	}
	/* USER CODE END StartI2C */
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

