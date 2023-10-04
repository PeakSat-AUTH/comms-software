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

extern UART_HandleTypeDef huart3;


template<class T>
static void vClassTask(void *pvParameters) {
    (static_cast<T *>(pvParameters))->execute();
}

void Task1(void * pvParameters){
    for(;;){

    }
}

void Task2(void * pvParameters){
    for(;;){

    }
}



extern "C" void main_cpp(){

    xTaskCreate(Task1, "blinkyTask 2", 1000, nullptr, tskIDLE_PRIORITY + 1, nullptr);
    xTaskCreate(Task2, "blinkyTask 2", 1000, nullptr, tskIDLE_PRIORITY + 1, nullptr);
    vTaskStartScheduler();

    /**
     * Uncomment below and comment above for Led task visualization (for STM32H743)
     */

    for(;;);
    return;
}

