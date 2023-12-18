#ifndef ECSS_SERVICES_PLATFORMPARAMETERS_HPP
#define ECSS_SERVICES_PLATFORMPARAMETERS_HPP

#include "Helpers/Parameter.hpp"

namespace PlatformParameters {
    /**
     * Definition of enumeration class that will be used to describe the status of the Antenna Deployment
     */
    enum class ADMStatus : uint16_t {
        NotDeployed = 0b000,
        Deployed = 0b1111,
        Element1NotDeployed = 0b0001,
        Elements12NotDeployed = 0b0011,
        Elements13NotDeployed = 0b0101,
        Elements14NotDeployed = 0b1001,
        Elements123NotDeployed = 0b0111,
        Elements124NotDeployed = 0b1011,
        Elements134NotDeployed = 0b1101,
        Element2NotDeployed = 0b0010,
        Elements23NotDeployed = 0b0110,
        Elements24NotDeployed = 0b1010,
        Elements234NotDeployed = 0b1110,
        Element3NotDeployed = 0b0100,
        Elements34NotDeployed = 0b1100,
        Element4NotDeployed = 0b1000
    };

    /**
     * Power Amplifier modes by Transceiver in dB
     */
    enum class PAGain : uint8_t {
        NoReduction = 0,
        Reduction1dB = 1,
        Reduction2dB = 2,
        Reduction3dB = 3,
    };

    /**
     * Sample Rate of the sub-register in TX
     */
    enum class TXSampleRate : uint8_t { // KHz
        Case4000KHz = 0x1,
        Case2000KHz = 0x2,
        Case1333KHz = 0x3,
        Case1000KHz = 0x4,
        Case800KHz = 0x5,
        Case666KHz = 0x6,
        Case500KHz = 0x8,
        Case400KHz = 0xA,
    };

    enum class TXSymbolRateUHF : uint8_t { // KHz
        Case5KHz = 1,
        Case10KHz = 2,
        Case20KHz = 3,
    };

    enum class TXSymbolRateSBand : uint8_t { // KHz
        Case50KHz = 1,
        Case100KHz = 2,
    };

    /**
     * Memory Partition, as defined in DDJF_OBSW
     */
    enum class memoryPartition : uint8_t {
        FirstPartition = 0,
        SecondPartition = 1,
    };
    /**
     * ID enumeration of COMMS subsystem's specific parameters.
     */
    enum ParameterID : uint16_t {
        ReportParametersUnusedStack = 6,
        AvailableHeap = 7,

        AntennaDeploymentStatus = 2003,
        SampleRateUHFTX = 2004,
        SampleRateSBandTX = 2005,
        SymbolRateSBandTX = 2006,
        CWInterval = 2007,
        GMSKBeaconInterval = 2008,
        ChannelNumberUHF = 2011,
        ChannelNumberSBand = 2012,
        PowerAmplifierUHF = 2014,
        PowerAmplifierS = 2015,
        VariableGainAmplifier = 2016,
        ReceivedSignalStrengthIndicator = 2017,
        UHFBandTX = 2018,
        SBandTX = 2020,
        NumberOfPackagesRejected = 2021,
        InvalidHMAC = 2022,
        InvalidPacketStructure = 2023,
        InvalidSpacecraftID = 2024,
        TCFrameSequenceCounter = 2025,
        COMMSPCBTemperature1 = 2026,
        COMMSPCBTemperature2 = 2027,
        COMMSMCUTemperature = 2028,
        COMMSMCUInputVoltage = 2029,
        COMMSMCUBootCounter = 2030,
        OnBoardTime = 2031,
        NANDUsedMemoryPartition = 2032,
        LastFailedEvent = 2033,
        COMMSMCUSystick = 2034,
        COMMSFLASHInt = 2035,
        COMMSSRAMInt = 2036,
        SymbolRateUHFTX = 2037,
    };
    inline Parameter<Time::DefaultCUC> commsMCUTime(Time::DefaultCUC(0));
    inline Parameter<uint16_t> reportParametersUnusedStack(0);
    inline Parameter<uint16_t> availableHeap(0);

    // COMMS parameters
    inline Parameter<ADMStatus> antennaDeploymentStatus(ADMStatus::NotDeployed);
    inline Parameter<TXSampleRate> sampleRateUHFTX(TXSampleRate::Case4000KHz);  //KHz
    inline Parameter<TXSampleRate> sampleRateSBandTX(TXSampleRate::Case4000KHz);  //KHz
    inline Parameter<TXSymbolRateSBand> symbolRateSBandTX(TXSymbolRateSBand::Case100KHz);  //KHz
    inline Parameter<TXSymbolRateUHF> symbolRateUHFBandTX(TXSymbolRateUHF::Case10KHz);  //KHz
    inline Parameter<uint16_t> cwInterval(300);  //seconds
    inline Parameter<uint16_t> gmskBeaconInterval(0);  //seconds
    inline Parameter<uint32_t> channelNumberUHF(0);
    inline Parameter<uint32_t> channelNumberSBand(0);
    inline Parameter<PAGain> powerAmplifierUHF(PAGain::NoReduction);  //dB
    inline Parameter<PAGain> powerAmplifierS(PAGain::NoReduction);   //dB
    inline Parameter<uint8_t> variableGainAmplifier(0);
    inline Parameter<float> receivedSignalStrengthIndicator(0);
    inline Parameter<bool> uhfBandTX(false);
    inline Parameter<bool> sBandTX(false);
    inline Parameter<uint16_t> numberOfPackagesRejected(0);
    inline Parameter<uint16_t> invalidHMAC(0);
    inline Parameter<uint16_t> invalidPacketStructure(0);
    inline Parameter<uint16_t> invalidSpacecraftID(0);
    inline Parameter<uint16_t> tcFrameSequenceCounter(0);

    /**
     * The measurements of the Temperature and the Input Voltage from the sensors are floats. However, the sensors
     * measure a specific range. Hence, to cut 2 bytes, the parameter variables are now uint16_t. The max value of the
     * variable (2^16) now represents the upper value of the measurement range, and 0 the lower value of the range.
     */
    inline Parameter<uint16_t> commsPCBTemperature1(0);
    inline Parameter<uint16_t> commsPCBTemperature2(0);
    inline Parameter<uint16_t> commsMCUTemperature(0);
    inline Parameter<uint16_t> commsMCUInputVoltage(0);

    inline Parameter<uint32_t> commsMCUBootCounter(0);
    inline Parameter<uint32_t> onBoardTime(0);
    inline Parameter<memoryPartition> nandUsedMemoryPartition(memoryPartition::FirstPartition);
    inline Parameter<uint16_t> lastFailedEvent(0);
    inline Parameter<uint32_t> commsMCUSystick(0);
    inline Parameter<uint32_t> commsFlashInt(0);
    inline Parameter<uint32_t> commsSRAMInt(0);
    inline Parameter<bool> commsUseUART(true);


}

#endif