/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : Comm_ControlBoard_Connectivity_int.h
 * @brief          : Header for Comm_ControlBoard_Connectivity_prog.c file.
 *                   This file contains the prototypes of functions that used
 *                   to initialize & de-initialize & start the communication
 *                   between the ctrl_board and the connectivity module.
 * @version		   : V1.0
 * @Date		   : 27/11/2024
 * @Author		   : Mostafa Edrees
 * @Email		   : mostafaedrees018@gmail.com
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef COMM_CONTROLBOARD_CONNECTIVITY_COMM_CONTROLBOARD_CONNECTIVITY_INT_H_
#define COMM_CONTROLBOARD_CONNECTIVITY_COMM_CONTROLBOARD_CONNECTIVITY_INT_H_

/* Includes ------------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

void Comm_CtrlBoard_Connectivity_voidInit(void);
void Comm_CtrlBoard_Connectivity_voidDeInit(void);
void Comm_CtrlBoard_Connectivity_voidStart_Communication(uint8_t *Copy_Pu8Dest_Address_Data, uint16_t Copy_u16DataSize);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#endif /* COMM_CONTROLBOARD_CONNECTIVITY_COMM_CONTROLBOARD_CONNECTIVITY_INT_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
