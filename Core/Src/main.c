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
#include "User_SD_Card.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "MSGPack.h"
#include "USB_Data.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define _TESTING_ 1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SD_HandleTypeDef hsd;
uint8_t receiveBuffer[4096];
struct USBDataReceived usbDataReceived;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config ( void );

static void MX_GPIO_Init ( void );

static void MX_SDIO_SD_Init ( void );
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void testing ( SDcardTypeDef sdcard );
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

int main ( void ) {

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init( );

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config( );

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init( );
    MX_SDIO_SD_Init( );
    MX_FATFS_Init( );
    MX_USB_DEVICE_Init( );
    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */
    HAL_Delay( 2000 );

    // TODO: Exception control

#if _TESTING_ == 0
    testing(sdcard);
#endif

    SDcardTypeDef sdcard;

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    usbDataReceived.isNewData = false;

    // TODO: No está logs? Crea logs
    MKDIR_SD(&sdcard, "logs\0" );

    while ( true ) {
        if ( usbDataReceived.isNewData ) {

            // TODO: Extract the folder from the fileName

            char data[1000] = { '\0' };
            char reading[1000] = { '\0' };
            UINT size = 0;

            Mount_SD( &sdcard, "" );
            if ( usbDataReceived.usbData.command == WRITE ) {

                if ( sdcard.fResult == FR_OK ) {
                    CreateAndWriteFile_SD( &sdcard,
                                           usbDataReceived.usbData.fileName,
                                           usbDataReceived.usbData.content );
                }

            } else if ( usbDataReceived.usbData.command == READ ) {

                if ( sdcard.fResult == FR_OK ) {
                    ReadFile_SD( &sdcard,
                                 usbDataReceived.usbData.fileName,
                                 reading,
                                 &size );
                }

                if ( sdcard.fResult == FR_OK ) {
                    reading[size] = '\0';
                    strcpy( usbDataReceived.usbData.content, reading );
                }


            } else if ( usbDataReceived.usbData.command == DELETE ) {

                if ( sdcard.fResult == FR_OK ) {
                    EraseFile_SD(&sdcard, usbDataReceived.usbData.fileName );
                }

                if ( sdcard.fResult == FR_OK ) {
                    reading[size] = '\0';
                    strcpy( usbDataReceived.usbData.content, "Success\0" );
                }

            } else if ( usbDataReceived.usbData.command == UPDATE ) {

                if ( sdcard.fResult == FR_OK ) {
                    // TODO: update or erase content
                    UpdateFile_SD( &sdcard,
                                   usbDataReceived.usbData.fileName,
                                   usbDataReceived.usbData.content );
                }

                if ( sdcard.fResult == FR_OK ) {
                    ReadFile_SD( &sdcard,
                                 usbDataReceived.usbData.fileName,
                                 reading,
                                 &size );
                }

                if ( sdcard.fResult == FR_OK ) {
                    reading[size] = '\0';
                    strcpy( usbDataReceived.usbData.content, reading );
                }

            } else if ( usbDataReceived.usbData.command == PRINT ) {

                char path[256];
                if ( sdcard.fResult == FR_OK ) {
                    strcpy( path, "LOGS\0" );
                    scan_files( &sdcard, path, &usbDataReceived.usbData );
                    strcpy( usbDataReceived.usbData.fileName, "-" );
                }

            } else {

                usbDataReceived.usbData.command = C_ERROR;

            }

            usbDataReceived.isNewData = false;
            // TODO: Create a usbDataToSend
            if ( sdcard.fResult != FR_OK ) {
                usbDataReceived.usbData.command = C_ERROR;
                strcpy( usbDataReceived.usbData.fileName, "-" );
                strcpy( usbDataReceived.usbData.content, sdcard.message );
            }

            UnpackMSG( &usbDataReceived.usbData, data );

            size = strlen( data );
            Unmount_SD( &sdcard, "" );
            CDC_Transmit_FS(( uint8_t * ) data, size );
            HAL_Delay( 1 );
        }

        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config ( void ) {
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE( );
    __HAL_PWR_VOLTAGESCALING_CONFIG( PWR_REGULATOR_VOLTAGE_SCALE1 );

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 168;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if ( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK ) {
        Error_Handler( );
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if ( HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_5 ) != HAL_OK ) {
        Error_Handler( );
    }
}

/**
  * @brief SDIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDIO_SD_Init ( void ) {

    /* USER CODE BEGIN SDIO_Init 0 */

    /* USER CODE END SDIO_Init 0 */

    /* USER CODE BEGIN SDIO_Init 1 */

    /* USER CODE END SDIO_Init 1 */
    hsd.Instance = SDIO;
    hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
    hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
    hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
    hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
    hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
    hsd.Init.ClockDiv = 0;
    /* USER CODE BEGIN SDIO_Init 2 */

    /* USER CODE END SDIO_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init ( void ) {
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE( );
    __HAL_RCC_GPIOA_CLK_ENABLE( );
    __HAL_RCC_GPIOC_CLK_ENABLE( );
    __HAL_RCC_GPIOD_CLK_ENABLE( );

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET );

    /*Configure GPIO pin : PA1 */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct );

}

/* USER CODE BEGIN 4 */

void testing ( SDcardTypeDef sdcard ) {
    char reading[1000] = "";
    UINT size = 0;
    Mount_SD( &sdcard, "" );

    if ( sdcard.fResult == FR_OK ) {
        CreateAndWriteFile_SD( &sdcard, "file_1.txt", "Lorem ipsum dolor sit amet.\n" );
    }

    if ( sdcard.fResult == FR_OK ) {
        CreateAndWriteFile_SD( &sdcard, "file_2.txt", "Lorem ipsum dolor sit amet.\n" );
    }

    if ( sdcard.fResult == FR_OK ) {
        ReadFile_SD( &sdcard, "3.txt", reading, &size );
        HAL_Delay( 1000 );
        CDC_Transmit_FS(( uint8_t * ) reading, size );
        HAL_Delay( 1 );
    }

    if ( sdcard.fResult == FR_OK ) {
        UpdateFile_SD( &sdcard, "file_1.txt", "File created.\n" );
    }

    if ( sdcard.fResult == FR_OK ) {
        UINT bytes = 0;
        ReadFile_SD( &sdcard, "file_1.txt", reading, &bytes );
    }

    if ( sdcard.fResult == FR_OK ) {
        EraseFile_SD(&sdcard, "file_2.txt" );
    }

    MKDIR_SD(&sdcard, "folder" );

    if ( sdcard.fResult == FR_OK ) {
        CreateAndWriteFile_SD( &sdcard, "folder/file_1.txt", "Folder created.\n" );
    }

    Unmount_SD( &sdcard, "" );
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler ( void ) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq( );
    while ( 1 ) {
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
