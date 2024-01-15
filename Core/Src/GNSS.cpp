#include "GNSS.hpp"
#include "etl/vector.h"

GNSSMessage GNSSReceiver::configureSerialPort(uint8_t COMPort, GNSSReceiver::BaudRate baudRate,
                                              GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::configureMessageType(GNSSReceiver::ConfigurationType type, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureSystemPowerMode(GNSSReceiver::PowerMode mode, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureSystemPositionRate(uint8_t rate, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureDOPMask(GNSSReceiver::DOPModeSelect mode, uint16_t PDOPvalue, uint16_t HDOPvalue,
                                           uint16_t GDOPvalue, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::configureElevationAndCNRMask(GNSSReceiver::ElevationAndCNRModeSelect mode, uint8_t elevationMask,
                                           uint8_t CNRMask, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configurePositionPinning(GNSSReceiver::PositionPinning positionPinning,
                                                   GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::configurePositionPinningParameters(uint16_t pinningSpeed, uint16_t pinningCnt, uint16_t unpiningSpeed,
                                                 uint16_t unpiningCnt, uint16_t unpinningDistance,
                                                 GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configure1PPSCableDelay(uint32_t cableDelay, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureNMEATalkerID(GNSSReceiver::TalkerIDType type, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::configure1PPSTiming(GNSSReceiver::TimingMode mode, uint16_t surveyLength, uint16_t standardDeviation,
                                  uint16_t latitude, uint16_t longtitude, uint16_t altitude,
                                  GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configure1PPSOutputMode(GNSSReceiver::OutputMode mode, GNSSReceiver::AlignSource source,
                                                  GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::configureSBAS(GNSSReceiver::EnableSBAS enable, GNSSReceiver::RangingSBAS ranging, uint8_t URAMask,
                            GNSSReceiver::CorrectionSBAS correction, uint8_t numberOfTrackingChannels,
                            uint8_t subsystemMask, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureQZSS(GNSSReceiver::EnableQZSS enable, uint8_t noOfTrackingChannels,
                                        GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureSBASAdvanced(GNSSReceiver::EnableSBAS enable, GNSSReceiver::RangingSBAS ranging,
                                                uint8_t rangingURAMask, GNSSReceiver::CorrectionSBAS correction,
                                                uint8_t numTrackingChannels, uint8_t subsystemMask, uint8_t waasPRN,
                                                uint8_t egnosPRN, uint8_t msasPRN, uint8_t gaganPRN, uint8_t sdcmPRN,
                                                uint8_t bdsbasPRN, uint8_t southpanPRN, uint8_t attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureSAEE(GNSSReceiver::EnableSAEE enable, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureExtendedNMEAMesaageInterval(etl::vector<uint8_t, 12> intervals,
                                                               GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureInterferenceDetection(GNSSReceiver::InterferenceDetectControl control,
                                                         GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configurePositionFixNavigationMap(GNSSReceiver::FirstFixNavigationMask firstFix,
                                                            GNSSReceiver::SubsequentFixNavigationMask subsequentFix,
                                                            GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::configureUTCReferenceTimeSyncToGPSTime(GNSSReceiver::EnableSyncToGPSTime enable, uint16_t utcYear,
                                                     uint8_t utcMonth, uint8_t utcDay,
                                                     GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::configureGNSSNavigationMode(GNSSReceiver::NavigationMode mode, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureGNSSConstellationTypeForNavigationSolution(uint8_t constellationType,
                                                                              GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::SoftwareImageDownloadUsingROMExternalLoader(GNSSReceiver::BaudRate baud,
                                                                      GNSSReceiver::FlashType flashType,
                                                                      uint16_t flashID,
                                                                      GNSSReceiver::BufferUsedIndex bufferUsedIndex,
                                                                      GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureGNSSDozeMode() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::configurePSTIMessageInterval(uint8_t PSTI_ID, uint8_t interval, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureGNSSDatumIndex(uint16_t datumIndex, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureGPSUTCLeapSecondsInUTC(uint16_t utcYear, uint8_t utcMonth, uint8_t leapSeconds,
                                                          uint8_t insertSeconds, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureNavigationDataMessageInterval(uint8_t navigationDataMessageInterval,
                                                                 GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::configureGNSSGEOFencingDatabyPolygon() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::configureNMEAStringInterval(uint16_t nmeaString, uint8_t interval, GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::SoftwareImageDownloadUsingInternalLoader(GNSSReceiver::BaudRate baud, GNSSReceiver::FlashType flashType,
                                                       uint16_t flashID, GNSSReceiver::BufferUsedIndex bufferUsedIndex,
                                                       GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage
GNSSReceiver::SoftwareImageDownloadUsingExternalLoader(GNSSReceiver::BaudRate baud, GNSSReceiver::FlashType flashType,
                                                       uint16_t flashID, GNSSReceiver::BufferUsedIndex bufferUsedIndex,
                                                       GNSSReceiver::Attributes attributes) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::querySoftwareVersion(GNSSReceiver::SoftwareType softwareType) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::querySoftwareCRC(GNSSReceiver::SoftwareType softwareType) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryPositionUpdateRate() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryPowerMode() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::QueryDOPMask() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::QueryELevationandCNRMask() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryPositionPinning() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::query1PPSTiming() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::query1PPSCableDelay() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryNMEATalkerID() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::querySBASStatus() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryQZSSStatus() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::querySBASAdvanced() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::querySAEEStatus() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryGNSSBootStatus() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryExtendedNMEAMesaageInterval() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryInterferenceDetectionStatus() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryGNSSParameterSearchEngineNumber() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryPositionFixNavigationMap() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::QueryUTCReferenceTimeSyncToGPSTime() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryGNSSNavigationMode() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryGNSSConstellationTypeForNavigationSolution() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryGPSTime() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryPSTIMessageInterval() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryRequestedPSTIMessageInterval() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryNavigationDataMessageInterval() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryVersionExtentionString() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryGNSSGEOFencingDatabyPolygon() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryGNSSMultiPolygonGEOFencingResult() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryNMEAStringInterval() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::queryRequestedNMEAStringInterval() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::getGPSEphemeris(uint8_t SV) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::getGLONASSEphemeris(uint8_t SV) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::setGLONASSEphemeris(uint8_t slotNumber, uint8_t kNumber, std::vector<uint8_t> ephemerisData0,
                                              std::vector<uint8_t> ephemerisData1, std::vector<uint8_t> ephemerisData2,
                                              std::vector<uint8_t> ephemerisData3) {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}

GNSSMessage GNSSReceiver::getGLONASSTimeCorrectionParameters() {
    return GNSSMessage{0, 0, etl::vector<uint8_t, 256>()};
}
