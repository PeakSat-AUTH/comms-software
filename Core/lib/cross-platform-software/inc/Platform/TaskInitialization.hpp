#pragma once

#include "FreeRTOS.h"
#ifndef STM32
#include "SEGGER_RTT.h"
#endif
#include "TimeKeepingTask.hpp"
#include "MCUTemperatureTask.hpp"
#include "AmbientTemperatureTask.hpp"
#include "UARTGatekeeperTask.hpp"
#include "WatchdogTask.hpp"

void initializeTasks();
