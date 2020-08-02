#include <stdio.h>  // 在系统指定目录下去找头文件
#include "add.h"  // 在当前目录下找头文件
#include "sub.h" // 当前目录下找不到，在系统指定目录下去找头文件
#include "mul.h"
#include "div.h"
int main(int argc, const char *argv[])
{
	printf("add:%d\n",add(10,5));
	printf("sub:%d\n",sub(10,5));
	printf("mul:%d\n",mul(10,5));
	printf("div:%d\n",div(10,5));
  	printf("num = %d\n",num);
	return 0;
}
