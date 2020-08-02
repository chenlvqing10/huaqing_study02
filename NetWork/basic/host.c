#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

typedef struct stu1{
	int num;
	char sex;
}__attribute__((packed)) stu1_t;//告诉编译器取消结构在编译过程中的优化对齐,按照实际占用字节数进行对齐，是GCC特有的语法

typedef struct stu2{
	int num;
	char sex;
}stu2_t;


int main(int argc,char* argv[])
{
	uint32_t host_t=0x87654321;//主机字节序
	printf("host_t:%#X\n",host_t);

	uint32_t net_t=htonl(host_t);//网络字节序
	printf("net_t=%#X\n",net_t);

	printf("the size of struct stu1_t is %ld\n",sizeof(stu1_t));
	printf("the size of struct stu2_t is %ld\n",sizeof(stu2_t));

	//IP地址的转换 将十进制ip地址转换为二进制网络字节序
	//int inet_aton(const char*cp,struct in_addr *inp)  成功非0  失败0
	struct in_addr addr;
	int ret=inet_aton("192.168.75.148",&addr);
	if(ret==0)//非法的IP地址
	{
		printf("非法的IP地址\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("地址正确，成功返回\n");
		printf("address=%#X\n",addr.s_addr);//高位和低位相反   结果=0x944BA8C0  二进制:10010100(148)      01001011(75)      10101000(168)    11000000(192)
	}
	


	//函数in_addr_t inet_addr(const char *cp);  typedef uint32_t in_addr_t;将一个点分十进制的IP转换成一个长整数型数
	//返回值:如果正确执行将返回一个无符号长整数型数。如果传入的字符串不是一个合法的IP地址，将返回INADDR_NONE(0)
	//struct in_addr {
	//    in_addr_t s_addr;
	//};
	uint32_t ip1=inet_addr("192.168.75.148");
	if(ip1==0)
	{
		printf("inet_addr 非法的IP地址\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		 printf("inet_addr  地址正确，成功返回\n");
		printf("ip1=%#X\n",ip1);
	}
	


	//函数:char *inet_ntoa(struct in_addr in);
	//功能:将网络地址转换成“.”点隔的字符串格式
	//返回值是一个字符指针类型的点分法表示的IP地址
	//这个返回结果放到了静态存储区. 这个时候不需要我们⼿动进⾏释放,后面的调用会覆盖上一次的调用
	struct in_addr addr1,addr2;
	uint32_t  l1,l2;
	l1= inet_addr("192.168.0.74");//将点分IP转换成二进制网络字节序
	l2 = inet_addr("211.100.21.179");//将点分IP转换成二进制网络字节序
	memcpy(&addr1, &l1, 4);//从源内存地址的起始位置开始拷贝若干个字节到目标内存地址中  源:l1  目标:addr1
	memcpy(&addr2, &l2, 4);//源:l2   目标:addr2
	printf("第一次打印的结果:%s : %s\n", inet_ntoa(addr1), inet_ntoa(addr2)); //注意这一句的运行结果   先调用add2 在调用add1  再打印  结果是的add1覆盖了add2
	printf("第二次打印的结果:%s\n", inet_ntoa(addr1));   
	printf("第二次打印的结果:%s\n", inet_ntoa(addr2));   


	//ipv6 新型网络地址转换函数  ipv4也适用  AF_INET（ipv4）   AF_INET6（ipv6）
	//新型网路地址转化函数inet_pton和inet_ntop
	//int inet_pton(int family, const char *strptr, void *addrptr);     
	//将点分十进制的ip地址转化为用于网络传输的数值格式返回值：若成功则为1，若输入不是有效的表达式则为0，若出错则为-1
	//const char * inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
	//将数值格式转化为点分十进制的ip地址格式  返回值：若成功则为指向结构的指针，若出错则为NULL
	const char straddr[20]="192.168.0.58";
	struct in_addr addr6;
	int ret6 = inet_pton(AF_INET, straddr, (void *)&addr6); //第一个参数指定是适用IPV4还是适用IPV6地址
	if(ret6==0)
	{
		printf("IP地址非法\n");
		exit(EXIT_FAILURE);
	}
	else if(ret6==-1)
	{
		printf("出错\n");
		exit(EXIT_FAILURE);
	}
	else if(ret6==1)
	{
		printf("inet_pton ip to bin_net is  %#X\n",addr6.s_addr);
	}
	
	//反向转换
	char straddr1[20]={0};
	if((inet_ntop(AF_INET, (void *)&addr6,straddr1 , 16))==NULL)
	{
		printf("地址非法\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("inet_ntop bin_net to ip is  %s\n",straddr1);
	}









	return 0;
}
