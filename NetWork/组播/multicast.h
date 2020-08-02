#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <netinet/in.h>
//设置多播组
#define  MGROUP  "224.2.3.4"

//设置端口号
#define RCVPORT  "6667"
#define PORT  1237
#define NAMESIZE 13


struct msg_st{
	char name[13];
	uint32_t math;
	uint32_t chinese;
}__attribute__((packed));;

