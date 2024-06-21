#include "main.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "DummyTask.h"
#include "at86rf215.hpp"
#include "at86rf215config.hpp"
#include "MCUTemperatureTask.hpp"
#include "txUHFTask.hpp"
#include "UARTGatekeeperTask.hpp"
#include "TemperatureSensorsTask.hpp"
#include "TimeKeepingTask.hpp"
#include "TCHandlingTask.hpp"
#include <string>

extern UART_HandleTypeDef huart3;
xTaskHandle task1_handler;
xTaskHandle task2_handler;



template<class T>
static void vClassTask(void *pvParameters) {
    (static_cast<T *>(pvParameters))->execute();
}

QueueHandle_t myqueue;

void Task1(void * pvParameters){
    for(;;){
        LOG_DEBUG << "task1";
        static uint32_t item=0;
        if(xQueueSend(myqueue,(void*) &item,100)==errQUEUE_FULL)
        {
            xTaskNotifyGive(task2_handler);
            vTaskDelay(1000);
        };
        item ++;
        vTaskDelay(500);
        HAL_GPIO_TogglePin(GPIOB,LD1_Pin);

    }
}

void Task2(void * pvParameters){
    for(;;){
        LOG_DEBUG << "task2";
        if( ulTaskNotifyTake(pdTRUE,10000))
        {
            for (int i=0; i<10; i++)
            {
                uint32_t received_item;
                xQueueReceive(myqueue,(void *) &received_item,100);
                LOG_DEBUG << std::to_string(received_item);
                vTaskDelay(10);
            }
        }

        vTaskDelay(50);
    }
}




extern "C" void main_cpp(){



    myqueue = xQueueCreate( 10, 4);
    uartGatekeeperTask.emplace();
    uartGatekeeperTask->createTask();
    xTaskCreate(Task1, "blinkyTask 2", 1000, nullptr, tskIDLE_PRIORITY + 1, &task1_handler);
    xTaskCreate(Task2, "blinkyTask 2", 1000, nullptr, tskIDLE_PRIORITY + 1, &task2_handler);
    vTaskStartScheduler();

    /**
     * Uncomment below and comment above for Led task visualization (for STM32H743)
     */

    for(;;);
    return;
}

