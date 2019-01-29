/*
 * Copyright (c) Inspur Group Co., Ltd. Unpublished
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

/*  This is a headfile:bbb_fun.h for bbb.c,which contains functions*/
/*  8Sep2013  liuzhiming   writren   */
#ifndef _BBB_H_
#define _BBB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <time.h>
#include <assert.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <mysql.h>
#include <errmsg.h>
#include "iniparser.h"

#define BUFSIZE         200     			//存放SQL语句的字符串数组的大小
#define CANCELIDS_SIZE  20      			//存放取消编译的进程号的数组大小  可与最大进程数一致  默认20

//以下为数据库中定义的字段大小
#define CODESIZE        50                  //code
#define CODE_TYPESIZE   3                   //code_type 
#define BRANCHSIZE      50                  //branch
#define PRODUCTSIZE     50                  //product
#define URLSIZE         200                 //url
#define PATHSIZE        200                 //path
#define OUTPUTSIZE		200                 //output
#define USRNAMESIZE		80					//usrname

#define SLEEP_TIME      10                  //睡眠时间（秒） 
#define CONFIG_SYSLOG_RETRY_TIMES   20   	//syslog写入条数，大于此数时，连接错误将不再写入log

typedef struct compile_record
{
    int id;
    int pid;
    struct compile_record *next;
}RECORD;

#define free(p)  do {                                                   \
        printf("%s:%d:%s:free(0x%lx)\n", __FILE__, __LINE__,            \
            __func__, (unsigned long)p);                                \
        free(p);                                                        \
    } while (0)

extern char *cvs_usr;
extern char *cvs_passwd;

extern char *svn_usr;
extern char *svn_passwd;

extern char *MySQL_usr;
extern char *MySQL_passwd;
extern char *database;
extern char *tablename;
extern char *host;

extern char *os;
extern char *compile_path;
extern char *output_path;

extern char *server_type;
extern char *hostname;
extern char *slaveIP;
extern char *slaveDiretory;

extern int  process_max;        			//以上为配置文件里的参数
extern int  pnum;							//进程总数

extern int parse_ini_file(char * ini_name);
extern void grab(MYSQL *conn, int id_tmp);
extern int read_compile(MYSQL *conn, char *code, char *code_type, char *branch,char *product, char *path, char *output, char *usrname, int *compile_option);
extern int read_cancel(MYSQL *conn, int *pids);
extern int read_get_result(MYSQL *conn, char *output, char *url);
extern void update_get_res(MYSQL *conn, int id_tmp, int flag);
extern void update_status(MYSQL *conn, int id_tmp, char *output);
extern void mkdir_mul(char *muldir);
extern int my_db_query(MYSQL *conn, const char *qry);
extern MYSQL *my_db_connect(MYSQL *conn, char *host, char *MySQL_usr, char *MySQL_passwd,char *database);
extern int compile_job(int id, char *code, char *code_type, char *branch, char *product, char *path, char *output, char *usrname, int compile_option);
extern void get_result(int id_res, char *output, char *url);
extern RECORD *insert_compile_record(RECORD *tail, int id, int pid);
extern int cancel_compile(MYSQL *conn, int id, int pid);
extern pid_t my_fork();
extern void reset_status(MYSQL *conn);
#endif
