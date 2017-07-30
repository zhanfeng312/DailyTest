#ifndef __UDC_RATINGS_PRODUCT_H__
#define __UDC_RATINGS_PRODUCT_H__


#include "udc_datatype.h"

#define UDC_START_CALL 1
#define UDC_END_CALL 2

#ifdef __cplusplus
extern "C" {
#endif

int udc_ratings_data_write(UDC_WATCH_TYPE_e watch_type, int frequency, int serviceId, int tsId, int volume, int bStartFlag);

int udc_adv_data_write(UDC_ADV_DATA_t data);




//vod
int udc_vod_data_write(UDC_VOD_DATA_t data);




//timeshift
int udc_timeshift_data_write(UDC_TIMESHIFT_DATA_t data);




//pages
int udc_pages_data_write(UDC_PAGES_DATA_t data);




//search
int udc_search_data_write(UDC_SEARCH_DATA_t data);




//ca
int udc_ca_data_write(UDC_CA_DATA_t data);




//pvr
int udc_pvr_data_write(UDC_PVR_DATA_t data);

#ifdef __cplusplus //
}
#endif
#endif


