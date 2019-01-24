/*
 * Copyright (C) Inspur Group Co., Ltd. Unpublished
 *
 * Inspur Group Co., Ltd.
 * Proprietary & Confidential
 *
 * This source code and the algorithms implemented therein constitute
 * confidential information and may comprise trade secrets of Inspur
 * or its associates, and any use thereof is subject to the terms and
 * conditions of the Non-Disclosure Agreement pursuant to which this
 * source code was originally received.
 */ 


#ifndef __NT_COMMOM_H_
#define __NT_COMMOM_H_

//config before include _nt_common.h
//example:
//#define NT_LOG_OUTPUT_DISABLE
//#define NT_LOG_LOGCAT_DISABLE
//#define NT_LOG_OUTPUT_LVL 5
//#define NT_LOG_TAG	"nt_xxx"
//#define NT_ASSERT_DISABLE

/*#define NT_ASSERT_HOOK(EXPR)                             \
                    do {                                    \
                        udc_log("(%s) has assert failed !\n", #EXPR);    \
                        while (1);                                      \
                    }while(0)*/



#ifndef NT_LOG_TAG
#define NT_LOG_TAG          "nt_xxx"
#endif

#ifndef NT_LOG_OUTPUT_LVL
#define NT_LOG_OUTPUT_LVL 5
#endif

/* output log's level */
#define NT_LOG_LVL_ASSERT                      0
#define NT_LOG_LVL_ERROR                       1
#define NT_LOG_LVL_WARN                        2
#define NT_LOG_LVL_INFO                        3
#define NT_LOG_LVL_DEBUG                       4
#define NT_LOG_LVL_VERBOSE                     5



#ifdef __ANDROID__
	#ifndef NT_LOG_LOGCAT_DISABLE
		#define NT_LOG_LOGCAT_ENABLE
		#include <android/log.h>
	#endif
#endif // __ANDROID__


#ifdef NT_LOG_OUTPUT_DISABLE
    #define nt_log_assert(tag, xfmt, ...)
    #define nt_log_error(tag, xfmt, ...)
    #define nt_log_warn(tag, xfmt, ...)
    #define nt_log_info(tag, xfmt, ...)
    #define nt_log_debug(tag, xfmt, ...)
    #define nt_log_verbose(tag, xfmt, ...)
    #define nt_log_raw(tag, xfmt, ...)
#else /* NT_LOG_OUTPUT_ENABLE */

	#ifdef NT_LOG_LOGCAT_ENABLE
	       #define nt_log_raw(tag, xfmt, ...) \
                    do {\
                        __android_log_print(ANDROID_LOG_FATAL, tag, xfmt, ##__VA_ARGS__);\
                    } while (0)

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_ASSERT
			#define nt_log_assert(tag, xfmt, ...) \
				do {\
				__android_log_print(ANDROID_LOG_FATAL, tag,"[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
				} while (0)
		#else
			#define nt_log_assert(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_ASSERT */

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_ERROR
			#define nt_log_error(tag, xfmt, ...) \
				do {\
				__android_log_print(ANDROID_LOG_ERROR, tag,"[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
				} while (0)
		#else
			#define nt_log_error(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_ERROR */

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_WARN
			#define nt_log_warn(tag, xfmt, ...) \
				do {\
				__android_log_print(ANDROID_LOG_WARN, tag,"[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
				} while (0)
		#else
			#define nt_log_warn(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_WARN */

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_INFO
			#define nt_log_info(tag, xfmt, ...) \
				do {\
				__android_log_print(ANDROID_LOG_INFO, tag,"[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
				} while (0)
		#else
			#define nt_log_info(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_INFO */

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_DEBUG
			#define nt_log_debug(tag, xfmt, ...) \
				do {\
				__android_log_print(ANDROID_LOG_DEBUG, tag,"[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
				} while (0)
		#else
			#define nt_log_debug(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_DEBUG */

		#if NT_LOG_OUTPUT_LVL == NT_LOG_LVL_VERBOSE
			#define nt_log_verbose(tag, xfmt, ...) \
				do {\
				__android_log_print(ANDROID_LOG_VERBOSE, tag,"[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
				} while (0)
		#else
			#define nt_log_verbose(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL == NT_LOG_LVL_VERBOSE */

	#else
	        #define nt_log_raw(tag, xfmt, ...) \
                    do {\
                        fprintf(stderr, tag " " xfmt, ##__VA_ARGS__);\
                    } while (0)

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_ASSERT
			#define nt_log_assert(tag, xfmt, ...) \
					do {\
					printf("F/" tag "[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
					} while (0)
		#else
			#define nt_log_assert(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_ASSERT */

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_ERROR
			#define nt_log_error(tag, xfmt, ...) \
					do {\
					printf("E/" tag "[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
					} while (0)
		#else
			#define nt_log_error(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_ERROR */

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_WARN
			#define nt_log_warn(tag, xfmt, ...) \
					do {\
					printf("W/" tag "[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
					} while (0)
		#else
			#define nt_log_warn(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_WARN */

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_INFO
			#define nt_log_info(tag, xfmt, ...) \
					do {\
					printf("I/" tag "[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
					} while (0)
		#else
			#define nt_log_info(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_INFO */

		#if NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_DEBUG
			#define nt_log_debug(tag, xfmt, ...) \
					do {\
					printf("D/" tag "[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
					} while (0)
		#else
			#define nt_log_debug(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL >= NT_LOG_LVL_DEBUG */

		#if NT_LOG_OUTPUT_LVL == NT_LOG_LVL_VERBOSE
			#define nt_log_verbose(tag, xfmt, ...) \
					do {\
					printf("V/" tag "[%s %d]:" xfmt, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
					} while (0)
		#else
			#define nt_log_verbose(tag, xfmt, ...)
		#endif /* NT_LOG_OUTPUT_LVL == NT_LOG_LVL_VERBOSE */

	#endif

#endif /* NT_LOG_OUTPUT_ENABLE */




#define nlog_a(...)     nt_log_assert(NT_LOG_TAG, __VA_ARGS__)
#define nlog_e(...)     nt_log_error(NT_LOG_TAG, __VA_ARGS__)
#define nlog_w(...)     nt_log_warn(NT_LOG_TAG, __VA_ARGS__)
#define nlog_i(...)     nt_log_info(NT_LOG_TAG, __VA_ARGS__)
#define nlog_d(...)     nt_log_debug(NT_LOG_TAG, __VA_ARGS__)
#define nlog_v(...)     nt_log_verbose(NT_LOG_TAG, __VA_ARGS__)


/* assert for developer */
#ifdef NT_ASSERT_DISABLE
    #define NT_ASSERT(EXPR)                    ((void)0);
#else
#ifdef NT_ASSERT_HOOK
    #define NT_ASSERT(EXPR)                             \
        if (!(EXPR))                                        \
        {                                                   \
            nlog_a("(%s) has assert failed !\n", #EXPR); \
            NT_ASSERT_HOOK(EXPR); \
        }
#else
    #define NT_ASSERT(EXPR)                             \
        if (!(EXPR))                                        \
        {                                                   \
            nlog_a("(%s) has assert failed !\n", #EXPR); \
            while(1); \
        }
#endif /* NT_ASSERT_HOOK */
#endif /* NT_ASSERT_DISABLE */


#define NT_ASSERT_PTR(ptr)	NT_ASSERT(NULL != ptr)
#define NT_ASSERT_STR(str)	NT_ASSERT(NULL != str && *(str))



#if defined(_WIN32)
	#include <Winsock2.h>
	#define nt_sleep_ms(x) Sleep(x)
#else
	#include <unistd.h>
	#define nt_sleep_ms(x) usleep((x) * 1000)
#endif

#include <stdio.h>
#define NT_STRCPY_S(x, y) snprintf(x, sizeof(x), "%s", y)
#define NT_STRCPY_D(x, y) snprintf(x, sizeof(x), "%d", y)
#define NT_ARRAY_COUNT(x) (sizeof(x) / sizeof((x)[0]))

#define NT_UNUSED(arg)	do { (arg) = (arg); } while (0)



/** A compile time assertion check. 
 * 
 *  Validate at compile time that the predicate is true without
 *  generating code. This can be used at any point in a source file 
 *  where typedef is legal. 
 * 
 *  On success, compilation proceeds normally. 
 * 
 *  On failure, attempts to typedef an array type of negative size. The 
 *  offending line will look like 
 *      typedef assertion_failed_file_h_42[-1] 
 *  where file is the content of the second parameter which should 
 *  typically be related in some obvious way to the containing file 
 *  name, 42 is the line number in the file on which the assertion 
 *  appears, and -1 is the result of a calculation based on the 
 *  predicate failing. 
 * 
 *  \param predicate The predicate to test. It must evaluate to 
 *  something that can be coerced to a normal C boolean. 
 * 
 *  \param file A sequence of legal identifier characters that should 
 *  uniquely identify the source file in which this condition appears. 
 */

#define NT_CASSERT(predicate, file) _impl_CASSERT_LINE(predicate,__LINE__,file)

#define _impl_PASTE(a,b) a##b
#define _impl_CASSERT_LINE(predicate, line, file) \
typedef char _impl_PASTE(assertion_failed_##file##_,line)[2*!!(predicate)-1];


#endif//__NT_COMMOM_H_