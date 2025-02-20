/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : Comm_ControlBoard_Connectivity_config.c
 * @brief          : This file contains the configuration parameters of the
 *                   communication between the control board (Nucleo-Board)
 *                   and the connectivity module (esp32).
 * @version		   : V1.0
 * @Date		   : 27/11/2024
 * @Author		   : Mostafa Edrees
 * @Email		   : mostafaedrees018@gmail.com
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stm32f4xx_hal.h"

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
/* USER CODE BEGIN PV */

UART_HandleTypeDef huart_comm_ctrlboard_connectivity =
{
		.Instance = USART1,
		.Init.BaudRate = 115200,
		.Init.WordLength = UART_WORDLENGTH_8B,
		.Init.StopBits = UART_STOPBITS_1,
		.Init.Parity = UART_PARITY_NONE,
		.Init.Mode = UART_MODE_TX_RX,
		.Init.HwFlowCtl = UART_HWCONTROL_NONE,
		.Init.OverSampling = UART_OVERSAMPLING_16,
};

/* USART1 DMA Init */
/* USART1_TX Init */
DMA_HandleTypeDef hdma_comm_ctrlboard_connectivity_tx =
{
		.Instance = DMA2_Stream7,
		.Init.Channel = DMA_CHANNEL_4,
		.Init.Direction = DMA_MEMORY_TO_PERIPH,
		.Init.PeriphInc = DMA_PINC_DISABLE,
		.Init.MemInc = DMA_MINC_ENABLE,
		.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
		.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE,
		.Init.Mode = DMA_NORMAL,
		.Init.Priority = DMA_PRIORITY_LOW,
		.Init.FIFOMode = DMA_FIFOMODE_DISABLE,
};

DMA_HandleTypeDef hdma_comm_ctrlboard_connectivity_rx =
{
		.Instance = DMA2_Stream2,
		.Init.Channel = DMA_CHANNEL_4,
		.Init.Direction = DMA_PERIPH_TO_MEMORY,
		.Init.PeriphInc = DMA_PINC_DISABLE,
		.Init.MemInc = DMA_MINC_ENABLE,
		.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
		.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE,
		.Init.Mode = DMA_NORMAL,
		.Init.Priority = DMA_PRIORITY_LOW,
		.Init.FIFOMode = DMA_FIFOMODE_DISABLE,
};

DMA_HandleTypeDef hdma_comm_ctrlboard_connectivity;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
