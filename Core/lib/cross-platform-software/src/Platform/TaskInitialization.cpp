#include "TaskInitialization.hpp"
#ifndef STM32
void initializeTasks() {
    SEGGER_RTT_Init();
    BootCounter::incrementBootCounter();

    uartGatekeeperTask.emplace();
    timeKeepingTask.emplace();
    ambientTemperatureTask.emplace();
    watchdogTask.emplace();
    mcuTemperatureTask.emplace();

    ambientTemperatureTask->createTask();
    mcuTemperatureTask->createTask();
    timeKeepingTask->createTask();
    uartGatekeeperTask->createTask();
    watchdogTask->createTask();
}
#endif