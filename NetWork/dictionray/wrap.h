#ifndef __WRAP__
#define __WRAP__

#include <stdio.h>          
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>
#include <ctype.h>

#define  QUIT			"quit"
#define  SERVER_PORT     1259
#define  SERVER_IP		"192.168.60.153"
#define  CLIENT_IP		"192.168.60.153"
#define  CLIENT_PORT	6667
#define  CLIENT_PORT1	6668
#define  CLIENT_PORT2	6669
#define  CLIENT_PORT3	6670
#define  TYPE_SERVER	1
#define  TYPE_CLIENT	2
#define   ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0])) //结构体数组的大小 
#define  EXPLAIN_SIZE	500
#define  WORD_SIZE		50


/*函数的声明*/
void pipesig_handler(int signo);
void get_sigsegv(int signo);

int tcp4bind(int type,int clnt_port,struct sockaddr_in serv_addr,struct sockaddr_in clnt_addr);//绑定IP和PORT
int acceptclient(int serv_sock,struct sockaddr_in clnt_addr,socklen_t clnt_addr_size);

char* getexplain(const char* pathname,char* buffer);//从文件中读取客户单输入单词的解释信息,如果单词不存在，则发送不匹配信息

void* Read(int fd, void *ptr, size_t nbytes);//读取数据到缓冲区
ssize_t  Write(int fd, void *ptr, size_t nbytes);//将缓冲区数据写入套接字

#endif
