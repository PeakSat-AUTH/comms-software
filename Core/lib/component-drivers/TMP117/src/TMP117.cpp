#include <cstdint>
#include "TMP117.hpp"

namespace TMP117 {

    etl::pair<Error, std::optional<uint16_t>> TMP117::readRegister(RegisterAddress targetRegister) {
        uint8_t target_reg = static_cast<uint8_t>(targetRegister);
        uint8_t *buf;

        if (HAL_I2C_Master_Transmit(&hi2c1, i2cSlaveAddress, &target_reg, 1, MaxTimeoutDelay) != HAL_OK) {
            return etl::make_pair(Error::Timeout, NULL);
        }

        if (HAL_I2C_Master_Receive(&hi2c1, i2cSlaveAddress, buf, 2, MaxTimeoutDelay) != HAL_OK) {
            return etl::make_pair(Error::Timeout, NULL);
        }

        return etl::make_pair(Error::NoErrors, ((static_cast<uint16_t>(buf[0]) << 8) & 0xFF00 | buf[1]));
    }

    Error TMP117::writeRegister(RegisterAddress targetRegister, uint16_t value) {
        uint8_t buf[] = {static_cast<uint8_t>(targetRegister), static_cast<uint8_t>(value & 0xFF),
                         static_cast<uint8_t>((value >> 8) & 0xFF)};

        if (HAL_I2C_Master_Transmit(&hi2c1, i2cSlaveAddress & 0x01, buf, 2, MaxTimeoutDelay) != HAL_OK) {
            return Error::Timeout;
        }
        return Error::NoErrors;
    }

    Error TMP117::writeEEPROM(uint8_t eepromRegister, uint16_t value) {

        if (eepromRegister > 3 || eepromRegister < 1) { return Error::InvalidEEPROM; }
        // Unlock EEPROM
        Error error;
        error = TMP117::writeRegister(RegisterAddress::EEPROMUnlock, 0x4000);
        if (error != Error::NoErrors) { return error; }

        uint16_t timeoutCounter = MaxTimeoutDelay;

        while (timeoutCounter > 0) {
            HAL_Delay(7); // Initial 7 ms wait
            timeoutCounter -= 7; // Rough estimation of elapsed ms
            auto[error, reg] = TMP117::readRegister(RegisterAddress::EEPROMUnlock);
            // Check if EEPROM is still busy
            if (!(reg.value() && 0x8000)) {
                // If it's finished abort and start writing
                break;
            }
            // If it times out, abort operation
            return Error::Timeout;
        }

        if (eepromRegister == 1) {
            error = TMP117::writeRegister(RegisterAddress::EEPROM1, value);
            return error;
        }
        if (eepromRegister == 2) {
            error = TMP117::writeRegister(RegisterAddress::EEPROM2, value);
            return error;
        }
        if (eepromRegister == 3) {
            error = TMP117::writeRegister(RegisterAddress::EEPROM3, value);
            return error;
        }

        return Error::NoErrors;
    }

    etl::pair<Error, std::optional<uint16_t>> TMP117::readEEPROM(uint8_t eepromRegister) {
        if (eepromRegister > 3 || eepromRegister < 1) { return etl::make_pair(Error::InvalidEEPROM, NULL); }

        if (eepromRegister == 1) {
            auto[error, reg] = TMP117::readRegister(RegisterAddress::EEPROM1);
            return etl::make_pair(error, reg.value());
        }
        if (eepromRegister == 2) {
            auto[error, reg] = TMP117::readRegister(RegisterAddress::EEPROM2);
            return etl::make_pair(error, reg.value());
        }
        if (eepromRegister == 3) {
            auto[error, reg] = TMP117::readRegister(RegisterAddress::EEPROM3);
            return etl::make_pair(error, reg.value());
        }
    }


    float TMP117::convertTemperature(uint16_t temp) {
        return static_cast<int16_t>(temp) * temperaturePrecision;
    }

    etl::pair<Error, uint16_t> TMP117::getRevNumber() {
        auto[error, reg] = readRegister(RegisterAddress::IDRegister);

        if (error != NoErrors) {
            return etl::make_pair(error, NULL);
        }

        return etl::make_pair(Error::NoErrors, reg.value() & 0xF >> 12);
    }

    etl::pair<Error, std::optional<float>> TMP117::setCalibrationOffset(float calibration) {
        if ((calibration > MaxAbsoluteCalibrationOffset) || (calibration < -MaxAbsoluteCalibrationOffset)) {
            return etl::make_pair(Error::InvalidCalibrationOffset, NULL);
        }

        Error error;

        if (calibration >= 0) {
            error = TMP117::writeRegister(RegisterAddress::TemperatureOffset,
                                        static_cast<uint16_t>(calibration / temperaturePrecision));
            return etl::make_pair(error, NULL);
        } else {
            error = TMP117::writeRegister(RegisterAddress::TemperatureOffset,
                                        ~(static_cast<uint8_t>(calibration / temperaturePrecision)) + 1);
            return etl::make_pair(error, NULL);
        }
    }

    etl::pair<Error, float> TMP117::getCalibrationOffset() {
        auto[error, reg] = readRegister(RegisterAddress::TemperatureOffset);

        if (error != NoErrors) {
            return etl::make_pair(error, NULL);
        }

        if (reg.value() & 0x8000) {
            return etl::make_pair(NoErrors, (-(~reg.value() + 1)) * temperaturePrecision);
        } else {
            return etl::make_pair(NoErrors, reg.value());
        }
    }


    etl::pair<Error, float> TMP117::getTemperature(bool ignoreAlert = false) {

        auto offset = getCalibrationOffset();

        if (offset.first != NoErrors) {
            return etl::make_pair(offset.first, NULL);
        }

        float temperatureOffset = offset.second;

        auto[error, reg] = readRegister(RegisterAddress::ConfigurationRegister);

        if (error != NoErrors) {
            return etl::make_pair(error, NULL);
        }

        if (!ignoreAlert) {
            if (reg.value() && 0x8000) {
                return etl::make_pair(Error::TemperatureHigh, NULL);
            }

            if (reg.value() && 0x4000) {
                return etl::make_pair(Error::TemperatureLow, NULL);
            }
        }

        // Continuous mode
        if (!(reg.value() && 0xC00)) {
            auto[error, reg] = readRegister(RegisterAddress::TemperatureRegister);
            if (error != NoErrors) {
                return etl::make_pair(error, NULL);
            }

            return etl::make_pair(
                    NoErrors,
                    convertTemperature(reg.value()) + temperatureOffset
            );
        }

        // One-shot mode
        if ((reg.value() >> 10) & 0x3 == 0x2) {
            error = TMP117::writeRegister(RegisterAddress::EEPROM1, reg.value() || 0xC00);
        } // One-shot ongoing but data not ready yet

        uint16_t timeout = MaxTimeoutDelay;

        while (timeout > 0) {
            HAL_Delay(TimeoutWait);
            timeout -= TimeoutWait;
            auto[error, reg] = readRegister(RegisterAddress::ConfigurationRegister);
            if (error != NoErrors) {
                return etl::make_pair(error, NULL);
            }

            if (reg.value() && 0x4) {
                auto[error, reg] = readRegister(RegisterAddress::TemperatureRegister);
                if (error != NoErrors) {
                    return etl::make_pair(error, NULL);
                }

                return etl::make_pair(
                        NoErrors,
                        convertTemperature(reg.value()) + temperatureOffset
                );
            }
        }
        return etl::make_pair(
                Timeout,
                NULL
        );
    }

    etl::pair<Error, uint16_t> TMP117::getDeviceID() {
        auto[error, reg] = readRegister(RegisterAddress::IDRegister);

        if (error != NoErrors) {
            return etl::make_pair(error, NULL);
        }

        return etl::make_pair(Error::NoErrors, reg.value() & 0xFFF);
    }


    void TMP117::handleIRQ(void) {
        /// The ALERT functionality is not going to be implemented for this version of the sensor since we simply need
        /// to poll the driver. All the alerts are handled there
    }

    Error TMP117::configure() {
        uint16_t config =
                (static_cast<uint16_t>(configuration.conversionMode) << 10) |
                ((configuration.cycleTime & 0x7) << 7) |
                (static_cast<uint16_t>(configuration.averaging) << 5) |
                (configuration.thermalAlert << 4) |
                (configuration.polarityAlert << 3) |
                (configuration.drAlert << 2);
        return writeRegister(RegisterAddress::ConfigurationRegister, config);
    }
}
