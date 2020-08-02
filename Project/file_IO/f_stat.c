#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/*use the stat function*/
int main(int argc, const char *argv[])
{
	//struct stat
	struct stat filestat;
	const char *filename="./fstat.txt";

	//get the file stat
	if((stat(filename,&filestat))<0)
	{
		perror("get file stat");
		exit(1);
	}
	else
		perror("get file stat");

	//获取文件的节点
	int st_ino=filestat.st_ino;
	printf("文件的节点编号:%d\n",st_ino);
	//获取设备编号，设备类型
	int dev_st=filestat.st_dev;
	int rdev_st=filestat.st_rdev;
	printf("主设备编号:%d  次设备编号:%d\n",dev_st,rdev_st);
	//获取文件权限
	char perm[10];
	if(S_ISSOCK(filestat.st_mode))
		perm[0]='s';
	else if(S_ISLNK(filestat.st_mode))
		perm[0]='l';
	else if(S_ISREG(filestat.st_mode))
		perm[0]='-';
	else if(S_ISBLK(filestat.st_mode))
		perm[0]='b';
	else if(S_ISDIR(filestat.st_mode))
		perm[0]='d';
	else if(S_ISCHR(filestat.st_mode))
		perm[0]='c';
	else if(S_ISFIFO(filestat.st_mode))
		perm[0]='p';
	else
		perm[0]='?';

	if (filestat.st_mode & S_IRUSR)
		perm[1] = 'r';
	else
		perm[1] = '-';

	if (filestat.st_mode & S_IWUSR)
		perm[2] = 'w';
	else
		perm[2] = '-';

	if (filestat.st_mode & S_IXUSR)
		perm[3] = 'x';
	else
		perm[3] = '-';

	if (filestat.st_mode & S_IRGRP)
		perm[4] = 'r';
	else
		perm[4] = '-';

	if (filestat.st_mode & S_IWGRP)
		perm[5] = 'w';
	else
		perm[5] = '-';

	if (filestat.st_mode & S_IXGRP)
		perm[6] = 'x';
	else
		perm[6] = '-';

	if (filestat.st_mode & S_IROTH)
		perm[7] = 'r';
	else
		perm[7] = '-';

	if (filestat.st_mode & S_IWOTH)
		perm[8] = 'w';
	else
		perm[8] = '-';

	if (filestat.st_mode & S_IXOTH)
		perm[9] = 'x';
	else
		perm[9]= '-';
	
    printf("文件权限：");
	for(int i=0;i<10;i++)
		printf("%c",perm[i]);
	printf("\n");
	
	//printf("文件权限:%s\n",perm);

	//获取文件链接数
	int number_link=filestat.st_nlink;
	printf("文件连接数:%d\n",number_link);

	//获取用户ID
	struct passwd *user;
	user=getpwuid(filestat.st_uid);
	printf("UserName:%s\n", user->pw_name);

	//获取文件所属组
	struct group *gp;
	gp=getgrgid(filestat.st_gid);
	printf("GroupName:%s\n",gp->gr_name);

	//获取文件字节数
	int size_st=filestat.st_size;
	printf("文件字节数:%d\n",size_st);

	//获取时间 最后一次修改时间
	time_t mtime = filestat.st_mtime;
	struct tm *pTime = localtime(&mtime);
    printf("%d月  %d  %d:%d\n",pTime->tm_mon+1,pTime->tm_mday,pTime->tm_hour,pTime->tm_min);
	
	//获取文件名
	 char name[1024] = {0};
	 if(readlink("./fstat.txt",name,sizeof(name))<0)
	 {
		perror("readlink");
		exit(EXIT_FAILURE);
	 }
	 printf("文件名：%s\n",name);
	 


	return 0;
}
