#include "main.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "DummyTask.h"
#include "at86rf215.hpp"
#include "at86rf215config.hpp"
#include "MCUTemperatureTask.hpp"
#include "UARTGatekeeperTask.hpp"
#include "TemperatureSensorsTask.hpp"
#include "TimeKeepingTask.hpp"
#include "TCHandlingTask.hpp"
#include "CAN.hpp"
#include "stm32h7xx_hal_fdcan.h"
#include "CANGatekeeperTask.hpp"
#include "WatchdogTask.hpp"
#include "StatisticsReportingTask.hpp"
#include "HousekeepingTask.hpp"
#include "TimeBasedSchedulingTask.hpp"
#include "TransceiverTask.hpp"

uint8_t button_flag = 0;

extern "C" void main_cpp(){
    uartGatekeeperTask.emplace();
    //mcuTemperatureTask.emplace();
    //temperatureSensorsTask.emplace();
    //timeKeepingTask.emplace();
    //tcHandlingTask.emplace();
    watchdogTask.emplace();
    //canTestTask.emplace();
    //canGatekeeperTask.emplace();
    //statisticsReportingTask.emplace();
    //housekeepingTask.emplace();
    //timeBasedSchedulingTask.emplace();
    transceiverTask.emplace();


    uartGatekeeperTask->createTask();
    //temperatureSensorsTask->createTask();
    //mcuTemperatureTask->createTask();
    //timeKeepingTask->createTask();
    //tcHandlingTask->createTask();
    watchdogTask->createTask();
    //canTestTask->createTask();
    //canGatekeeperTask->createTask();
    //statisticsReportingTask->createTask();
    //housekeepingTask->createTask();
    //timeBasedSchedulingTask->createTask();
    transceiverTask->createTask();

    vTaskStartScheduler();

    for(;;);
    return;
}

/**
 * HAL_UARTEx_RxEventCallback is a callback function for UART receiving which is enable by the
 * the call of the function HAL_UARTEx_ReceiveToIdle_DMA().
 * It is triggered whenever the UART line is IDLE.
 * @param huart : pointer of type UART_HandleTypeDef
 * @param Size : incoming size of data in bytes
 */
extern "C" void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    // Size is used for copying the correct size of data to the TcCommand buffer,
    // of the TC Handling Task
    tcHandlingTask -> incomingMessageSize = Size;
    BaseType_t xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(tcHandlingTask->taskHandle, 0, eNoAction,  &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    // Reset the DMA to receive the next chunk of data
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, tcHandlingTask->RxDmaBuffer.data(), TcCommandSize);
}

extern "C" void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {
        /* Retreive Rx messages from RX FIFO0 */

        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &CAN::rxHeader0, CAN::rxFifo0.data()) != HAL_OK) {
            /* Reception Error */
            Error_Handler();
        }
        canGatekeeperTask->switchActiveBus(CAN::Redundant);
        CAN::rxFifo0.repair();
        CAN::Frame newFrame = CAN::getFrame(&CAN::rxFifo0, CAN::rxHeader0.Identifier);
        if(CAN::rxFifo0[0] >> 6 == CAN::TPProtocol::Frame::Single){
            canGatekeeperTask->addSFToIncoming(newFrame);
            xTaskNotifyFromISR(canGatekeeperTask->taskHandle, 0, eNoAction, &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }else{
            canGatekeeperTask->addMFToIncoming(newFrame);
            if(CAN::rxFifo0[0] >> 6 == CAN::TPProtocol::Frame::Final){
                xTaskNotifyFromISR(canGatekeeperTask->taskHandle, 0, eNoAction, &xHigherPriorityTaskWoken);
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }

        if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {
            /* Notification Error */
            Error_Handler();
        }
    }
}

/**
 * @brief This function handles EXTI line[15:10] interrupts.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == USER_Btn_Pin)
        button_flag = 1;
}

extern "C" [[maybe_unused]] void EXTI15_10_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(USER_Btn_Pin);
    HAL_GPIO_EXTI_IRQHandler(RF_IRQ_Pin);
    transceiverTask->transceiver.handle_irq();
}


extern "C" void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    // Size is used for copying the correct size of data to the TcCommand buffer,
    // of the TC Handling Task
    BaseType_t xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(gnssTask->taskHandle, 0, eNoAction,  &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    // Reset the DMA to receive the next chunk of data
    HAL_UARTEx_ReceiveToIdle_DMA(&huart5, gnssTask->incomingMessage, 512);

}






