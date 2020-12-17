#include "gb_transfer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define Tranverse16(X) ((((uint16_t)(X) & 0xff00) >> 8)|(((uint16_t)(X) & 0x00ff) << 8))
#define Tranverse32(X) ((((uint32_t)(X) & 0xff000000) >> 24)|(((uint32_t)(X) & 0x00ff0000) >> 8)|(((uint32_t)(X) & 0x0000ff00) << 8)|(((uint32_t)(X) & 0x000000ff) << 24))

GBTransfer::GBTransfer()
{
    memset(&sVehicleInfo, 0, sizeof(sVehicleInfo));
}

GBTransfer::~GBTransfer()
{
    
}

void GBTransfer::ascii_to_hex(const uint8_t* ascii_buf, int32_t ascii_buf_size, int8_t* hex_buf)
{
    int32_t i = 0;

    for (; i < ascii_buf_size / 2; i++) {

        int8_t ch_high = ascii_buf[i * 2];
        int8_t ch_low = ascii_buf[i * 2 + 1];

        if (('0' <= ch_high) && ('9' >= ch_high))

            ch_high = ch_high - '0';

        else if (('A' <= ch_high) && ('F' >= ch_high))

            ch_high = ch_high - 'A' + 10;

        else if (('a' <= ch_high) && ('f' >= ch_high))

            ch_high = ch_high - 'a';


        if (('0' <= ch_low) && ('9' >= ch_low))

            ch_low = ch_low - '0';

        else if (('A' <= ch_low) && ('F' >= ch_low))

            ch_low = ch_low - 'A' + 10;

        else if (('a' <= ch_low) && ('f' >= ch_low))

            ch_low = ch_low - 'a';

        hex_buf[i] = (ch_high << 4) + ch_low;
    }
}

void GBTransfer::ParseGBData(std::string gbData)
{
    std::string str;

    if (gbData.length() > 48) {
        str = gbData.substr(0, 48); //首部长度
        printf("The header is %s\n", str.c_str());
        GetHeader(str);
    }
}

void GBTransfer::GetHeader(std::string header)
{
    int8_t *buf = (int8_t *)malloc(header.length()/2 + 1);
    if (buf == NULL) {
        printf("malloc failed, errno is %d\n", errno);
        exit(1);
    }
    int8_t *p = buf;
    ascii_to_hex((uint8_t*)header.c_str(), header.length(), buf);

    //23 23 03 FE 4C4C323237343039304C57303030323137 01 0151
    sHeader.header_sign1 = *p++;
    sHeader.header_sign2 = *p++;
    sHeader.command_byte = *p++;
    sHeader.ack_byte = *p++;
    memcpy(&sHeader.tbox_vin, p, 17);
    p += 17;
    sHeader.encrypt_type = *p++;
    memcpy(&sHeader.data_length, p, 2);
    sHeader.data_length = Tranverse16(sHeader.data_length);

    free(buf);
    buf = NULL;

    printf("type: %d, ack_type: %d, vin: %s, encrypt_type: %d, data_length: %d\n",
           sHeader.command_byte, sHeader.ack_byte, sHeader.tbox_vin, sHeader.encrypt_type, sHeader.data_length);

    switch (sHeader.command_byte) {
    case COMMAND_LOG_ON:
        printf("This is log on!\n");
        break;
    case COMMAND_LOG_OUT:
        printf("This is log out!\n");
        break;
    case COMMAND_REALTIME_INFO:
        printf("This is realtime data!\n");
        break;
    case COMMAND_HISTORY_INFO:
        printf("This is history data!\n");
        break;
    case COMMAND_HEART_BEAT:
        printf("This is heart beat!\n");
        break;
    default:
        break;
    }
}

void GBTransfer::GetVehicleInfo()
{
    return;
}

void GBTransfer::GetChargableSysTmpInfo()
{
    return;
}
void GBTransfer::GetChargableSysInfo()
{
    return;
}

void GBTransfer::GetAlarmInfo()
{
    return;
}
void GBTransfer::GetLocationInfo()
{
    return;
}

void GBTransfer::GetDrivingMotorInfo()
{
    return;
}