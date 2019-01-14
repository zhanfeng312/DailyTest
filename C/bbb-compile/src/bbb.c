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

/* File Name:   bbb_fun.c
   Author:      liuzhiming
   Created Time:9 Sep 2013
*/

#include "../include/bbb.h"

char *cvs_usr       = NULL;
char *cvs_passwd    = NULL;
char *svn_usr       = NULL;
char *svn_passwd    = NULL;
char *MySQL_usr     = NULL;
char *MySQL_passwd  = NULL;
char *database      = NULL;
char *tablename     = NULL;
char *host          = NULL;
char *os            = NULL;
char *compile_path  = NULL;
char *output_path   = NULL;
char *server_type   = NULL;
char *hostname      = NULL;
char *slaveIP       = NULL;
char *slaveDiretory = NULL;
int  process_max    = 0;        //缓存配置文件里的参数
int  pnum           = 0;        //进程总数

/************************************************************************/
/*Function 1:parse_ini_file   读bbb.ini配置文件                           */
/************************************************************************/
int parse_ini_file(char * ini_name)
{
    dictionary *ini;
    char *tmp;

    assert(ini_name);

    ini = iniparser_load(ini_name);
    if (ini==NULL)
    {
        fprintf(stderr, "cannot parse file: %s\n", ini_name);
        return -1;
    }

    tmp          = iniparser_getstring(ini, "Cvs:cvs_usr", NULL);
    cvs_usr      = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Cvs:cvs_passwd", NULL);
    cvs_passwd   = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Svn:svn_usr", NULL);
    svn_usr      = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Svn:svn_passwd", NULL);
    svn_passwd   = strdup(tmp);
    tmp          = iniparser_getstring(ini, "MySQL:MySQL_usr", NULL);
    MySQL_usr    = strdup(tmp);
    tmp          = iniparser_getstring(ini, "MySQL:MySQL_passwd", NULL);
    MySQL_passwd = strdup(tmp);
    tmp          = iniparser_getstring(ini, "MySQL:database", NULL);
    database     = strdup(tmp);
    tmp          = iniparser_getstring(ini, "MySQL:tablename", NULL);
    tablename    = strdup(tmp);
    tmp          = iniparser_getstring(ini, "MySQL:host", NULL);
    host         = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Os:os", NULL);
    os           = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Path:compile_path", NULL);
    compile_path = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Path:output_path", NULL);
    output_path  = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Server:server_type", NULL);
    server_type  = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Server:hostname", NULL);
    hostname     = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Server:slaveIP", NULL);
    slaveIP      = strdup(tmp);
    tmp          = iniparser_getstring(ini, "Server:slaveDiretory", NULL);
    slaveDiretory= strdup(tmp);
    process_max  = iniparser_getint(ini, "Process:process_max", -1);

    iniparser_freedict(ini);
    return 0;
}

/************************************************************************/
/*Function 2:grab             父进程抢占一条记录
                        对可编译对象修改 status,hostname                   */
/************************************************************************/
void grab(MYSQL *conn, int id_tmp)
{
    char str[BUFSIZE];

    assert(conn);
    assert(id_tmp);

    snprintf(str, sizeof(str), "update %s set status='running',hostname='%s' where id=%d", tablename, hostname, id_tmp);
    my_db_query(conn, str);
}

/************************************************************************/
/* Function 3:read_compile   读是否有可编译对象
                    有并抢占返回id  无返回0  每次只抢一条                    */
/************************************************************************/
int read_compile(MYSQL *conn, char *code, char *code_type, char *branch, char *product, char *path, char *output, char *usrname, int *compile_option)
{
    int id_tmp = 0;
    char str[BUFSIZE];
    MYSQL_RES *result;
    MYSQL_ROW  row;

    assert(conn);
    assert(code);
    assert(code_type);
    assert(branch);
    assert(product);
    assert(path);
    assert(output);
    assert(usrname);
    assert(compile_option);

    snprintf(str, sizeof(str),
        "select ID,code,code_type,branch,product,path,output,usrname,compile from %s where status='not_start' and os='%s' and cancel='hold' for update", tablename, os);
    /*开启事务*/
    my_db_query(conn, "START TRANSACTION");
    my_db_query(conn, str);

    result = mysql_store_result(conn);
    row    = mysql_fetch_row(result);               //只取第一行编译  把剩下的机会留给别人
    /*如果有可编译的对象*/
    if (row != NULL)
    {
        id_tmp = atoi(row[0]);
        grab(conn, id_tmp);                         //传id 对这行抢占
        /*提交事务*/
        my_db_query(conn, "COMMIT");

        /*把code,code_type,branch,product,path,output,usrname保存到数组中*/
        strncpy(code, row[1], CODESIZE);
        code[CODESIZE]='\0';
        strncpy(code_type, row[2], CODE_TYPESIZE);
        code_type[CODE_TYPESIZE] = '\0';
        strncpy(branch, row[3], BRANCHSIZE);
        branch[BRANCHSIZE] = '\0';
        strncpy(product, row[4], PRODUCTSIZE);
        product[PRODUCTSIZE] = '\0';
        strncpy(path, row[5], PATHSIZE);
        path[PATHSIZE] = '\0';
        strncpy(output, row[6], OUTPUTSIZE);
        output[OUTPUTSIZE] = '\0';
        strncpy(usrname, row[7], USRNAMESIZE);
        usrname[USRNAMESIZE] = '\0';
        *compile_option = atoi(row[8]);
    }
    else
        my_db_query(conn, "COMMIT");
    mysql_free_result(result);
    return id_tmp;
}

/************************************************************************/
/*Function 4:read_cancel    读是否有取消编译的对象
                          有返回1  无返回0  无需抢占                       */
/************************************************************************/
int read_cancel(MYSQL *conn, int *ids)
{
    char str[BUFSIZE];
    MYSQL_RES *result;
    MYSQL_ROW  row;

    assert(conn);
    assert(ids);

    snprintf(str, sizeof(str), "select id from %s where hostname='%s' and status='running' and cancel='cancel'", tablename, hostname);
    my_db_query(conn, str);

    result = mysql_store_result(conn);
    row    = mysql_fetch_row(result);
    if (NULL != row)
    {
        int i=1;
        ids[0] = atoi(row[0]);
        while ((row = mysql_fetch_row(result)))
            ids[i++] = atoi(row[0]);         //把需要取消编译的id都存下来
        mysql_free_result(result);
        return 1;
    }
    mysql_free_result(result);
    return 0;
}

/************************************************************************/
/*Function 5:read_get_result   判断是否有需要取回子服务器的编译结果
                                有返回id 无返回0 一次取回一条                */
/************************************************************************/
int read_get_result(MYSQL *conn, char *output, char *url)
{
    int id_tmp = 0;
    char str[BUFSIZE];
    MYSQL_RES *result;
    MYSQL_ROW  row;

    assert(conn);
    assert(output);
    assert(url);

    snprintf(str, sizeof(str), "select ID,output,url from %s where hostname<>'%s' and status='done' and get_res='no' and cancel='hold'", tablename, hostname);
    my_db_query(conn, str);

    result = mysql_store_result(conn);
    row    = mysql_fetch_row(result);
    if (NULL != row)
    {
        id_tmp = atoi(row[0]);
        strncpy(output, row[1], OUTPUTSIZE);
        output[OUTPUTSIZE] = '\0';
        strncpy(url, row[2], URLSIZE);
        url[URLSIZE] = '\0';
        /*修改状态为downloading*/
        snprintf(str, sizeof(str), "update %s set get_res='downloading' where id='%d'", tablename, id_tmp);
        my_db_query(conn,str);
    }
    mysql_free_result(result);
    return id_tmp;
}

/************************************************************************/
/*Function 6:update_get_res  父进程取回结果后写入get_res                   */
/************************************************************************/
void update_get_res(MYSQL *conn, int id_tmp, int flag)
{
    char str[BUFSIZE];
    assert(conn);
    assert(id_tmp);                 //flag：0 下载成功；flag：-1 下载失败

    if (flag == 0)
        snprintf(str, sizeof(str), "update %s set get_res='yes' where id='%d'", tablename, id_tmp);
    else
        snprintf(str, sizeof(str), "update %s set get_res='no' where id='%d'", tablename, id_tmp);
    my_db_query(conn, str);
}

/************************************************************************/
/*Function 7:update_status  子进程写入status                              */
/************************************************************************/
void update_status(MYSQL *conn, int id_tmp, char *output)
{
    char str[BUFSIZE];

    assert(conn);
    assert(id_tmp);
    assert(output);

    snprintf(str, sizeof(str), "update %s set status='done' where id='%d'", tablename, id_tmp);
    my_db_query(conn,str);

    if (strcmp(server_type, "slave") == 0)
    {
        char str[BUFSIZE*2],url[BUFSIZE];
        snprintf(url, sizeof(url), "%s/%s/", slaveIP,output+strlen(slaveDiretory)+1);   //根目录换成IP地址
        snprintf(str, sizeof(str), "update %s set url ='%s' where id=%d", tablename, url, id_tmp);
        my_db_query(conn,str);
    }
}

/************************************************************************/
/*Function 8:mkdir_mul         创建多级目录                               */
/************************************************************************/
void mkdir_mul(char *muldir)
{
    int i, len;
    char str[150];

    assert(muldir);

    strncpy(str, muldir, 150);
    len = strlen(str);
    for (i = 1; i < len; i++)                   //去掉开头的‘/’
    {
        if (str[i] == '/')
        {
            str[i] = '\0';
            /*判断此目录是否存在，不存在则创建*/
            if (access(str, F_OK) != 0)
            {
                mkdir(str, 0755);
            }
            str[i] = '/';
        }
    }
    /*创建最后一级*/
    if (len > 0 && access(str, F_OK) != 0)
    {
        mkdir(str, 0755);
    }
}

/************************************************************************/
/*Function 9:my_db_query        执行SQL语句
                            返回0：成功  非0：失败                         */
/************************************************************************/
int my_db_query(MYSQL *conn, const char *qry)
{
    int rc, tryed = 1;
    unsigned int errNUM;
    char *errStr;

    assert(conn);
    assert(qry);

    while (1)
    {
        rc = mysql_real_query(conn, qry, strlen(qry));
        if (rc == 0)
            break;
        if (tryed <= CONFIG_SYSLOG_RETRY_TIMES)
        {
            errStr = (char *)mysql_error(conn);
            errNUM = mysql_errno(conn);
            syslog(LOG_USER | LOG_INFO, "ERROR@_mysql_real_query_[TRY=%d]: Query=%s Errno=%d Error=%s", tryed, qry, errNUM, errStr);
            /*如果数据库连接中断，则重新连接*/
            if (errNUM == CR_SERVER_GONE_ERROR)
            {
                syslog(LOG_USER | LOG_INFO, "Retry connecting to DB...");
                my_db_connect(conn, host, MySQL_usr, MySQL_passwd, database);
            }
            tryed++;
        }
        sleep (1);
    }
    return rc;
}

/************************************************************************/
/*Function 10：my_db_connect       连接数据库
                              返回非空：成功 空：失败                       */
/************************************************************************/
MYSQL *my_db_connect(MYSQL *conn, char *host, char *MySQL_usr, char *MySQL_passwd, char *database)
{
    int tryed = 1;
    MYSQL *rc;
    char *errStr;
    unsigned int errNUM;

    assert(host);
    assert(MySQL_usr);
    assert(MySQL_passwd);
    assert(database);

    while (1)
    {
        rc = mysql_real_connect(conn, host, MySQL_usr, MySQL_passwd, database, 0, NULL, 0);
        if (NULL != rc)
            break;
        if (tryed <= CONFIG_SYSLOG_RETRY_TIMES)
        {
            errStr = (char *)mysql_error(conn);
            errNUM = mysql_errno(conn);
            syslog(LOG_USER | LOG_INFO, "ERROR@_mysql_real_connect[TRY=%d]: Errno=%d Error=%s\n", tryed, errNUM, errStr);
            tryed++;
        }
        sleep(1);
    }
    return rc;
}

/************************************************************************/
/*Function 11:compile_job         编译                                  */
/************************************************************************/
int compile_job(int id, char *code, char *code_type, char *branch, char *product, char *path, char *output, char *usrname, int compile_option)
{
    MYSQL *conn;
    pid_t pid;
    int status;
    DIR *dirp;
    struct dirent *direntp;
    char cvsroot[BUFSIZE];
    char buildstr[BUFSIZE];
    char usrnamestr[BUFSIZE];
    char FILESpath[OUTPUTSIZE];

    assert(id);
    assert(code);
    assert(code_type);
    assert(branch);
    assert(product);
    assert(path);
    assert(output);
    assert(usrname);
    assert(compile_option);

    /*生成输出目录*/
    if (strcmp(server_type, "slave") == 0)
    {
        char change_outpath[BUFSIZE];
        snprintf(change_outpath, sizeof(change_outpath), "%s/%s", output_path, output+strlen("/opt/ioa/"));
        memcpy(output, change_outpath, OUTPUTSIZE);
        output[OUTPUTSIZE] = '\0';
    }
    mkdir_mul(output);
    /*建立编译目录*/
    snprintf(buildstr, sizeof(buildstr), "%s/%s/%s/%s", compile_path, code_type, code, branch);
    mkdir_mul(buildstr);
    /*cvs*/
    if (strcmp(code_type, "cvs") == 0)
    {
        snprintf(usrnamestr, sizeof(usrnamestr), "%s/%s", buildstr, usrname);
        snprintf(cvsroot, sizeof(cvsroot), ":pserver:%s:%s@mcv.inspur.com:/opt/cvs", cvs_usr, cvs_passwd);
        pid = my_fork();
        /*检出代码*/
        if (pid == 0)
        {
            chdir(buildstr);
            if (strcmp(branch, "HEAD") == 0)
                execl("/usr/bin/cvs", "cvs", "-d", cvsroot, "co", "-P", "-d", usrname, code, (char *)0);
            else
                execl("/usr/bin/cvs", "cvs", "-d", cvsroot, "co", "-P", "-r", branch, "-d", usrname, code, (char *)0);
        }
        else
        {
            waitpid(pid, &status, 0);
            char logpath[OUTPUTSIZE];
            snprintf(logpath, sizeof(logpath), "%s/BUILD.LOG", output);
            chdir(usrnamestr);
            pid = my_fork();
            if (pid == 0)
            {
                /*执行build.sh*/
                freopen(logpath, "a", stdout);
                freopen(logpath, "a", stderr);
                execl("/bin/sh", "source", "build.sh", code, branch, product, output, (char *)0);
            }
            else
            {}
        }
    }
    /*svn*/
    else if (strcmp(code_type, "svn") == 0)
    {
        char productstr[BUFSIZE];
        snprintf(productstr, sizeof(productstr), "%s/%s", buildstr, product);
        mkdir_mul(productstr);
        snprintf(usrnamestr, sizeof(usrnamestr), "%s/%s", productstr, usrname);
        /*检出代码*/
        pid = my_fork();
        if (pid == 0)
        {
            chdir(productstr);
            execl("/usr/bin/svn", "svn", "co", path, "--username", svn_usr,"--password", svn_passwd, usrname, (char *)0);
        }
        else
        {
            waitpid(pid, &status, 0);
            char logpath[OUTPUTSIZE];
            snprintf(logpath, sizeof(logpath), "%s/BUILD.LOG", output);
            chdir(usrnamestr);
            pid = my_fork();
            if (pid == 0)
            {
                /*执行build.sh*/
                freopen(logpath, "a", stdout);
                freopen(logpath, "a", stderr);
           if (compile_option != 0)
                    {
                    char compile_str[4];
                    snprintf(compile_str, sizeof(compile_str), "%d", compile_option);
                    fprintf(stderr, "compile_option is %s\n", compile_str);
                execl("/bin/sh", "source", "build.sh", code, branch, product, output,compile_str, (char *)0);
                    }
            }
            else
                waitpid(pid, &status, 0);
        }
    }
    /*git*/
    else
    {
        char productstr[BUFSIZE];
        snprintf(productstr, sizeof(productstr), "%s/%s", buildstr, product);
        mkdir_mul(productstr);
        snprintf(usrnamestr, sizeof(usrnamestr), "%s/%s", productstr, usrname);
        /*检出代码*/
        pid = my_fork();
        if (pid == 0)
        {
            chdir(productstr);
            execl("/usr/bin/git", "git", "clone", path, usrname, (char *)0);
        }
        else
        {
            waitpid(pid, &status, 0);
            char logpath[OUTPUTSIZE];
            snprintf(logpath, sizeof(logpath), "%s/BUILD.LOG", output);
            chdir(usrnamestr);
            pid = my_fork();
            if (pid == 0)
            {
                /*执行build.sh*/
                freopen(logpath, "a", stdout);
                freopen(logpath, "a", stderr);
                if (compile_option != 0)
                {
                    char compile_str[4];
                    snprintf(compile_str, sizeof(compile_str), "%d", compile_option);
                    fprintf(stderr, "compile_option is %s\n", compile_str);
                    execl("/bin/sh", "source", "build.sh", compile_str, output, (char *)0);
                }
                else
                    execl("/bin/sh", "source", "build.sh", (char *)0);
            }
            else
                waitpid(pid, &status, 0);
        }
    }
    /*把编译生成的文件名写入到FILES中*/
    dirp = opendir(output);
    snprintf(FILESpath, sizeof(FILESpath), "%s/FILES", output);
    freopen(FILESpath, "w", stdout);
    while((direntp = readdir(dirp)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name , "..") != 0 && strcmp(direntp->d_name, "FILES") != 0)
            fprintf(stdout, "%s\n", direntp->d_name);
    }
    closedir(dirp);
    /*子进程重新连接数据库*/
    mysql_library_init(0, NULL, NULL);
    conn = mysql_init(NULL);
    my_db_connect(conn, host, MySQL_usr, MySQL_passwd, database);
    update_status(conn, id, output);
    mysql_close(conn);
    mysql_library_end();

    return 0;
}

/************************************************************************/
/*Function 12:get_result       取回编译结果                               */
/************************************************************************/
void get_result(int id_res, char *output, char *url)
{
    MYSQL *conn;
    pid_t pid;
    int status;

    assert(id_res);
    assert(output);
    assert(url);

    /*切换至输出目录下*/
    mkdir_mul(output);
    chdir(output);
    pid = my_fork();
    if (pid == 0)
    {
        char str[] = "FILES";
        strncat(url, str, strlen(str));
        /*先下载FILES文件， -c：断点续传，-t 0：无限重连 -T 120：120s为超时 --limit-rate=800K 限速800K/s GET_RESULT.LOG：log文件*/
        execl("/usr/bin/wget", "wget", "-c", "-t 0", "-T 120", "--limit-rate=800K", "-a GET_RESULT.LOG", url, (char *)0);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WEXITSTATUS(status) == 0)                    //下载成功，子进程返回0
        {
            FILE *fp = fopen ("FILES", "r");
            char buf[50];
            while (fgets(buf, 100, fp) != NULL)
            {
                pid = my_fork();
                if (pid == 0)
                {
                    strncat(url, buf, strlen(buf)-1);
                    /*根据FILES文件的内容下载相应文件*/
                    execl("/usr/bin/wget", "wget",  "-c", "-t 0", "-T 120", "--limit-rate=800K", "-a GET_RESULT.LOG", url, (char *)0);
                }
                else
                {
                    waitpid(pid, &status, 0);
                    if (WEXITSTATUS(status) != 0)
                        break;
                }
            }
            fclose (fp);
            mysql_library_init(0, NULL, NULL);
            conn = mysql_init(NULL);
            my_db_connect(conn, host, MySQL_usr, MySQL_passwd, database);
            if (WEXITSTATUS(status) == 0)
                /*下载成功，修改get_res=yes*/
                update_get_res(conn, id_res, 0);
            else
                /*下载失败，修改get_res=no*/
                update_get_res(conn, id_res, -1);
            mysql_close(conn);
            mysql_library_end();
        }
        else
        {
            /*下载失败，修改get_res=no*/
            mysql_library_init(0, NULL, NULL);
            conn = mysql_init(NULL);
            my_db_connect(conn, host, MySQL_usr, MySQL_passwd, database);
            update_get_res(conn, id_res, -1);
            mysql_close(conn);
            mysql_library_end();
        }
    }
}

/************************************************************************/
/*Function 13:insert_compile_record     在记录链表的尾部插入新的节点         */
/************************************************************************/
RECORD *insert_compile_record(RECORD *tail, int id, int pid)
{
    RECORD *pnew;

    assert(tail);
    assert(id);
    assert(pid);

    while(1)
    {
        pnew = (RECORD *)malloc(sizeof(RECORD));
        if (pnew != NULL)
            break;
        syslog(LOG_USER | LOG_INFO, "Failed to create Record point");
        sleep (1);
    }
    pnew->id = id;
    pnew->pid = pid;
    pnew->next = NULL;
    tail->next = pnew;
    tail = pnew;
    return tail;
}

/************************************************************************/
/*Function 14:cancel_compile       取消编译                              */
/************************************************************************/
int cancel_compile(MYSQL *conn, int id, int pid)
{
    char str[BUFSIZE];

    assert(conn);
    assert(id);
    assert(pid);

    if (kill(-pid, SIGKILL) != 0)           //对pid进程组的所有进程发终止信号
    {
        switch (errno)
        {
        case EPERM:
            syslog(LOG_USER | LOG_INFO, "You do not have right to access!Please use root! \n");
            break;
        case ESRCH:
            syslog(LOG_USER | LOG_INFO, "Process to kill not found!It is already done!\n");
            break;
        }
    }
    snprintf(str, sizeof(str), "update %s set status='done' where id=%d and status='running'", tablename, id);
    my_db_query(conn, str);
    return 0;
}

/************************************************************************/
/*Function 15:my_fork         创建子进程                                  */
/************************************************************************/
pid_t my_fork()
{
    pid_t pid;
    while (1)
    {
        pid = fork();
        if (pid >= 0)
            break;
        syslog(LOG_USER | LOG_INFO, "failed to fork when read compile \n");
        sleep (1);
    }
    return pid;
}

/************************************************************************/
/*Function 16:reset_status    恢复未编译完和未下载完的记录为初始状态           */
/************************************************************************/
void reset_status(MYSQL *conn)
{
    int id_tmp;
    char usrname_tmp[USRNAMESIZE+1];
    char str[BUFSIZE];
    MYSQL_RES *result;
    MYSQL_ROW  row;

    assert(conn);
    /*把未编完的running重置为初始状态*/
    snprintf(str, sizeof(str), "select ID,usrname from %s where status='running' and hostname='%s'", tablename, hostname);
    my_db_query(conn,str);
    result = mysql_store_result(conn);
    if (result)
    {
        while ((row = mysql_fetch_row(result)))
        {
            id_tmp = atoi(row[0]);
            strncpy(usrname_tmp, row[1], USRNAMESIZE);
            usrname_tmp[USRNAMESIZE] = '\0';
            /*建立新的编译目录*/
            strncat(usrname_tmp, ".1", strlen(".1"));
            snprintf(str, sizeof(str), "update %s set usrname='%s',hostname='',url='',status='not_start' where id='%d'", tablename, usrname_tmp, id_tmp);
            my_db_query(conn,str);
        }
    }
    mysql_free_result(result);
    /*把未下载完的downloading重置为初始状态*/
    if (strcmp(server_type, "master") == 0)
    {
        snprintf(str, sizeof(str), "update %s set get_res='no' where get_res='downloading'", tablename);
        my_db_query(conn,str);
    }
}
