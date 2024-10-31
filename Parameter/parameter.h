/**
 * @file paramter.h
 * @author Sinyeop Go (sygo@higenrnm.com)
 * @brief
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef PARAMETER_H
#define PARAMETER_H

/*-----------------------------------------------------------------------------
------
------    Includes
------
------------------------------------------------------------------------------*/
#include <stdint.h>
/*------------------------------------------------------------------------------
------
------    Defines and Types
------
------------------------------------------------------------------------------*/
#define PARAMETER_MAX_NUMBER (115)
#define PARAMETER_IDX_NUMBER (PARAMETER_MAX_NUMBER + 1)

#define PARAM_NULL (void *)(0)
#define PARAM_SUCCESS   0
#define PARAM_FAILURE   1

#define P_TYPE_NULL     0x0000
#define P_TYPE_INT32_T  0x0404
#define P_TYPE_UINT32_T 0x0407
#define P_TYPE_INT16_T  0x0203
#define P_TYPE_UINT16_T 0x0206
#define P_TYPE_INT8_T   0x0102
#define P_TYPE_UINT8_T  0x0105
#define P_TYPE_FLOAT_T  0x0408
#define P_TYPE_STRING   0x0409

#define TYPE_LENGTH_1BYTPE_MASK 0x0100
#define TYPE_LENGTH_2BYTPE_MASK 0x0200
#define TYPE_LENGTH_4BYTPE_MASK 0x0400

#define PPM_ELE_ATTR_FUNC                   0x0200
#define PPM_ELE_ATTR_FUNC_MASK              0x0200
#define PPM_ELE_ATTR_RETAIN                 0x0010
#define PPM_ELE_ATTR_REATIN_MASK            0x0010
#define PPM_ELE_ATTR_WRITE                  0x0002
#define PPM_ELE_ATTR_WRITE_MASK             0x0002
#define PPM_ELE_ATTR_READ                   0x0001
#define PPM_ELE_ATTR_READ_MAKS              0x0001
#define PPM_ELE_ATTR_CANT_ACCESS_SVON       0x0004
#define PPM_ELE_ATTR_CANT_ACCESS_SVON_MASK  0x0004

/**
 * @brief parameter definition
 * Parameter will be loaded from flash
 */
typedef struct {
    uint16_t hw_id;                 /**< hardware id, motor drive id */
    uint16_t hw_ver;                /**< hardware version */
    uint16_t hw_drv_continuous;      /**< hardware drive continuous current value [0.1A] */
    uint16_t hw_drv_peak;            /**< hardware drive peak current value [0.1A] */
    uint16_t hw_inv_max;            /**< hardware inverter current max, [0.1A] */
//  uint16_t hw_gate;               /**< kind of Gate Drivers */
//  uint16_t hw_curr_sensor_kind;   /**< kind of current sensor */
} drv_hw_info;

typedef struct {
    uint16_t hw_curr_sensor_ph;     /**< hardware current sensor phase */
    uint16_t hw_curr_sensor_max;    /**< hardware phase current sensor max, [0.1A] */
    uint32_t curr_sen_scale_u;      /**< current sensor U phase consersion scale, [x10e-6] */
    uint32_t curr_sen_scale_v;      /**< current sensor V phase consersion scale, [x10e-6] */
    uint32_t curr_sen_scale_w;      /**< current sensor W phase consersion scale, [x10e-6] */
    int16_t curr_sen_offset_u;      /**< current sensor U phase offset, [mA] */
    int16_t curr_sen_offset_v;      /**< current sensor V phase offset, [mA] */
    int16_t curr_sen_offset_w;      /**< current sensor W phase offset, [mA] */
    int16_t vdc_sen_offset;         /**< vdc sensor offset, [mV] */
    uint32_t vdc_sen_scale;         /**< vdc sensor conversion scale, [x10e-6] */
} hw_sensor;

typedef struct {
    uint16_t mtr_id;                /**< motor ID or name or part number */
    uint16_t mtr_pole;              /**< number of motor pole, [number, N] */
    uint32_t mtr_rated_trq;         /**< motor rated torque, [Nm x10e-6] */
    uint32_t mtr_max_trq;           /**< motor max torque, [Nm x10e-6] */
    uint32_t mtr_rated_curr;        /**< motor rated current, [mArms] */
    uint32_t mtr_resistance;        /**< motor resistance, [uOhm] */
    uint32_t mtr_inductance;        /**< motor inductance, [uH] */
    uint32_t mtr_trq_constant;      /**< motor torque constant, [Nm/A x10e-6] */
    uint32_t mtr_inertia;           /**< motor rotor inertia, [gf-cm-sec^2 x10e-6] */
    uint16_t mtr_rated_spd;         /**< motor rated speed, [rpm] */
    uint16_t mtr_max_spd;           /**< motor max speed, [rpm] */
} motor;

typedef struct {
    uint32_t enc_elec_offset;       /**< encoder electrical offset */
    uint16_t enc_type;              /**< ecoder type */
    uint32_t enc_mtr_single_res;    /**< encoder motor side single turn bit or ppr */
    uint32_t enc_mtr_multi_res;     /**< encoder motor side multi turn bit or ppr */
    uint32_t enc_out_single_res;    /**< encoder output side single turn bit or ppr */
    uint32_t enc_out_multi_res;     /**< encoder output side multi turn bit or ppr */
} encoder;

/**
* \brief Speed feedback parameter
*/
typedef struct {
    uint16_t spd_fb_obv_pole;       /**< speed feedback observer pole, [Hz] */
    uint16_t spd_fb_state_band;     /**< speed feedback state filter bandwidth, [Hz] */
    uint16_t spd_fb_state_lpf;      /**< speed feedback state filter low pass filter cutoff frequency, [Hz] */
} spd_fb;

typedef struct {
    uint16_t trq_ctrl_frq;          /**< torque(current) controller band width, [Hz] */
    uint8_t trq_ctrl_anti_ratio;    /**< torque(current) controller anti-windup ratio, [x0.1] */
} trq_ctrl;

typedef struct {
    uint16_t spd_ctrl_frq;          /**< speed controller band width, [Hz] */
    uint8_t spd_ctrl_i_ratio;       /**< speed controller I gain ratio, [x0.1] */
    uint8_t spd_ctrl_anti_ratio;    /**< speed controller anti-windup ratio, [x0.1] */
    uint16_t spd_ctrl_j_ratio;      /**< speed controller inertia ratio (rotor:load ratio), [x0.1] */
    uint16_t spd_ctrl_pi_ip_ratio;  /**< speed controller PI-IP ratio, [x0.001] */
} spd_ctrl;

typedef struct factor_param {
    uint32_t gear_mtr_revol; /**< gear ratio motor shaft revolution */
    uint32_t gear_drv_revol; /**< gear ratio drive shaft revolution */
    uint32_t feed_feed; /**< feed constant = feed / drive shaft revolution */
    uint32_t feed_drv_revol; /**< drive shaft revolution */
    uint32_t enc_resol; /**< encoder resolution per motor revolution */
    uint32_t mtr_revol; /**< motor revolution */
} factor_param_t;

/**
 * @brief
 *
 * @todo memory ares alienment
 *
 */
typedef struct parameter_data {
    //communication
    uint16_t    ethercatNodeNum;
    uint8_t     modbusNodeNum;
    uint8_t     modbusBaudrate;
    uint8_t     canId;
    uint8_t     canBaudrate;

    //alarm
    uint32_t    alarm_state;
    uint32_t    time_stamp;

    drv_hw_info drv_info_param;      //0x2000
    hw_sensor   hw_sen_param;
    motor       mtr_param;          //0x2100
    encoder     enc_param;          //0x2200| 0x2220 | 0x2240
    spd_fb      spd_fb_param;       //0x2280
    trq_ctrl    trq_ctrl_param;     //0x3100
    spd_ctrl    spd_ctrl_param;     //0x3200

    uint16_t err_code;              /**< Error Code (alarm code -> fsm)*/

    uint16_t crtl_word;             /**< Control Word 구현해야함*/
    uint16_t status_word;           /**< Status Word 구현해야함*/

    int16_t quick_stop_op;          /**< Quickstop Option Code */
    int16_t shutdown_op;            /**< Shutdown Option Code */
    int16_t disable_op;             /**< Disable Operation Option Code */
    int16_t halt_op;                /**< Halt Option Code */
    int16_t fault_re;               /**< Fault Reaction Code */

    int8_t opmode;                  /**< Modes of Operation (fsm)*/
    int8_t opmode_display;          /**< Modes of Operation Display (fsm)*/

    int32_t pos_actual_val;         /**< Position Actual Value 써야함[pulse]*/
    uint32_t following_err_window;  /**< Following Error Window 써야함[pulse]*/
    uint32_t pos_window;            /**< Position Window 써야함[pulse]*/
    int32_t vel_demand_val;         /**< Velocity Demand Value 써야함[ppr]*/
    int32_t vel_actual_val;         /**< Velocity Actual Value 써야함[ppr]*/
    uint16_t vel_window;            /**< Velocity Window 써야할듯*/
    uint16_t vel_window_ti;         /**< Velocity Window Time 써야할듯*/

    int16_t target_trq;             /**< Target Torque 써야함[0.1%,모터 정격 대비]*/
    int16_t trq_demand;             /**< Torque Demand 써야할듯[0.1%,모터 정격 대비]*/
    int16_t trq_actual_value;       /**< Torque Actual Value 써야함[0.1%,모터 정격 대비]*/
    int16_t curr_actual_value;      /**< Current Actual Value 써야함*[0.1% 모터 정격 전류 대비]*/
    uint32_t dc_link_circuit_vol;   /**< DC Link Circuit Voltage 써야함[mV]*/
    int32_t target_pos;             /**< Target Position 써야함[pulse]*/
    int32_t min_pos_range_limit;    /**< Min Position Range Limit 안쓸듯[pulse]*/
    int32_t max_pos_range_limit;    /**< Max Position Range Limit 안쓸듯[pulse]*/
    int32_t home_offset;            /**< Home Offset 써야할듯[pulse]*/
    int32_t sw_min_pos_limit;       /**< Software Min Position Limit 안쓸듯[pulse]*/
    int32_t sw_max_pos_limit;       /**< Software Max Position Limit 안쓸듯[pulse]*/
    uint8_t pol;                    /**< Polarity 써야할듯[1 or 0]*/
    uint32_t max_profile_vel;       /**< Max Profile Velocity 모르겠음*/

    uint32_t profile_vel;           /**< Profile Velocity 모르겠음*/
    uint32_t profile_accel;         /**< Profile Acceleration 모르겠음*/
    uint32_t profile_decel;         /**< Profile Deceleration 모르겠음*/
    uint32_t quick_stop;            /**< Quickstop Declaration 모르겠음*/
    int16_t motion_profile_type;    /**< Motion Profile Type 모르겠음*/
    uint32_t trq_slope;             /**< Torque Slope 모르겠음*/
    int16_t trq_profile_type;       /**< Torque Profile Type 모르겠음*/

    factor_param_t unit_factor;     /**< User unit factor */
    int8_t homing_method;           /**< Homing Method 모르겠음*/
    uint32_t switch_search_speed;   /**< Switch Searching Speed in Homing 모르겠음*/
    uint32_t zero_search_speed;     /**< Zero Searching Speed in Homing 모르겠음*/
    uint32_t homing_accel;          /**< Homing Acceleration 모르겠음*/

    int16_t trq_offset;             /**< Torque Offset 안쓸듯[0.1%]*/
    uint16_t touch_probe_fxn;       /**< Touch Probe Function 모르겠음*/
    uint16_t touch_probe_status;    /**< Touch Probe Status 모르겠음*/
    int32_t touch_probe_1_po;       /**< Touch Probe 1 Positive Edge 모르겠음*/
    int32_t touch_probe_1_ne;       /**< Touch Probe 1 Negative Edge 모르겠음*/

    uint32_t max_accel;             /**< Max Acceleration 모르겠음*/
    uint32_t max_decel;             /**< Max Deceleration 모르겠음*/

    uint16_t po_trq_limit;          /**< Positive Torque Limit 써야함[0.1%]*/
    uint16_t ne_trq_limit;          /**< Negative Torque Limit 써야함[0.1%]*/
    int32_t add_pos_actual_val_1;   /**< Additional Position Actual Value 1 써야할듯[pulse]*/
    uint32_t add_pos_enc_resol_1;   /**< Additional Position Encoder Resolution 1 써야할듯[pulse]*/
    uint32_t add_gear_ratio_numer_1;/**< Additional Gear Ratio Numerator 1 모르겠음*/
    uint32_t add_gear_ratio_denom_1;/**< Additional Gear Ratio Denominator 1 모르겠음*/

    int32_t follow_err_actual_val;  /**< Following Error Actual Value 써야할듯[pulse]*/
    int32_t pos_demand_internal_val;/**< Position Demand Internal Value 써야할듯[pulse]*/
    uint32_t digital_input;         /**< Digital Inputs 안쓸듯*/
    uint32_t digital_output;        /**< Digital Outputs 안쓸듯*/
    int32_t target_vel;             /**< Target Velocity 써야함[ppr]*/

    uint16_t mtr_type;              /**< Motor Type 안쓸듯*/
    uint8_t* mtr_catalog_num;       /**< Motor Catalog Number 안쓸듯*/

    uint32_t support_drive_mode;    /**< Supported Drive Modes 안쓸듯*/
} parameter_data_t;
/*------------------------------------------------------------------------------
------
------    Macro
------
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
------
------    variables(external)
------
------------------------------------------------------------------------------*/
extern parameter_data_t ares_lt_param;
/*------------------------------------------------------------------------------
------
------    Functions
------
------------------------------------------------------------------------------*/


#endif // PARAMETER_H