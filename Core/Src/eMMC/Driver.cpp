#include "eMMC/Driver.hpp"

using namespace eMMC;

extern MMC_HandleTypeDef hmmc1;

void eMMC::initializeEMMC(){
    if(HAL_MMC_ConfigWideBusOperation(&hmmc1, SDMMC_BUS_WIDE_8B)!=HAL_OK){
        // Error_Handler();
    }
    if(HAL_MMC_Init(&hmmc1)!=HAL_OK){
        // Error_Handler();
    }
    if(HAL_MMC_InitCard(&hmmc1)!=HAL_OK){
        // Error_Handler();
    }
}

void eMMC::checkEMMC(){
    HAL_MMC_CardInfoTypeDef mmc_info;
    HAL_MMC_GetCardInfo(&hmmc1, &mmc_info);
    // Log Card info
}