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

/* File Name:   bbb.c  
   Author:      liuzhiming
   Created Time:8 Sep 2013
*/

#include "../include/bbb.h"

int main()
{
    int  ret = 0, i = 0;                            
    int  id = 0, id_res = 0;     
    int  cancel_ids[CANCELIDS_SIZE] = {0};                 
    RECORD *head = NULL, *tail = NULL;
    RECORD *p = NULL, *q = NULL, *tmp = NULL;
    pid_t pid_compile = 1, pid_get_res = 1;
    
    char code[CODESIZE+1];
    char code_type[CODE_TYPESIZE+1];
    char branch[BRANCHSIZE+1];
    char product[PRODUCTSIZE+1];
    char url[URLSIZE+1];
    char path[PATHSIZE+1];
    char output[OUTPUTSIZE+1];
    char usrname[USRNAMESIZE+1];
    int  compile_option = 0;
    MYSQL *conn = NULL;

    /*读配置文件*/
    parse_ini_file("src/bbb.ini");   
    /*openlog*/
    openlog("bbb-compile", LOG_CONS | LOG_PID, 0);
    /*成为精灵进程*/
    while (1)
    {
        if (daemon(0, 1) == 0)               //daemon(0, 0): '/','/dev/null',关掉终端输出,daemon(0,1)可开启控制端输出
            break;
        syslog(LOG_USER | LOG_INFO, "Daemon error"); 
        sleep(1);
    }
    /*忽略SIGCHLD 以避免僵尸进程*/
    signal(SIGCHLD, SIG_IGN);        
    /*初始化记录链表*/
    while(1)
    {
        head = (RECORD *)malloc(sizeof(RECORD));
        if (head != NULL)
            break;
        syslog(LOG_USER | LOG_INFO, "Failed to create Record head");
        sleep (1);    
    }
    head->next = NULL;
    tail = head;    
    /*连接MySQL*/
    mysql_library_init(0, NULL, NULL);
    conn = mysql_init(NULL);
    my_db_connect(conn, host, MySQL_usr, MySQL_passwd, database);
    /*把上次没执行完的任务重置为初始状态*/
    reset_status(conn);
        
    /*主循环*/
    while(1)
    {
        /*编译*/
        if (pnum < process_max)
            id = read_compile(conn, code, code_type, branch, product, path, output, usrname, &compile_option);
        else
            id = 0;         
        if (id)
        {
            pid_compile = my_fork();
            if (pid_compile == 0)
            {   
                setpgid(0, 0);                                          //成为新的进程组长
                signal(SIGCHLD, SIG_DFL);                               //子进程信号处理方式为默认
                compile_job(id, code, code_type, branch, product, path, output, usrname, compile_option);
            }
            else
            {
                tail = insert_compile_record(tail, id, pid_compile);    //增加一个链表节点
                pnum++;                                                 //正在编译进程数加1
            }
        }
        if(pid_compile == 0)
            break;

        /*取消编译*/
        if (read_cancel(conn, cancel_ids))
        {
            i = 0;
            while ((i < process_max) && cancel_ids[i])
            {
                p = head->next; 
                q = head;
                while (NULL != p)
                {
                    if (p->id == cancel_ids[i])
                        break;
                    p = p->next;
                    q = q->next;
                }
                /*取消编译*/
                cancel_compile(conn, cancel_ids[i], p->pid);
                /*删除节点*/
                q->next = p->next;
                if (p != NULL)
                {
                    free(p);
                    p = NULL;
                }
                if (q->next == NULL)              //如果删除了最后一个节点，把尾指针指向前一个节点
                    tail = q;
                pnum--;
                i++;
            }
            for (i=0; i < process_max; i++)
                cancel_ids[i] = 0;
        }

        /*取回编译结果*/
        if (strcmp(server_type, "master") == 0 && (id_res = read_get_result(conn, output, url)))     //只有主服务器取回编译结果
        {
            pid_get_res = my_fork();
            if (pid_get_res == 0)
            {
                signal(SIGCHLD, SIG_DFL);
                get_result(id_res, output, url);
            }
            else
            {}
        }
        if (pid_get_res == 0)
            break;

        /*对已经编译完成的记录删除节点*/
        p = head->next; 
        q = head;
        while (p != NULL)
        {
            ret = kill(p->pid, 0);              //判断进程是否存在，存在返回0，不存在返回-1
            if(ret == -1)
            {
                q->next = p->next;
                tmp = p;
                p = p->next;
                if (tmp)
                {
                    free(tmp);
                    tmp = NULL;
                }
                if (q->next == NULL)
                    tail = q;
                pnum--;                                
            }
            else
            {
                p = p->next;
                q = q->next;
            }
        }
        
        sleep(SLEEP_TIME);                     //休息SLEEP_TIME,进行下次查询
    }

    return 0;
}



