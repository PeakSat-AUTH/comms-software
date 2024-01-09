#pragma once

#include "etl/vector.h"

class GNSSReceiver {
public:
    GNSSReceiver();

private:
    typedef etl::vector<uint8_t, 256> GNSSMessage;

    GNSSMessage message;

    enum class GNSSMessages : uint8_t {
        SystemRestart = 0x1,
        QuerySoftwareVersion = 0x2,
        QuerySoftwareCRC = 0x3,
        SetFactoryDefaults = 0x4,
        ConfigureSerialPort = 0x5,
        ConfigureMessageType = 0x9,
        ConfigurePowerMode = 0xC,
        ConfigurePositionUpdateRate = 0xE,
        QueryPositionUpdateRate = 0x10,
        QueryPowerMode = 0x15,
        ConfigureDOPMask = 0x2A,
        ConfigureElevationAndCNRMask = 0x2B,
        QueryDOPMask = 0x2E,
        QueryElevationAndCNRMask = 0x2F,
        GetGPSEphemeris = 0x30,
        ConfigurePositionPinning = 0x39,
        QueryPositionPinning = 0x3A,
        ConfigurePositionPinningParameters = 0x3B,
        SetGPSEphemeris = 0x41,
        Query1PPSTiming = 0x44,
        Configure1PPSCableDelay = 0x45,
        Query1PPSCableDelay = 0x46,
        ConfigureNMEATalkerID = 0x4B,
        QueryNMEATalkID = 0x4F,
        Configure1PPSTiming = 0x54,
        Configure1PPSOutputMode = 0x55,
        Query1PPSOutputMode = 0x56,
        GetGLONASSEphemeris = 0x5B,
        SetGLONASSEphemeris = 0x5C,
        GetGLONASSTimeCorrectionParameters = 0x5F,
        SetGLONASSTimeCorrectionParameters = 0x60
    };

    enum class GNSSMessagesSubID : uint16_t {
        ConfigureSBAS = (0x62 << 8) | 0x1,
        QuerySBASStatus = (0x62 << 8) | 0x2,
        ConfigureQZSS = (0x62 << 8) | 0x3,
        QueryQZSSStatus = (0x62 << 8) | 0x4,
        ConfigureSBASAdvanced = (0x62 << 8) | 0x5,
        QuerySBASAdvanced = (0x62 << 8) | 0x6,
        SBASStatus = (0x62 << 8) | 0x80,
        QZSSStatus = (0x62 << 8) | 0x81,
        SBASAdvanced = (0x62 << 8) | 0x82,
        ConfigureSAEE = (0x63 << 8) | 0x1,
        QuerySAEE = (0x63 << 8) | 0x2,
        SAEEStatus = (0x63 << 8) | 0x80,
        QueryBootStatus = (0x64 << 8) | 0x1,
        ConfigureExtendedNMEAMessageInterval = (0x64 << 8) | 0x2,
        QueryExtendedNMEAMessageInterval = (0x64 << 8) | 0x3,
        ConfigureInterferenceDetection = (0x64 << 8) | 0x6,
        QueryInterferenceDetectionStatus = (0x64 << 8) | 0x7,
        QueryGNSSParameterSearchEngineNumber = (0x64 << 8) | 0xB,
        ConfigurePositionFixNavigationMask = (0x64 << 8) | 0x11,
        QueryPositionFixNavigationMask = (0x64 << 8) | 0x12,
        ConfigureUTCReferenceTimeSyncToGPSTime = (0x64 << 8) | 0x15,
        QueryUTCReferenceTimeSyncToGPSTime = (0x64 << 8) | 0x16,
        ConfigureGNSSNavigationMode = (0x64 << 8) | 0x17,
        QueryGNSSNavigationMode = (0x64 << 8) | 0x18,
        ConfigureGNSSConstellationTypeForNavigationSolution = (0x64 << 8) | 0x19,
        QueryGNSSConstellationTypeForNavigationSolution = (0x64 << 8) | 0x1A,
        SoftwareImageDownloadUsingROMExternalLoader = (0x64 << 8) | 0x1B,
        ConfigureGNSSDozeMode = (0x64 << 8) | 0x1C,
        QueryGPSTime = (0x64 << 8) | 0x20,
        ConfigurePSTIMessageInterval = (0x64 << 8) | 0x21,
        QueryPSTIMessageInterval = (0x64 << 8) | 0x22,
        QueryRequestedPSTIMessageInterval = (0x64 << 8) | 0x23,
        ConfigureGNSSDatumIndex = (0x64 << 8) | 0x27,
        QueryGNSSDatumIndex = (0x64 << 8) | 0x28,
        ConfigureGPSUTCLeapSecondsInUTC = (0x64 << 8) | 0x2D,
        ConfigureNavigationDataMessageInterval = (0x64 << 8) | 0x2F,
        QueryNavigationDataMessageInterval = (0x64 << 8) | 0x30,
        ConfigureGNSSGeoFencingDataByPolygon = (0x64 << 8) | 0x34,
        QueryGNSSGeoFencingDataByPolygon = (0x64 << 8) | 0x35,
        QueryGNSSMultiPolygonGeoFencingResult = (0x64 << 8) | 0x36,
        ConfigureNMEAStringInterval = (0x64 << 8) | 0x3B,
        QueryNMEAStringInterval = (0x64 << 8) | 0x3C,
        QueryRequestedNMEAStringInterval = (0x64 << 8) | 0x40,
        SoftwareImageDownloadUsingInternalLoader = (0x64 << 8) | 0x4E,
        SoftwareImageDownloadUsingExternalLoader = (0x64 << 8) | 0x4F,
        QueryVersionExtensionString = (0x64 << 8) | 0x7D,
        GNSSBootStatus = (0x64 << 8) | 0x80,
        ExtendedNMEAMessageInterval = (0x64 << 8) | 0x81,
        InterferenceDetectionStatus = (0x64 << 8) | 0x83,
        GNSSParameterSearchEngineNumber = (0x64 << 8) | 0x85,
        PositionFixNavigationMask = (0x64 << 8) | 0x88,
        GPSUTCReferenceTime = (0x64 << 8) | 0x8A,
        GNSSNavigationMode = (0x64 << 8) | 0x8B,
        GNSSConstellationTypeForNavigationSolution = (0x64 << 8) | 0x8C,
        GPSTime = (0x64 << 8) | 0x8E,
        PSTIMessageInterval = (0x64 << 8) | 0x8F,
        RequestedPSTIMessageInterval = (0x64 << 8) | 0x90,
        GNSSDatumIndex = (0x64 << 8) | 0x92,
        NavigationDataMessageInterval = (0x64 << 8) | 0x98,
        GNSSGeoFencingDataByPolygon = (0x64 << 8) | 0x99,
        GNSSMultiPolygonGeoFencingResult = (0x64 << 8) | 0x9A,
        NMEAStringInterval = (0x64 << 8) | 0x9D,
        RequestedNMEAStringInterval = (0x64 << 8) | 0x9F,
        VersionExtensionString = (0x64 << 8) | 0xFE,
        Configure1PPSPulseWidth = (0x65 << 8) | 0x1,
        Query1PPSPulseWidth = (0x65 << 8) | 0x2,
        ConfigurePPS2FrequencyOutput = (0x65 << 8) | 0x3,
        QueryPPS2FrequencyOutput = (0x65 << 8) | 0x4,
        OnePPSPulseWidth = (0x65 << 8) | 0x80,
        GNSSPPS2FrequencyOutput = (0x65 << 8) | 0x81,
        SetBeidouEphemerisData = (0x67 << 8) | 0x1,
        GetBeidouEphemerisData = (0x67 << 8) | 0x2,
        BeidouEphemerisData = (0x67 << 8) | 0x80,
        ConfigureRTKModeAndOperationalFunction = (0x6A << 8) | 0x6,
        QueryRTKModeAndOperationalFunction = (0x6A << 8) | 0x7,
        ConfigureRTKSlaveBaseSerialPortBaudRate = (0x6A << 8) | 0xC,
        QueryRTKSlaveBaseSerialPortBaudRate = (0x6A << 8) | 0xD,
        ConfigureRTKPreciselyKinematicBaseSerialPortBaudRate = (0x6A << 8) | 0x13,
        QueryRTKPreciselyKinematicBaseSerialPortBaudRate = (0x6A << 8) | 0x14,
        ConfigureRTKRoverMovingBaseHeadingAndPitchOffsets = (0x6A << 8) | 0x15,
        QueryRTKRoverMovingBaseHeading = (0x6A << 8) | 0x16,
        RTKModeAndOperationalFunction = (0x6A << 8) | 0x83,
        RTKSlaveBaseSerialPortBaudRate = (0x6A << 8) | 0x85,
        RTKPreciselyKinematicBaseSerialPortBaudRate = (0x6A << 8) | 0x88,
        HeadingAndPitchOffsetsOfRTKRoverMovingBase = (0x6A << 8) | 0x89,
        SetGALILEOEphemeris = (0x6E << 8) | 0x1,
        GetGALILEOEphemeris = (0x6E << 8) | 0x2,
        GALILEOEphemerisData = (0x6E << 8) | 0x80,
        SetIRNSSEphemeris = (0x6F << 8) | 0x3,
        GetIRNSSEphemeris = (0x6F << 8) | 0x4,
        IRNSSEphemerisData = (0x6F << 8) | 0x81
    };

    //Messages prime ID
    void systemRestart();

    void querySoftwareVersion();

    void querySoftwareCRC();

    void setFactoryDefaults();

    void configureSerialPort();

    void configureMessageType();

    void configureSystemPowerMode();

    void configureSystemPositionRate();

    void quertPositionUpdateRate();

    void queryPowerMode();

    void configureDOPMask();

    void configureElevationAndCNRMask();

    void QueryDOPMask();

    void QueryELevationandCNRMask();

    void getGPSEphemeris();

    void configurePositionPinning();

    void queryPositionPinning();

    void configurePositionPinningParameters();

    void setGPSEphemeris();

    void query1PPSTiming();

    void configure1PPSCableDelay();

    void query1PPSCableDelay();

    void configureNMEATalkerID();

    void queryNMEATalkerID();

    void configure1PPSTiming();

    void configure1PPSOutputMode();

    void query1PPSOutputMode();

    void getGLONASSEphemeris();

    void setGLONASSEphemeris();

    void getGLONASSTimeCorrectionParameters();

    void setGLONASSTimeCorrectionParameters();

    //Messages sub ID
    void configureSBAS();

    void querySBASStatus(); //ANSWER MESSAGES

    void configureQZSS();

    void queryQZSSStatus();

    void configureSBASAdvanced();

    void querySBASAdvanced();

    void configureSAEE();

    void querySAEEStatus(); //ANSWER MESSAGES

    void queryGNSSBootStatus();

    void configureExtendedNMEAMesaageInterval();

    void queryExtendedNMEAMesaageInterval();

    void configureInterferenceDetection();

    void queryInterferenceDetectionStatus();

    void queryGNSSParameterSearchEngineNumber();

    void ConfigurePositionFixNavigationMask();

    void queryPositionFixNavigationMap();

    void configureUTCReferenceTimeSyncToGPSTime();

    void QueryUTCReferenceTimeSyncToGPSTime();

    void configureGNSSNavigationMode();

    void queryGNSSNavigationMode();

    void configureGNSSConstellationTypeForNavigationSolution();

    void queryGNSSConstellationTypeForNavigationSolution();

    void SoftwareImageDOwnloadUsingROMExternalLoader();

    void configureGNSSDozeMode();

    void queryGPSTime();

    void configurePSTIMessageInterval();

    void queryPSTIMessageInterval();

    void queryRequestedPSTIMessageInterval();

    void configureGNSSDatumIndex();

    void configureGPSUTCLeapSecondsInUTC();

    void configureNavigationDataMessageInterval();

    void queryNavigationDataMessageInterval();

    void queryVersionExtentionString();

    void configureGNSSGEOFencingDatabyPolygon();

    void queryGNSSGEOFencingDatabyPolygon();

    void queryGNSSMultiPolygonGEOFencingResult();

    void configureNMEAStringInterval();

    void queryNMEAStringInterval();

    void queryRequestedNMEAStringInterval();

    void SoftwareImageDownloadUsingInternalLoader();

    void SoftwareImageDownloadUsingExternalLoader();


};