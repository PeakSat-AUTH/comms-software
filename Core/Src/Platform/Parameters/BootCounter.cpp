#include "BootCounter.hpp"
#ifndef STM32
namespace BootCounter {
    void clearRegisters() {
        GPBRWrite(UnexpectedResetRegister, ClearRegisterValue);
        GPBRWrite(BootCounterRegister, ClearRegisterValue);
    }

    void setRegisters() {
        if (GPBRRead(UnexpectedResetRegister) == SoftwareResetValue) {
            return;
        }

        GPBRWrite(UnexpectedResetRegister, SoftwareResetValue);
        GPBRWrite(BootCounterRegister, ClearRegisterValue);
    }

    void incrementBootCounter() {
        if (GPBRRead(BootCounterRegister) > BootCounterLimit) {
            clearRegisters();
        }
        setRegisters();
        GPBRWrite(BootCounterRegister, GPBRRead(BootCounterRegister) + 1);
    }
}
#endif