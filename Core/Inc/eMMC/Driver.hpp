#pragma once

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_mmc.h"

namespace eMMC{
    void initializeEMMC();

    void checkEMMC();

}