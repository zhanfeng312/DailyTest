#ifndef __STB_INFO_H__
#define __STB_INFO_H__

#ifdef  __cplusplus
extern "C" {
#endif

typedef enum {

	/*Net Info*/
	NETWORK_DEVICE,
	NETWORK_MAC_ADDRESS,
	NETWORK_IP_ADDRESS,
	NETWORK_MASK,
	NETWORK_DOMAIN,
	NETWORK_DNS_SERVER_IP,
	NETWORK_TIME_SERVER_IP,
	NETWORK_STB_SERVER_IP,
	NETWORK_2DOT4G_STATE,
	NETWORK_2DOT4G_WEB_CONNECTION,

	/*Resource Info*/
	RESOURCE_CPU,
	RESOURCE_OS_VER,
	RESOURCE_STB_ID,
	RESOURCE_MEM_INFO,
	RESOURCE_CPU_LOAD,
	RESOURCE_DECODER_INFO,
	RESOURCE_SYSTEM_TIME,
}STBInfo_e;

int get_string_type_stb_info(STBInfo_e type, char *pValue, int len);

#ifdef  __cplusplus
}
#endif

#endif // !__STB_INFO_H__
