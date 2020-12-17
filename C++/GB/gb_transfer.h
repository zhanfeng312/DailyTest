#ifndef __GB_TRANSFER_H__
#define __GB_TRANSFER_H__

#include "gb_protocol_def.h"
#include <string>

class GBTransfer {
public:
	static GBTransfer& getInstance() {
		static GBTransfer __instance;
		return __instance;
	}
	void ParseGBData(std::string gbData);

private:
	GBTransfer();
	virtual ~GBTransfer();
	void GetHeader(std::string header);
	void GetVehicleInfo();
    void GetChargableSysTmpInfo();
	void GetChargableSysInfo();
	void GetAlarmInfo();
	void GetLocationInfo();
	void GetDrivingMotorInfo();
	void ascii_to_hex(const uint8_t* ascii_buf,int32_t ascii_buf_size,int8_t* hex_buf);

	PacketHeader_t sHeader;
    VehicleInfo_t sVehicleInfo;
	DrivingMotorInfo_t sDrivingMotorInfo;
	VehicleLocation_t sLocationInfo;
	ExtermInfo_t sExtermInfo;
	ExtermInfo_t sExtermInfo_tmp;
	AlarmInfo_t sAlarmInfo;
	ChargableSysInfo_t sChargableSysInfo;
	ChargableSysTmpInfo_t sChargableSysTmpInfo;
};
#endif //__GB_TRANSFER_H__