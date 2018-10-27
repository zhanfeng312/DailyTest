#include "stbinfo.h"

#define NT_LOG_OUTPUT_LVL 5
#define NT_LOG_TAG  "test_stbinfo"
#include "_nt_common.h"

int main(int argc, char *argv[])
{
	nlog_d("This is my test program!\n");
	nlog_d("---------------------------\n");

	char pInfo[128] = { 0 };
    
	get_string_type_stb_info(NETWORK_DEVICE, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

	nlog_d("---------------------------\n");
    
	get_string_type_stb_info(NETWORK_MAC_ADDRESS, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(NETWORK_DOMAIN, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(NETWORK_DNS_SERVER_IP, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(NETWORK_TIME_SERVER_IP, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(NETWORK_STB_SERVER_IP, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(NETWORK_IP_ADDRESS, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(NETWORK_MASK, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(NETWORK_2DOT4G_STATE, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(NETWORK_2DOT4G_WEB_CONNECTION, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(RESOURCE_CPU, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(RESOURCE_OS_VER, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

	get_string_type_stb_info(RESOURCE_STB_ID, pInfo, sizeof(pInfo));
    memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");
    
	get_string_type_stb_info(RESOURCE_MEM_INFO, pInfo, sizeof(pInfo));
	memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(RESOURCE_CPU_LOAD, pInfo, sizeof(pInfo));
	memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(RESOURCE_DECODER_INFO, pInfo, sizeof(pInfo));
	memset(pInfo, 0, sizeof(pInfo));

    nlog_d("---------------------------\n");

    get_string_type_stb_info(RESOURCE_SYSTEM_TIME, pInfo, sizeof(pInfo));
	memset(pInfo, 0, sizeof(pInfo));

	nlog_d("---------------------------\n");
	nlog_d("test over!\n");

	return 0;
}