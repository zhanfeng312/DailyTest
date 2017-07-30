#ifndef _UDC_PROTOCOL_H_
#define _UDC_PROTOCOL_H_

#include <time.h>
#include "udc_ratings_product.h"//todo remove
#include "udc_datatype.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef void udc_handle;

typedef void(*request_spectrum_data)(int start_frequecy, int end_frequecy, int count);

#define IDC_IPINFO_DNS_MAX_COUNT (4)
#define UDC_IPINFO_VLAUS_MAX_LEN (32)
#define UDC_IPINFO_TYPE_DHCPSTR "DHCP"
#define UDC_IPINFO_TYPE_STATICSTR "Manual"
typedef enum
{
    UDC_IPINFO_TYPE_UNKNOWN = -1,
    UDC_IPINFO_TYPE_DHCP = 0,
    UDC_IPINFO_TYPE_STTAIC,
}UDC_IPINFO_TYPE_e;
typedef struct __UDC_IPINFO_t
{
    UDC_IPINFO_TYPE_e enAddressingType;
    char aAddress[UDC_IPINFO_VLAUS_MAX_LEN];
    char aMask[UDC_IPINFO_VLAUS_MAX_LEN];
    char aGateWay[UDC_IPINFO_VLAUS_MAX_LEN];
    char aDns[IDC_IPINFO_DNS_MAX_COUNT][UDC_IPINFO_VLAUS_MAX_LEN];
}UDC_IPINFO_t;
typedef int(*request_ipinfo_data)(UDC_IPINFO_t *stInfo, int *pNum);


#define UDC_CABLE_MAX_COUNT (8)
typedef enum
{
    UDC_CABLE_Modulation_QAM_NONE  = 0x00,  /*δ���� */
    UDC_CABLE_Modulation_QAM16     = 0x01,  /*16 -QAM*/
    UDC_CABLE_Modulation_QAM32     = 0x02,  /*32 -QAM*/
    UDC_CABLE_Modulation_QAM64     = 0x03,  /*64 -QAM*/
    UDC_CABLE_Modulation_QAM128    = 0x04,  /*128-QAM*/
    UDC_CABLE_Modulation_QAM256    = 0x05,  /*256-QAM*/
    UDC_CABLE_Modulation_QAM_RESERVE = 0xFF /*Ԥ��*/
} UDC_CABLE_Modulation_e;
typedef struct __UDC_CABLE_t
{
    UDC_CABLE_Modulation_e             enModulation;
    int                                                 iFreqKHz;
    int                                                 iSNRdB;
    int                                                 iPowerdBmV;
    int                                                 iBER;
    int                                                 iSymbolRate;
    int                                                 iLocked; //0:unlocked 1:locked
    int                                                 iQuality;
}UDC_CABLE_t;
typedef int(*request_cable_data_cb)(UDC_CABLE_t *stInfo, int *pNum);

#define UDC_ERRORCODE_MAX_COUNT (256)
typedef struct __UDC_ERRORCODE_t
{
    time_t stTimeMs;
    int iErrorCode;
}UDC_ERRORCODE_t;
typedef int(*request_errorcode_data_cb)(UDC_ERRORCODE_t *stInfo, int *pNum);


typedef struct
{
	char	stbId[127 + 1];
	char	cardNo[63 + 1];
	char	regionCode[15 + 1];
	char	manufacturer[15 + 1];
	char	deviceType[15 + 1];
	char	mac[31 + 1];
	char	cpu[127 + 1];
	char	softwareVersion[31 + 1];
	char	hardwareVersion[31 + 1];
	char	rd[31 + 1];
} BootUDCPost_s;


typedef struct udc_conf_s
{
	char url[80];
	char hearbeat_url[80];
	int auth_type;
	char username[60];
	char pwd[60];

	request_spectrum_data spectrum_request;

	BootUDCPost_s bootpost;

	request_ipinfo_data ipinfo_request;

	request_cable_data_cb cable_request_cb;
    
    request_errorcode_data_cb errorcode_request_cb;

}udc_conf_t;

udc_handle* udc_protocol_new(void);

int udc_protocol_setup(udc_handle *handle, udc_conf_t *conf);

void udc_rpc_spectrum_cb(unsigned int *data, unsigned int count_byte);

int udc_ratingsdata_write(UDC_WATCH_TYPE_e watch_type, int frequency, int serviceId, int tsId, int volume, int bStartFlag);

int udc_advdata_write(UDC_ADV_DATA_t data);

int udc_voddata_write(UDC_VOD_DATA_t data);

int udc_timeshiftdata_write(UDC_TIMESHIFT_DATA_t data);

int udc_pagesdata_write(UDC_PAGES_DATA_t data);

int udc_cadata_write(UDC_CA_DATA_t data);

int udc_pvrdata_write(UDC_PVR_DATA_t data);

int udc_searchdata_write(UDC_SEARCH_DATA_t data);

int udc_protocol_start(udc_handle *handle);

int udc_protocol_stop(udc_handle *handle);

int udc_protocol_cleanup(udc_handle *handle);



#ifdef __cplusplus
}
#endif

#endif//_UDC_PROTOCOL_H_



//todo auto check BootUDCPost_s len and buf len, build err
//lib
//win linux h