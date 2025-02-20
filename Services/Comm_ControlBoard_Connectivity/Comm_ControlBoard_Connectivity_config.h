/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : Comm_ControlBoard_Connectivity_config.h
 * @brief          : Header for Comm_ControlBoard_Connectivity_prog.c file.
 *                   This file contains the configuration parameters of the
 *                   communication between the control board (Nucleo-Board)
 *                   and the connectivity module (esp32).
 * @version		   : V1.0
 * @Date		   : 27/11/2024
 * @Author		   : Mostafa Edrees
 * @Email		   : mostafaedrees018@gmail.com
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef COMM_CONTROLBOARD_CONNECTIVITY_COMM_CONTROLBOARD_CONNECTIVITY_CONFIG_H_
#define COMM_CONTROLBOARD_CONNECTIVITY_COMM_CONTROLBOARD_CONNECTIVITY_CONFIG_H_

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define OFFSET_Tx										0x200
#define ADDRESS_SOURCE_DATA								(uint8_t *)((SRAM1_BASE) + (OFFSET_Tx))
#define DATA_SIZE_Tx									100u

#define OFFSET_Rx										0x800
#define ADDRESS_DESTINATION_DATA						(uint8_t *)((SRAM1_BASE) + (OFFSET_Rx))

#define NUM_USER										(1u)
#define DATA_SIZE_Rx									(uint16_t)(67 * NUM_USER)

typedef enum __attribute__((__packed__))
{
  Door_Off,
  Door_On
}Door_Access;

typedef enum __attribute__((__packed__))
{
  Engine_Off,
  Engine_On
}Engine_Access;

typedef enum __attribute__((__packed__))
{
  Trunk_Off,
  Trunk_On
}Trunk_Access;

typedef struct __attribute__((__packed__))
{
    char user_id[30];
    char user_name[30];

    unsigned int speed_limit;

    Door_Access door;
    Engine_Access engine;
    Trunk_Access trunk;

} userData;

/* USER CODE END Private defines */

#endif /* COMM_CONTROLBOARD_CONNECTIVITY_COMM_CONTROLBOARD_CONNECTIVITY_CONFIG_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
