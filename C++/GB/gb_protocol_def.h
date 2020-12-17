#ifndef __GB_PROTOCOL_DEF_H__
#define __GB_PROTOCOL_DEF_H__
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include <stdint.h>
/*-----------------------------------------------------------------------------
 * MACROS
 *---------------------------------------------------------------------------*/
#define OFFSET_SEC_OF_GMT8 28800
#define PROTO_MIN_LENGTH 25
#define PROTO_TBOX_VIN_LEN 17
#define PROTO_HEADER_SIGN '#'
#define PROTO_TIME_LEN 6
#define PROTO_ICCID_LEN 20

#define MAX_SINGLE_CELL_NUM_OF_CURRENT_FRAME 150
#define MAX_CHARGABLE_SYS_PROBE_NUM 150
#define SECRETKEY_SIZE 16

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/

typedef enum
{
	COMMAND_LOG_ON = 0x01,
	COMMAND_REALTIME_INFO = 0X02,
	COMMAND_HISTORY_INFO = 0X03,
	COMMAND_LOG_OUT = 0X04,
	COMMAND_HEART_BEAT = 0X07,
	COMMAND_CHECK_TIME = 0X08,
} HeaderCommandByte_e;

typedef enum
{
	ACK_DEFAULT = 0,
	ACK_SUCCESS = 0x01,
	ACK_FALSE = 0X02,
	ACK_VIN_EXIST = 0X03,
	ACK_COMMAND = 0XFE
} HeaderAckByte_e;

typedef enum
{
	ENCRYPTTYPE_PLAIN = 0x01,
	ENCRYPTTYPE_RSA = 0X02,
	ENCRYPTTYPE_AES128 = 0X03,
	ENCRYPTTYPE_ERR = 0Xfe,
	ENCRYPTTYPE_INVALID = 0Xff,
} HeaderEncryptType_e;

typedef enum
{
	ID_OF_VEHICLE_INFO = 0x01,
	ID_OF_DRIVING_MOTOR = 0X02,
	ID_OF_FUEL_CELL = 0X03,
	ID_OF_ENGINE_INFO = 0X04,
	ID_OF_VEHICLE_LOCATION = 0X05,
	ID_OF_CHARGABLE_SYS = 0X06,
	ID_OF_CHARGABLE_SYS_TMP = 0X07,
	ID_OF_EXTREME_INFO = 0X08,
	ID_OF_ALARM_INFO = 0X09,
} InfoTypeID_e;

#pragma pack(push, 1)
// Packet Header, 7bytes
typedef struct PacketHeader
{
	char header_sign1;
	char header_sign2;
	uint8_t command_byte;
	uint8_t ack_byte;
	char tbox_vin[PROTO_TBOX_VIN_LEN + 1];
	uint8_t encrypt_type;
	uint16_t data_length;
} PacketHeader_t;
//Packet Tail, 1 byte
typedef uint8_t PacketTail_t;

//GMT+8
typedef struct GDTimeStruct
{
	uint8_t year;
	uint8_t month;
	uint8_t data;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} GDTimeStruct_t;

typedef struct DrivingMotorData
{
	uint8_t driving_motor_ID;
	uint8_t driving_motor_status;
	uint8_t driving_motor_control_tmp;
	uint16_t driving_motor_speed;
	uint16_t driving_motor_torque;
	uint8_t driving_motor_tmp;
	uint16_t motor_controlor_votage_in;
	uint16_t motor_controler_dc_generatrix_current;
} DrivingMotorData_t;

typedef struct ChargableSysDataPart1
{
	uint8_t chargable_sys_ID;
	uint16_t chargable_sys_votage;
	uint16_t chargable_sys_current;
	uint16_t single_cell_num;
	uint16_t start_cell_ID_of_current_frame;
	uint8_t single_cell_num_of_current_frame;
} ChargableSysDataPart1_t;
typedef struct ChargableSysData
{
	ChargableSysDataPart1_t chargable_sys_data_part1;
	//[MAX_SINGLE_CELL_NUM_OF_CURRENT_FRAME]
	uint16_t single_Cell_votage_list[MAX_SINGLE_CELL_NUM_OF_CURRENT_FRAME];
} ChargableSysData_t;

typedef struct ChargableSysTmpDataPart1
{
	uint8_t chargable_sys_ID;
	uint16_t chargable_sys_probe_num;
} ChargableSysTmpDataPart1_t;
typedef struct ChargableSysTmpData
{
	ChargableSysTmpDataPart1_t chargable_sys_tmp_data_part1;
	//[MAX_CHARGABLE_SYS_PROBE_NUM]
	uint8_t tmp_value_list_of_probe[MAX_CHARGABLE_SYS_PROBE_NUM];
} ChargableSysTmpData_t;

typedef struct LogOnInfo
{
	GDTimeStruct_t logon_time;
	uint16_t serial_number;
	char tbox_iccid[PROTO_ICCID_LEN];
	uint8_t chargable_sysnum; //0-250
	uint8_t chargable_sys_codelen; //0-50
	//[MAX_CHARGABLE_SYSNUM * MAX_CHARGABLE_SYS_CODELEN]
	char* chargable_sys_ptr;
} LogOnInfo_t;

typedef struct LogOutInfo
{
	GDTimeStruct_t logout_time;
	uint16_t serial_number;
} LogOutInfo_t;

//ID_OF_VEHICLE_INFO = 0x01,
typedef struct VehicleInfo
{
	uint8_t vehicle_status;
	uint8_t charge_status;
	uint8_t running_mode;
	uint16_t vehicle_speed;
	uint32_t accumulated_odo;
	uint16_t whole_votage;
	uint16_t whole_current;
	uint8_t soc;
	uint8_t DC_DC_status;
	uint8_t gear_pos;
	uint16_t insulation_resistance;
	uint8_t acc_pedal_distance;
	uint8_t brake_pedal_status;
} VehicleInfo_t;

//	ID_OF_DRIVING_MOTOR = 0X02,
typedef uint8_t DrivingMotorNum_t;
typedef struct DrivingMotorInfo
{
	DrivingMotorNum_t driving_motor_num;
	//IM ISG SAM
	DrivingMotorData_t driving_motor_data_list[3];
} DrivingMotorInfo_t;

//	ID_OF_FUEL_CELL = 0X03,
typedef struct FuelCellInfo
{
	uint16_t fuel_cell_votage;
	uint16_t fuel_cell_current;
	uint16_t fuel_cost_rate;
	uint16_t fuel_cell_tmpprobe_num;
	//[MAX_FUEL_CELL_tmpPROBE_NUM]
	uint8_t* tmpprobe_value_ptr;
	uint16_t max_hsys_tmp;
	uint8_t max_hsys_tmp_probeID;
	uint16_t highest_H_potency;
	uint8_t highest_H_potency_sensorID;
	uint16_t highest_H_press;
	uint8_t highest_H_press__sensorID;
	uint8_t highpress_DC_DC_status;
} FuelCellInfo_t;

//	ID_OF_ENGINE_INFO = 0X04,
typedef struct EngineInfo
{
	uint8_t engine_status;
	uint16_t axle_speed;
	uint16_t fuel_cost_rate;

} EngineInfo_t;

//	ID_OF_VEHICLE_LOCATION = 0X05,
typedef struct VehicleLocation
{
	uint8_t fix_status;
	int32_t longtitude;
	int32_t altitude;
} VehicleLocation_t;

//	ID_OF_EXTREME_INFO = 0X06,
typedef struct ExtermInfo
{
	uint8_t highest_votage_cell_sys_ID;
	uint8_t highest_votage_cell_single_ID;
	uint16_t highest_value_of_votage_cell_single;
	uint8_t lowest_votage_cell_sys_ID;
	uint8_t lowest_votage_cell_single_ID;
	uint16_t lowest_value_of_votage_cell_single;
	uint8_t highest_tmp_assembly_ID_in_chargable_sys;
	uint8_t highest_tmp_proble_ID_in_assembly;
	uint8_t highest_tmp_value_in_chargable_sys;
	uint8_t lowest_tmp_assembly_ID_in_chargable_sys;
	uint8_t lowest_tmp_proble_ID_in_assembly;
	uint8_t lowest_tmp_value_in_chargable_sys;
} ExtermInfo_t;

//	ID_OF_ALARM_INFO = 0X07,
typedef struct AlarmInfo
{
	uint8_t highest_alarm_level;
	uint32_t common_alarm_flag;
	uint8_t failure_num_in_chargable_sys;
	//[MAX_FAILURE_NUM_IN_CHARGABLE_SYS]
	uint32_t failure_code_list_of_chargable_sys[60];
	uint8_t failure_num_of_driving_motor;
	//[MAX_FAILURE_NUM_OF_DRIVING_MOTOR]
	uint32_t failure_code_list_of_driving_motor[180];
	uint8_t failure_num_of_engine;
	//[MAX_FAILURE_NUM_OF_ENGINE]
	uint32_t failure_code_list_of_engine[60];
	uint8_t failure_num_of_others;
//[MAX_FAILURE_NUM_OF_OTHERS]
//uint32_t* failure_code_list_of_others_ptr;
} AlarmInfo_t;

//ID_OF_CHARGABLE_SYS = 0X08,
typedef uint8_t ChargableSysNum_t;

typedef struct ChargableSysInfo
{
	ChargableSysNum_t chargable_sys_num;
	ChargableSysData_t chargable_sys_Data;
} ChargableSysInfo_t;

//ID_OF_CHARGABLE_SYS_TMP = 0X09,
typedef struct ChargableSysTmpInfo
{
	ChargableSysNum_t chargable_sys_num;
	ChargableSysTmpData_t chargable_sys_tmp_data;
} ChargableSysTmpInfo_t;

#pragma pack(pop)

#ifdef __cplusplus  // close out "C" linkage in case of c++ compiling
}
#endif

#endif /* __GB_PROTOCOL_DEF_H__ */