#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/bank.h"
#include "../inc/network.h"

static const char* g_svrip = NULL;

void menu_loop (int (*menu) (void), int (*on_menu[]) (void), size_t size) {
    for (;;) {
        int id = menu ();
        if (id < 0 || size <= id)
            printf ("Invalid selection !\n");
        else if (on_menu[id] () == -1)
            break;
    }
}
int main_menu (void) {
    printf ("--------\n");
    printf ("网络银行\n");
    printf ("--------\n");
    printf ("[1] 开户\n");
    printf ("[2] 存款\n");
    printf ("[3] 取款\n");
    printf ("[4] 查询\n");
    printf ("[5] 转账\n");
    printf ("[0] 退出\n");
    printf ("--------\n");
    printf ("请选择：");
    int id = -1;
    scanf ("%d", &id);
    //清空缓冲区
    scanf ("%*[^\n]");
    scanf ("%*c");

    return id;
}
int on_quit (void) {
    printf ("谢谢使用，再见！\n");
    return -1;
}
int on_open (void) {
	OPEN_REQUEST req;

	printf ("户名：");
	scanf ("%s", req.name);
	printf ("密码：");
	scanf ("%s", req.passwd);
	printf ("金额：");
	scanf ("%lf", &req.balance);
        //建立套结字,连接,并发送,返回建立的套结字
	int sockfd = sndreq (g_svrip, TYPE_OPEN, &req, sizeof (req));
	if (sockfd == -1)
            return 0;

	OPEN_RESPOND res;
        //接受开户响应
	if (rcvres (sockfd, &res, sizeof (res)) == -1)
		return 0;
	if (strlen (res.error)) {
		printf ("%s\n", res.error);
		return 0;
	}
	printf ("账号：%d\n", res.id);
	return 0;
}
/*
int on_close(void)
{
    CLOSE_REQUEST req;

    printf("帐号: ");
    scanf ("%d", &req.id);
    printf("户名: ");
    scanf ("%s", req.name);
    printf("密码: ");
    scanf("%s", req.passwd);

    int sockfd = sndreq(g_svrip, TYPE_CLOSE, &req, sizeof (req));
    if (sockfd == -1)
        return 0;
    CLOSE_RESPOND res;
    if (rcvreq(sockfd, &res, sizeof (res)) == -1)
        return 0;
    printf("该账户已被注销!");
    return 0;
}
*/
int on_save (void){
    SAVE_REQUEST req;

    printf("帐号: ");
    scanf ("%d", &req.id);
    printf("户名: ");
    scanf ("%s", req.name);
    printf("要存入的钱: ");
    scanf ("%lf", &req.money);

    int sockfd = sndreq(g_svrip, TYPE_SAVE, &req, sizeof (req));
    if (sockfd == -1)
        return 0;
    SAVE_RESPOND res;
    if (rcvres (sockfd, &res, sizeof (res)) == -1)
        return 0;
    printf("账户余额:%g\n", res.balance);
    return 0;
}
int on_qu (void)
{
    WITHDRAW_REQUEST req;
    printf("帐号: ");
    scanf("%d", &req.id);
    printf("账户名: ");
    scanf("%s", req.name);
    printf("密码: ");
    scanf("%s", req.passwd);
    printf("你要取的钱数: ");
    scanf("%lf", &req.money);

    int sockfd = sndreq(g_svrip, TYPE_WITHDRAW, &req, sizeof (req));
    if (sockfd == -1)
        return 0;
    WITHDRAW_RESPOND res;
    if (rcvres(sockfd, &res, sizeof (res)) == -1)
        return -1;
    printf("该账户剩余的钱数为:%g\n", res.balance);
    return 0;
}
int on_query (void)
{
    QUERY_REQUEST req;
    printf("帐号: ");
    scanf("%d", &req.id);
    printf("账户名: ");
    scanf("%s", req.name);
    printf("密码: ");
    scanf("%s", req.passwd);

    int sockfd = sndreq(g_svrip, TYPE_QUERY, &req, sizeof (req));
    if (sockfd == -1)
        return -1;
    QUERY_RESPOND res;
    if (rcvres (sockfd, &res, sizeof (res)) == -1)
        return 0;
    printf("该账户余额为:%g\n", res.balance);
    return 0;
}
int on_transfer(void)
{
    TRANSFER_REQUEST req;
    printf("你的帐号: ");
    scanf ("%d", &req.id[0]);
    printf("你的户名: ");
    scanf ("%s", req.name[0]);
    printf("你的密码: ");
    scanf("%s", req.passwd);
    printf("你要转的钱数: ");
    scanf("%lf", &req.money);
    printf("对方帐号: ");
    scanf ("%d", &req.id[1]);
    printf("对方户名: ");
    scanf("%s", req.name[1]);


    int sockfd = sndreq(g_svrip, TYPE_TRANSFER, &req, sizeof (req));
    if (sockfd == -1)
        return 0;
    TRANSFER_RESPOND res;
    if (rcvres(sockfd, &res, sizeof (res)) == -1){
        printf("转帐失败!\n");
        return -1;
    }
    printf("转帐成功!\n");
    return 0;
}
int main (int argc, char* argv[]) {
    if (argc < 2) {
        fprintf (stderr, "用法：%s <服务器IP地址>\n", argv[0]);
        return -1;
    }
    g_svrip = argv[1];
    int (*on_menu[]) (void) = {on_quit, on_open,
        on_save, on_qu, on_query, on_transfer};
    //给函数指针数组赋值
    menu_loop (main_menu, on_menu,
            sizeof (on_menu) / sizeof (on_menu[0]));
    //调用这个函数
    return 0;
}
