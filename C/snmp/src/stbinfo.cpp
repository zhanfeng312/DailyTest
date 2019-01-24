#include "stbinfo.h"
#include <string.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <sys/system_properties.h>

#define NT_LOG_OUTPUT_LVL 5
#define NT_LOG_TAG  "nt_stbinfo"
#include "_nt_common.h"


#define BUFF_SIZE             (128)
#define WIRED_INTERFACE       "eth0"
#define WLAN_INTERFACE        "wlan0"
#define PING_SERVER           "168.95.1.1"
#define MAC_ADDRESS_FILE      "/sys/class/net/"WIRED_INTERFACE"/address"

#define DOMAIN_PROP           "persist.stbs.domain"
#define DNS_SERVER_PROP       "persist.stbs.dns"
#define TIME_SERVER_PROP      "persist.stbs.ntp.ser"
#define STB_SERVER1_PROP      "persist.stbs.server1"
#define STB_SERVER2_PROP      "persist.stbs.server2"
#define STB_SERVER3_PROP      "persist.stbs.server3"

#define CPU_NAME              "MSO9380AV"
#define STB_ID                "MOD503"
#define DECODER_INFO          "MSO9380AV"

#define IFCONFIG_ETH          "busybox ifconfig "WIRED_INTERFACE
#define GET_IP                "| grep \"inet addr\" | busybox sed 's/.*inet addr://g' | busybox sed 's/ .*$//g'"
#define GET_MASK              "| grep \"Mask\" | busybox sed 's/.*Mask://g'"
#define IP_ROUTE_TABLE_MAIN   "ip route show table main"
#define GET_2DOT4_STATE       "| grep \""WLAN_INTERFACE"\""

#define SURE_POPEN(cmd) \
    do {    \
        fp = NULL; \
        if(cmd == NULL) { \
            nlog_e("popen NULL\n"); \
            return -1; \
        } else if ((fp = popen(cmd, "r")) == NULL) { \
            nlog_e("can not popen [%s]\n", (char *)cmd); \
            return -1; \
        } else { \
            /*nlog_e("popen [%s] success\n", (char *)cmd)*/; \
        } \
    } while (0)


static int get_stbinfo_via_popen_without_get_result(const char *cmd)
{
    FILE *fp = NULL;
    int ret = -1;

    if (cmd == NULL || *cmd == 0){

        nlog_e("input wrong\n");
        return -1;
    }

    SURE_POPEN(cmd);
    char value[BUFF_SIZE] = {0};

    if (!fgets(value, sizeof(value), fp)){
        ret = -1;
    }
    else{
        ret = 0;
    }

    pclose(fp);
    fp = NULL;
    
    return ret;
}

static int get_stbinfo_via_popen(const char *cmd, char *value, int len)
{
    FILE *fp = NULL;

    if (cmd == NULL || *cmd == 0 || value == NULL || len <= 0){

        nlog_e("input wrong\n");
        return -1;
    }

    SURE_POPEN(cmd);
    memset(value, 0, len);
    
    if (fread(value, 1, len - 1, fp) <= 0){

        nlog_e("can not read!\n");
        pclose(fp);
        fp = NULL;

        return -1;
    }
    
    if ((len = strlen(value)) > 0 && *(value + len - 1) == '\n'){

        *(value + len - 1) = 0;
    }

    pclose(fp);
    fp = NULL;
    
    return 0;
}

#define SURE_FOPEN(file_path) \
    do {    \
        if ((fp = fopen(file_path, "r")) == NULL) { \
            nlog_e("open file %s failed!\n", file_path); \
            return -1; \
        } else { \
            /*nlog_e("open file [%s] success\n", file_path)*/; \
        } \
    } while (0)

static int get_stbinfo_via_read_file(STBInfo_e type, char *value, int len)
{
    if (value == NULL || len <= 0){
        
        nlog_e("input wrong!\n");
        return -1;
    }

    FILE *fp = NULL;
    
    switch(type){

    case NETWORK_MAC_ADDRESS:
        SURE_FOPEN(MAC_ADDRESS_FILE);
        break;
    default:
        break;
    }

    memset(value, 0, len);
    if (fread(value, 1, len - 1, fp) <= 0){
        
        nlog_e("can not read\n");
        fclose(fp);
        fp = NULL;
        return -1;
    }
    if ((len = strlen(value)) > 0 && *(value + len - 1) == '\n'){
        
        *(value + len - 1) = 0;
    }

    fclose(fp);
    fp = NULL;

    return 0;    
}

static int get_mem_info(char *pInfo, int len)
{
    if (pInfo == NULL || len <= 0){

        nlog_e("input wrong!\n");
        return -1;
    }

    struct sysinfo info;
    memset(&info, 0, sizeof(info));

    if (0 != sysinfo(&info)) {
        
        nlog_e("get sysinfo failed!\n");
        return -1;
    }

    unsigned long totalram = info.totalram;
    unsigned long usedram = info.totalram - info.freeram;

    snprintf(pInfo, len, "%lu MB/%lu MB", usedram / (1024 * 1024), totalram / (1024 * 1024));

    return 0;
}

static int get_cpu_loadinfo(char *pInfo, int len)
{
    if (pInfo == NULL || len <= 0){

        nlog_e("input wrong!\n");
        return -1;
    }
    
    FILE *fp = NULL;
    char buf[BUFF_SIZE] = {0};
    char cpu[5] = {0};

    long int user, nice, sys, idle, iowait, irq, softirq;
    long int cpu_all1, cpu_all2, cpu_idle1, cpu_idle2;
    float cpu_usage;

    int index = 0;
    do{
        SURE_FOPEN("/proc/stat");

        /* get the first line data*/
        fgets(buf, sizeof(buf), fp);
        
        sscanf(buf, "%s%ld%ld%ld%ld%ld%ld%ld", cpu, &user, &nice, &sys, &idle, &iowait, &irq, &softirq);

        int tmp_sum_value = user + nice + sys + idle + iowait + irq + softirq;

        if (index == 0) {
            cpu_all1 = tmp_sum_value;
            cpu_idle1 = idle;

            fclose(fp);
        }
        else {
            cpu_all2 = tmp_sum_value;
            cpu_idle2 = idle;
            break;
        }

        usleep(100000);
        memset(buf, 0, sizeof(buf));
        cpu[0] = '\0';
        user = nice = sys = idle = iowait = irq = softirq = 0;
        index++;
    } while (index < 2);

   
    cpu_usage = (float)(cpu_all2 - cpu_all1 - (cpu_idle2 - cpu_idle1)) / (cpu_all2 - cpu_all1) * 100;
    nlog_d("get the cpu usage rate is %.2f%%\n", cpu_usage);

    snprintf(pInfo, len, "%.2f%%", cpu_usage);
    
    return 0;
}

static int get_stb_server_ip(char *pInfo)
{
    char ip[20] = {0};
    __system_property_get(STB_SERVER1_PROP, ip);
    if (strlen(ip) > 0){
        strncat(pInfo, ip, strlen(ip));
        strncat(pInfo, ", ", 2);
    }
    memset(ip, 0, sizeof(ip));
    __system_property_get(STB_SERVER2_PROP, ip);
    if (strlen(ip) > 0){
        strncat(pInfo, ip, strlen(ip));
        strncat(pInfo, ", ", 2);
    }
    memset(ip, 0, sizeof(ip));
    __system_property_get(STB_SERVER3_PROP, ip);
    if (strlen(ip) > 0){
        strncat(pInfo, ip, strlen(ip));
    }
    
    return 0;
}

static int get_current_system_time(char *pInfo, int len)
{
    if (pInfo == NULL || len <= 0){

        nlog_e("input wrong!\n");
        return -1;
    }

    struct tm *ptr = NULL;
    time_t lt;
    
    lt = time(NULL);
    ptr = localtime(&lt);

    strftime(pInfo, len, "%F %h %T", ptr);

    return 0;
}

int get_string_type_stb_info(STBInfo_e type, char * pValue, int len)
{
    if (pValue == NULL || len <= 0) {

        nlog_e("input wrong!\n");
        return -1;
    }

    char *tmp_value = (char *)malloc(BUFF_SIZE * sizeof(char));
    memset(tmp_value, 0, BUFF_SIZE);

    char cmd[BUFF_SIZE] = {0};

    nlog_d("get stb info, type is %d\n", type);

    switch (type)
    {
    case NETWORK_DEVICE:
        strcpy(tmp_value, WIRED_INTERFACE);
        break;
    //case NETWORK_TYPE:
    case NETWORK_MAC_ADDRESS:
        get_stbinfo_via_read_file(NETWORK_MAC_ADDRESS, tmp_value, BUFF_SIZE);
        break;
    case NETWORK_DOMAIN:
        __system_property_get(DOMAIN_PROP, tmp_value);
        break;
    case NETWORK_DNS_SERVER_IP:
        __system_property_get(DNS_SERVER_PROP, tmp_value);
        break;
    case NETWORK_TIME_SERVER_IP:
        __system_property_get(TIME_SERVER_PROP, tmp_value);
        break;
    case NETWORK_STB_SERVER_IP:
        get_stb_server_ip(tmp_value);
        break;
    //case NETWORK_TOTAL_BIT_RATE:
    case NETWORK_IP_ADDRESS:
        snprintf(cmd, sizeof(cmd) - 1, "%s %s", IFCONFIG_ETH, GET_IP);
        if (get_stbinfo_via_popen(cmd, tmp_value, BUFF_SIZE) != 0){
            snprintf(tmp_value, BUFF_SIZE, "%s", "0.0.0.0");
        }
        break;
    case NETWORK_MASK:
        snprintf(cmd, sizeof(cmd) - 1, "%s %s", IFCONFIG_ETH, GET_MASK);
        if (get_stbinfo_via_popen(cmd, tmp_value, BUFF_SIZE) != 0){
            snprintf(tmp_value, BUFF_SIZE, "%s", "0.0.0.0");
        }
        break;
    //case NETWORK_GATEWAY:
    case NETWORK_2DOT4G_STATE:
        snprintf(cmd, sizeof(cmd) - 1, "%s %s", IP_ROUTE_TABLE_MAIN, GET_2DOT4_STATE);
        if (get_stbinfo_via_popen_without_get_result(cmd) != 0){
            snprintf(tmp_value, BUFF_SIZE, "%s", "Off");
        }else{
            snprintf(tmp_value, BUFF_SIZE, "%s", "On");
        }
        break;
    case NETWORK_2DOT4G_WEB_CONNECTION:
        {
            snprintf(cmd, sizeof(cmd) - 1, "busybox ping -c1 -w1 -I%s %s 2>/dev/null", WLAN_INTERFACE, PING_SERVER);
            if (get_stbinfo_via_popen_without_get_result(cmd) != 0){
                snprintf(tmp_value, BUFF_SIZE, "%s", "No - ");
            }else{
                snprintf(tmp_value, BUFF_SIZE, "%s", "Ok - ");
            }
            
            char tmp_buff[50] = {0};
            get_stbinfo_via_popen("date", tmp_buff, sizeof(tmp_buff));
            strncat(tmp_value, tmp_buff, strlen(tmp_buff));
        }
        break;
    case RESOURCE_CPU:
        strcpy(tmp_value, CPU_NAME);
        break;
    case RESOURCE_OS_VER:
        {
            char buf[20] = {0};
            __system_property_get("ro.build.version.release", buf);
            snprintf(tmp_value, BUFF_SIZE, "Android %s", buf);
        }
        break;
    case RESOURCE_STB_ID:
        strcpy(tmp_value, STB_ID);
        break;
    case RESOURCE_MEM_INFO:
        get_mem_info(tmp_value, BUFF_SIZE);
        break;
    //case RESOURCE_TIME_ZONE:
    case RESOURCE_CPU_LOAD:
        get_cpu_loadinfo(tmp_value, BUFF_SIZE);
        break;
    //case RESOURCE_DISK_UNUSED_SPACE:
    case RESOURCE_DECODER_INFO:
        strcpy(tmp_value, DECODER_INFO);
        break;
    case RESOURCE_SYSTEM_TIME:
        get_current_system_time(tmp_value, BUFF_SIZE);
        break;
    //case RESOURCE_STB_STATUS:
    default:
        break;
    }

    nlog_d("get the value of type(%d) is %s\n", type, tmp_value);

    snprintf(pValue, len, "%s", tmp_value);
    free(tmp_value);
    tmp_value = NULL;

    return 0;
}