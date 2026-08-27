#pragma once
#ifndef ATHENA_DATA
#define ATHENA_DATA

namespace athena::data {

class telemetry_base {
  public:
    /* @brief APID
     * 64 -> 69: image
     * 70: telemetry
     */
    char *APID;
    double ccsds_time;
};

namespace meteor {

/*
 * <!-- Analog telemetry raw bytes, payload bytes 22..37. -->
 */
/*
class analog_telemetry_data : public telemetry_base {
  public:
    // 16
    u8 MSUMR_TLM_Analog_BaseplateTemperature_Raw;
    u8 MSUMR_TLM_Analog_Channel3PhotodetectorTemperature_Raw;
    u8 MSUMR_TLM_Analog_Channel2PhotodetectorTemperature_Raw;
    u8 MSUMR_TLM_Analog_Channel1PhotodetectorTemperature_Raw;
    u8 MSUMR_TLM_Analog_IRLensesTemperature_Raw;
    u8 MSUMR_TLM_Analog_LampCurrentChannel3_Raw;
    u8 MSUMR_TLM_Analog_LampCurrentChannel2_Raw;
    u8 MSUMR_TLM_Analog_LampCurrentChannel1_Raw;
    u8 MSUMR_TLM_Analog_ColdBodyTemperature3_Raw;
    u8 MSUMR_TLM_Analog_ColdBodyTemperature2_Raw;
    u8 MSUMR_TLM_Analog_ColdBodyTemperature1_Raw;
    u8 MSUMR_TLM_Analog_HotBodyTemperature3_Raw;
    u8 MSUMR_TLM_Analog_HotBodyTemperature2_Raw;
    u8 MSUMR_TLM_Analog_HotBodyTemperature1_Raw;
    u8 MSUMR_TLM_Analog_DetectorTemperatureChannel6_Raw;
    u8 MSUMR_TLM_Analog_DetectorTemperatureChannel5_Raw;
};

class digital_telemetry_data : public telemetry_base {
  public:
    // 26
    u8 MSUMR_TLM_Digital_Channel1Mode;
    u8 MSUMR_TLM_Digital_Channel2Mode;
    u8 MSUMR_TLM_Digital_Channel3Mode;
    u8 MSUMR_TLM_Digital_Channel4Mode;
    u8 MSUMR_TLM_Digital_Channel5Mode;
    u8 MSUMR_TLM_Digital_Channel6Mode;
    u8 MSUMR_TLM_Digital_FP1_IC_Photo1;
    u8 MSUMR_TLM_Digital_FP1_IC_Photo2;
    u8 MSUMR_TLM_Digital_FP1_IC_Photo3;
    u8 MSUMR_TLM_Digital_FP1_IC_Photo4;
    u8 MSUMR_TLM_Digital_FP2_IK_Photo1;
    u8 MSUMR_TLM_Digital_FP2_IK_Photo2;
    u8 MSUMR_TLM_Digital_FP2_IK_Photo3;
    u8 MSUMR_TLM_Digital_FP2_IK_Photo4;
    u8 MSUMR_TLM_Digital_BOSOperatingMode;
    u8 MSUMR_TLM_Digital_LevelingChannel123;
    u8 MSUMR_TLM_Digital_PresenterDNSSensor;
    u8 MSUMR_TLM_Digital_Synchronization2;
    u8 MSUMR_TLM_Digital_Synchronization1;
    u8 MSUMR_TLM_Digital_IncludedPURG;
    u8 MSUMR_TLM_Digital_ProtectiveCover2;
    u8 MSUMR_TLM_Digital_ProtectiveCover1;
    u8 MSUMR_TLM_Digital_FP3_IC_Photo1;
    u8 MSUMR_TLM_Digital_FP3_IC_Photo2;
    u8 MSUMR_TLM_Digital_FP3_IC_Photo3;
    u8 MSUMR_TLM_Digital_FP3_IC_Photo4;
};
*/

enum meteor_telemetry_type { NONE = 0, ANALOG = 16, DIGITAL = 26 };

class meteor_telemetry : public telemetry_base {
  public:
    char *msu_mr_id;
    char *msu_mr_set;
    char *type_name;
    meteor_telemetry_type type = NONE;
    char **telemetry[2];
};

} // namespace meteor

} // namespace athena::data
#endif
