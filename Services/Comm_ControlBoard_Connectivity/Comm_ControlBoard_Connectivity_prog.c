/* USER CODE BEGIN Header */
/**
 ***********************************************************************************************
 * @file           : Comm_ControlBoard_Connectivity_prog.c
 * @brief          : the code of the nucleo to communicate with connectivity module
 * @version		   : V1.0
 * @Date		   : 27/11/2024
 * @Author		   : Mostafa Edrees
 * @Email		   : mostafaedrees018@gmail.com
 ***********************************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdint.h>
#include "string.h"

#include "main.h"

#include "stm32f4xx_hal.h"

#include "Comm_ControlBoard_Connectivity_config.h"
#include "Comm_ControlBoard_Connectivity_priv.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define RxBuf_SIZE   			(5 * sizeof(userData))
#define DB_Backup_SIZE 			(10 * sizeof(userData))

uint8_t RxBuf[RxBuf_SIZE];
uint8_t DB_Backup[DB_Backup_SIZE];

uint16_t oldPos = 0;
uint16_t newPos = 0;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

//userData *Users_Profile_Rx = (userData *)(ADDRESS_DESTINATION_DATA);

extern UART_HandleTypeDef huart_comm_ctrlboard_connectivity;
extern DMA_HandleTypeDef hdma_comm_ctrlboard_connectivity_tx;
extern DMA_HandleTypeDef hdma_comm_ctrlboard_connectivity_rx;
extern DMA_HandleTypeDef hdma_comm_ctrlboard_connectivity;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


/**
 * @brief  Initialize the Communication between the control board
 * 		and the connectivity board according to the configuration
 * 		in the Comm_ControlBoard_Connectivity_config.h file
 * @param  None
 * @retval None
 */
void Comm_CtrlBoard_Connectivity_voidInit(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Initialize all configured peripherals */
	MX_DMA_Init();

	if (HAL_UART_Init(&huart_comm_ctrlboard_connectivity) != HAL_OK)
	{
		Error_Handler();
	}

}


/**
 * @brief  DeInitialize the Communication between the control board
 * 		and the connectivity board.
 * @param  None
 * @retval None
 */
void Comm_CtrlBoard_Connectivity_voidDeInit(void)
{
	HAL_UART_MspDeInit(&huart_comm_ctrlboard_connectivity);
}


/**
 * @brief  Start Communication between the control board
 * 		and the connectivity board to receive the data
 * 		sent by the connectivity module.
 * @param  Copy_Pu8Src_Address_Data a pointer to the source
 * 		address of the data that we will receive data at it.
 * @param	Copy_u16DataSize the length of the data that we will
 * 		send it by UART.
 * @retval None
 */
void Comm_CtrlBoard_Connectivity_voidStart_CommunicationTx(uint8_t *Copy_Pu8Src_Address_Data, uint16_t Copy_u16DataSize)
{
	if(HAL_UART_Transmit_DMA(&huart_comm_ctrlboard_connectivity, Copy_Pu8Src_Address_Data, Copy_u16DataSize) != HAL_OK)
	{
		Error_Handler();
	}
}


/**
 * @brief  Start Communication between the control board
 * 		and the connectivity board to receive the data
 * 		sent by the connectivity module.
 * @param  Copy_Pu8Dest_Address_Data a pointer to the destination
 * 		address of the data that we will receive data at it.
 * @param	Copy_u16DataSize the length of the data that we will
 * 		receive it by UART.
 * @retval None
 */
void Comm_CtrlBoard_Connectivity_voidStart_CommunicationRx(uint8_t *Copy_Pu8Dest_Address_Data)
{
	//	if(HAL_UART_Receive_DMA(&huart_comm_ctrlboard_connectivity, Copy_Pu8Dest_Address_Data, Copy_u16DataSize) != HAL_OK)
	//	{
	//		Error_Handler();
	//	}

	HAL_StatusTypeDef Local_enuHALstate = HAL_UARTEx_ReceiveToIdle_DMA(&huart_comm_ctrlboard_connectivity, RxBuf, RxBuf_SIZE);
	__HAL_DMA_DISABLE_IT(&hdma_comm_ctrlboard_connectivity_rx, DMA_IT_HT);

	if(Local_enuHALstate != HAL_OK)
	{
		Error_Handler();
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_8)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		/* Send Remote Frame to Bluepill to get GPS Reading */
		//CAN Code
		/* Toggling PB5 to make external interrupts on bluepill to tell it that we need gps readings */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET);

		/* Send GPS Reading to Connectivity or set flag to be ready to send data when we receive it */
		//UART Code
	}

	if(GPIO_Pin == GPIO_PIN_7)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		/* Call UART DMA to be ready to receive new data */
		Comm_CtrlBoard_Connectivity_voidStart_CommunicationRx((uint8_t *)DB_Backup);
	}
}


/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void)
{
	if(hdma_comm_ctrlboard_connectivity_rx.Instance == DMA1_Stream5)
	{
		/* DMA controller clock enable */
		__HAL_RCC_DMA1_CLK_ENABLE();

		/* DMA interrupt init */
		/* DMA1_Stream5_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	}
	else if(hdma_comm_ctrlboard_connectivity_tx.Instance == DMA2_Stream7)
	{
		/* DMA controller clock enable */
		__HAL_RCC_DMA2_CLK_ENABLE();

		/* DMA interrupt init */
		/* DMA2_Stream7_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	}
	else if(hdma_comm_ctrlboard_connectivity_rx.Instance == DMA2_Stream2)
	{
		/* DMA controller clock enable */
		__HAL_RCC_DMA2_CLK_ENABLE();

		/* DMA interrupt init */
		/* DMA2_Stream2_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	}

}

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(huart->Instance==USART1)
	{
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART1 DMA Init */
		/* USART1_RX Init */
		//		hdma_comm_ctrlboard_connectivity.Instance = DMA2_Stream2;
		//		hdma_comm_ctrlboard_connectivity.Init.Channel = DMA_CHANNEL_4;
		//		hdma_comm_ctrlboard_connectivity.Init.Direction = DMA_PERIPH_TO_MEMORY;
		//		hdma_comm_ctrlboard_connectivity.Init.PeriphInc = DMA_PINC_DISABLE;
		//		hdma_comm_ctrlboard_connectivity.Init.MemInc = DMA_MINC_ENABLE;
		//		hdma_comm_ctrlboard_connectivity.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		//		hdma_comm_ctrlboard_connectivity.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		//		hdma_comm_ctrlboard_connectivity.Init.Mode = DMA_NORMAL;
		//		hdma_comm_ctrlboard_connectivity.Init.Priority = DMA_PRIORITY_LOW;
		//		hdma_comm_ctrlboard_connectivity.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_comm_ctrlboard_connectivity_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(huart,hdmatx,hdma_comm_ctrlboard_connectivity_tx);

		if (HAL_DMA_Init(&hdma_comm_ctrlboard_connectivity_rx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(huart,hdmarx,hdma_comm_ctrlboard_connectivity_rx);

		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);

		/* USER CODE END USART1_MspInit 1 */
	}
	else if(huart->Instance==USART2)
	{
		/* USER CODE BEGIN USART2_MspInit 0 */

		/* USER CODE END USART2_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART2 DMA Init */
		/* USART2_RX Init */
		hdma_comm_ctrlboard_connectivity.Instance = DMA1_Stream5;
		hdma_comm_ctrlboard_connectivity.Init.Channel = DMA_CHANNEL_4;
		hdma_comm_ctrlboard_connectivity.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_comm_ctrlboard_connectivity.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_comm_ctrlboard_connectivity.Init.MemInc = DMA_MINC_ENABLE;
		hdma_comm_ctrlboard_connectivity.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_comm_ctrlboard_connectivity.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_comm_ctrlboard_connectivity.Init.Mode = DMA_NORMAL;
		hdma_comm_ctrlboard_connectivity.Init.Priority = DMA_PRIORITY_LOW;
		hdma_comm_ctrlboard_connectivity.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_comm_ctrlboard_connectivity) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(huart,hdmarx,hdma_comm_ctrlboard_connectivity);

		/* USER CODE BEGIN USART2_MspInit 1 */

		/* USER CODE END USART2_MspInit 1 */
	}

}

/**
 * @brief UART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
	if(huart->Instance==USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

		/* USART1 DMA DeInit */
		HAL_DMA_DeInit(huart->hdmatx);

		/* USART1 DMA DeInit */
		HAL_DMA_DeInit(huart->hdmarx);

		/* USART1 interrupt DeInit */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}
	else if(huart->Instance==USART2)
	{
		/* USER CODE BEGIN USART2_MspDeInit 0 */

		/* USER CODE END USART2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

		/* USART2 DMA DeInit */
		HAL_DMA_DeInit(huart->hdmarx);
		/* USER CODE BEGIN USART2_MspDeInit 1 */

		/* USER CODE END USART2_MspDeInit 1 */
	}

}

/* USER CODE BEGIN 4 */

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//	static int cnt = 0;
	//	cnt++;
}

///**
// * @brief  Rx Transfer completed callbacks.
// * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
// *                the configuration information for the specified UART module.
// * @retval None
// */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//
//}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART1)
	{
		oldPos = newPos;  // Update the last position before copying new data

		/* If the data in large and it is about to exceed the buffer size, we have to route it to the start of the buffer
		 * This is to maintain the circular buffer
		 * The old data in the main buffer will be overlapped
		 */
		if (oldPos+Size > DB_Backup_SIZE)  // If the current position + new data size is greater than the main buffer
		{
			uint16_t datatocopy = DB_Backup_SIZE-oldPos;  // find out how much space is left in the main buffer
			memcpy ((uint8_t *)DB_Backup+oldPos, RxBuf, datatocopy);  // copy data in that remaining space

			oldPos = 0;  // point to the start of the buffer
			memcpy ((uint8_t *)DB_Backup, (uint8_t *)RxBuf+datatocopy, (Size-datatocopy));  // copy the remaining data
			newPos = (Size-datatocopy);  // update the position
		}

		/* if the current position + new data size is less than the main buffer
		 * we will simply copy the data into the buffer and update the position
		 */
		else
		{
			memcpy ((uint8_t *)DB_Backup+oldPos, RxBuf, Size);
			newPos = Size+oldPos;
		}
	}
}

/* USER CODE END 4 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

