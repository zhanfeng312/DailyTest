#ifndef __UDC_ENUM_H__
#define __UDC_ENUM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#if ( defined __unix ) || ( defined __linux__ )
#ifndef _WINDLL_FUNC
#define _WINDLL_FUNC
#endif
#elif ( defined _WIN32 )
#ifndef _WINDLL_FUNC
#define _WINDLL_FUNC		_declspec(dllexport)
#endif
#endif

typedef enum
{
	UDC_EVENT_CODE_UNKNOWN = -1,
	UDC_EVENT_CODE_BOOT,
	UDC_EVENT_CODE_RATINGS,
	UDC_EVENT_CODE_HEARTBEAT,
	UDC_EVENT_CODE_ALARM,
	UDC_EVENT_CODE_INFORM,
	UDC_EVENT_CODE_MAX,
}UDC_EVENT_CODE_e;

typedef enum
{
	UDC_ALARM_EVENT_CODE_UNKNOWN = -1,
	UDC_ALARM_EVENT_CODE_SIGNALQUALITY,
	UDC_ALARM_EVENT_CODE_FRAMESLOST,
	UDC_ALARM_EVENT_CODE_PACKETSLOST,
	UDC_ALARM_EVENT_CODE_MAX,
}UDC_ALARM_EVENT_CODE_e;

typedef enum
{
	UDC_RPC_EVENT_CODE_UNKNOWN = -1,
	UDC_RPC_EVENT_CODE_SPECTRUM,
	UDC_RPC_EVENT_CODE_IPADDRESS,
	UDC_RPC_EVENT_CODE_SUBNETMASK,
	UDC_RPC_EVENT_CODE_MACADDRESS,
	UDC_RPC_EVENT_CODE_REGION,
	UDC_RPC_EVENT_CODE_MAX,
}UDC_RPC_EVENT_CODE_e;

typedef enum
{
	UDC_WATCH_TYPE_UNKNOWN = -1,
	UDC_WATCH_TYPE_TV,
	UDC_WATCH_TYPE_BROADCAST,
	UDC_WATCH_TYPE_OTHER,
	UDC_WATCH_TYPE_MAX,
}UDC_WATCH_TYPE_e;

#define UDC_ADV_UNKNOWN (-1)
#define UDC_ADV_FLYTEXT (0)
#define UDC_ADV_PIC (1)
#define UDC_ADV_VIDEO_ADV 2)
#define UDC_ADV_WEBURL (3)
#define UDC_ADV_XMLURL (4)
#define UDC_ADV_I_FRAME (5)
#define UDC_ADV_VIDEO_PATCH (6)
#define UDC_ADV_TYPE_MAX (7)

typedef enum
{
	UDC_SERVER_ERROR_CODE_UNKNOWN = -1,
	UDC_SERVER_ERROR_CODE_NOERROR,
	UDC_SERVER_ERROR_CODE_ERROR,
}UDC_SERVER_ERROR_CODE_e;

typedef enum
{
    UDC_DATA_START_CALL = 1,
    UDC_DATA_STOP_CALL
}UDC_DATA_CALL_TYPE;

typedef struct tagUDC_COMMON_DATA_t
{
    time_t	                                       stStartTime ;		
    time_t	                                       stStopTime;
    UDC_DATA_CALL_TYPE              enCallType;
}UDC_COMMON_DATA_t;


//ratings
typedef struct __UDC_RATINGS_W_DATA_t
{
    UDC_WATCH_TYPE_e	type;		
    int	                             frequency ;		
    int	                             serviceId ;
    int                                    tsId;
    int                                    volume;
}UDC_RATINGS_W_DATA_t;

typedef struct __UDC_RATINGS_DATA_t
{
    UDC_COMMON_DATA_t          stCData;
    UDC_RATINGS_W_DATA_t     stWData;
}UDC_RATINGS_DATA_t;

//adv
typedef struct
{
	int	iAdvType ;
	int	iAdvTypeId ;
	int	iADPositionID ;
	int	iADID ;
	int	iIsDefault ;
	int	iTimeOffset ;
	int	iAssetId ;
	int	iAreaCode ;
	int	iAction ;
	char	aChanelName[ 31 + 1 ] ;
	char	aContent[ 255 + 1 ] ;
	char	aCatalogId[ 63 + 1 ] ;
	char	aChannelId[ 63 + 1 ] ;
	char	aParameter[ 255 + 1 ] ;
} UDC_ADV_W_DATA_t ;
typedef struct __UDC_ADV_DATA_t
{
    UDC_COMMON_DATA_t       stCData;
    UDC_ADV_W_DATA_t          stWData;
}UDC_ADV_DATA_t;
_WINDLL_FUNC int DSCINIT_UDC_ADV_W_DATA_t( UDC_ADV_W_DATA_t *pst );
_WINDLL_FUNC int DSCSERIALIZE_JSON_UDC_ADV_W_DATA_t( void *pPst , char *encoding , char *buf , int *p_len );
_WINDLL_FUNC int DSCDESERIALIZE_JSON_UDC_ADV_W_DATA_t( char *encoding , char *buf , int *p_len , void *pst );



//vod
typedef struct
{
	int	iVODType ;
	int	iMovId ;
	int	iColumnID ;
	int	iDuration ;
	int	iRestTime ;
	int	iIpqam ;
	int	iIAction ;
	int	iStatus ;
	char	aProtocol[ 15 + 1 ] ;
	char	aVodStartTime[ 31 + 1 ] ;
	char	aVodEndTime[ 31 + 1 ] ;
	char	aQamname[ 31 + 1 ] ;
	char	aWorkSource[ 63 + 1 ] ;
	char	aMovAddetName[ 125 + 1 ] ;
	char	aParameter[ 255 + 1 ] ;
} UDC_VOD_W_DATA_t ;

typedef struct __UDC_VOD_DATA_t
{
    UDC_COMMON_DATA_t       stCData;
    UDC_VOD_W_DATA_t          stWData;
}UDC_VOD_DATA_t;
_WINDLL_FUNC int DSCINIT_UDC_VOD_W_DATA_t( UDC_VOD_W_DATA_t *pst );
_WINDLL_FUNC int DSCSERIALIZE_JSON_UDC_VOD_W_DATA_t( void *pPst , char *encoding , char *buf , int *p_len );
_WINDLL_FUNC int DSCDESERIALIZE_JSON_UDC_VOD_W_DATA_t( char *encoding , char *buf , int *p_len , void *pst );



//timeshift
#define UDC_OD_EVENTTYPE_TIMESHIFT (0)
#define UDC_OD_EVENTTYPE_PLAYBACK (1)
#define UDC_OD_EVENTTYPE_MAX (2)
typedef struct
{
	int	iEventType ;
	int	iProgramId ;
	int	iIpqam ;
	int	iAction ;
	char	aProtocol[ 15 + 1 ] ;
	char	aChanelName[ 31 + 1 ] ;
	char	aQamname[ 31 + 1 ] ;
	char	aTSStartTime[ 31 + 1 ] ;
	char	aTSEndTime[ 31 + 1 ] ;
	char	aProgramName[ 125 + 1 ] ;
	char	aParameter[ 255 + 1 ] ;
} UDC_TIMESHIFT_W_DATA_t ;

typedef struct __UDC_TIMESHIFT_DATA_t
{
    UDC_COMMON_DATA_t       stCData;
    UDC_TIMESHIFT_W_DATA_t          stWData;
}UDC_TIMESHIFT_DATA_t;
_WINDLL_FUNC int DSCINIT_UDC_TIMESHIFT_W_DATA_t( UDC_TIMESHIFT_W_DATA_t *pst );
_WINDLL_FUNC int DSCSERIALIZE_JSON_UDC_TIMESHIFT_W_DATA_t( void *pPst , char *encoding , char *buf , int *p_len );
_WINDLL_FUNC int DSCDESERIALIZE_JSON_UDC_TIMESHIFT_W_DATA_t( char *encoding , char *buf , int *p_len , void *pst );



//pages
typedef struct
{
	int	iMenuID ;
	int	iPageID ;
	int	iColumnID ;
	int	iPageNum ;
	int	iSrviceNum ;
	int	iAction ;
	char	aWorkSource[ 31 + 1 ] ;
	char	aPagesStartTime[ 31 + 1 ] ;
	char	aPagesEndTime[ 31 + 1 ] ;
	char	aMenuName[ 31 + 1 ] ;
	char	aColumnName[ 255 + 1 ] ;
	char	aParameter[ 255 + 1 ] ;
} UDC_PAGES_W_DATA_t ;

typedef struct __UDC_PAGES_DATA_t
{
    UDC_COMMON_DATA_t       stCData;
    UDC_PAGES_W_DATA_t          stWData;
}UDC_PAGES_DATA_t;
_WINDLL_FUNC int DSCINIT_UDC_PAGES_W_DATA_t( UDC_PAGES_W_DATA_t *pst );
_WINDLL_FUNC int DSCSERIALIZE_JSON_UDC_PAGES_W_DATA_t( void *pPst , char *encoding , char *buf , int *p_len );
_WINDLL_FUNC int DSCDESERIALIZE_JSON_UDC_PAGES_W_DATA_t( char *encoding , char *buf , int *p_len , void *pst );



//search
typedef struct
{
	char	aArea[ 63 + 1 ] ;
	char	aResult[ 63 + 1 ] ;
	char	aKeyword[ 255 + 1 ] ;
} UDC_SEARCH_W_DATA_t ;

typedef struct __UDC_SEARCH_DATA_t
{
    UDC_COMMON_DATA_t       stCData;
    UDC_SEARCH_W_DATA_t          stWData;
}UDC_SEARCH_DATA_t;
_WINDLL_FUNC int DSCINIT_UDC_SEARCH_W_DATA_t( UDC_SEARCH_W_DATA_t *pst );
_WINDLL_FUNC int DSCSERIALIZE_JSON_UDC_SEARCH_W_DATA_t( void *pPst , char *encoding , char *buf , int *p_len );
_WINDLL_FUNC int DSCDESERIALIZE_JSON_UDC_SEARCH_W_DATA_t( char *encoding , char *buf , int *p_len , void *pst );



//ca
typedef struct
{
	int	iStatus ;
	char	aCAStartTime[ 31 + 1 ] ;
	char	aCAExpireDate[ 31 + 1 ] ;
	char	aVersion[ 63 + 1 ] ;
	char	aProvisionCode[ 63 + 1 ] ;
	char	aProgramPack[ 63 + 1 ] ;
	char	aManufacturer[ 63 + 1 ] ;
} UDC_CA_W_DATA_t ;

typedef struct __UDC_CA_DATA_t
{
    UDC_COMMON_DATA_t       stCData;
    UDC_CA_W_DATA_t          stWData;
}UDC_CA_DATA_t;
_WINDLL_FUNC int DSCINIT_UDC_CA_W_DATA_t( UDC_CA_W_DATA_t *pst );
_WINDLL_FUNC int DSCSERIALIZE_JSON_UDC_CA_W_DATA_t( void *pPst , char *encoding , char *buf , int *p_len );
_WINDLL_FUNC int DSCDESERIALIZE_JSON_UDC_CA_W_DATA_t( char *encoding , char *buf , int *p_len , void *pst );



//pvr
typedef struct
{
	char	aWorkSource[ 63 + 1 ] ;
	int	iServiceID ;
	int	iTSID ;
	int	iFrequency ;
	char	aChanelName[ 31 + 1 ] ;
	char	aLogicChanelName[ 31 + 1 ] ;
	char	aPvrStarttime[ 31 + 1 ] ;
	char	aPvrEndtime[ 31 + 1 ] ;
} UDC_PVR_W_DATA_t ;

typedef struct __UDC_PVR_DATA_t
{
    UDC_COMMON_DATA_t       stCData;
    UDC_PVR_W_DATA_t          stWData;
}UDC_PVR_DATA_t;
_WINDLL_FUNC int DSCINIT_UDC_PVR_W_DATA_t( UDC_PVR_W_DATA_t *pst );
_WINDLL_FUNC int DSCSERIALIZE_JSON_UDC_PVR_W_DATA_t( void *pPst , char *encoding , char *buf , int *p_len );
_WINDLL_FUNC int DSCDESERIALIZE_JSON_UDC_PVR_W_DATA_t( char *encoding , char *buf , int *p_len , void *pst );


#ifdef __cplusplus //
}
#endif
#endif
    
