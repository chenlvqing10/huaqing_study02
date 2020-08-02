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
#include <dirent.h>

//获取文件权限
void getfilepoem(mode_t st_mode,char *perm)
{
	if(S_ISSOCK(st_mode))
		perm[0]='s';
	else if(S_ISLNK(st_mode))
		perm[0]='l';
	else if(S_ISREG(st_mode))
		perm[0]='-';
	else if(S_ISBLK(st_mode))
		perm[0]='b';
	else if(S_ISDIR(st_mode))
		perm[0]='d';
	else if(S_ISCHR(st_mode))
		perm[0]='c';
	else if(S_ISFIFO(st_mode))
		perm[0]='p';
	else
		perm[0]='?';

	if (st_mode & S_IRUSR)
		perm[1] = 'r';
	else
		perm[1] = '-';

	if (st_mode & S_IWUSR)
		perm[2] = 'w';
	else
		perm[2] = '-';

	if (st_mode & S_IXUSR)
		perm[3] = 'x';
	else
		perm[3] = '-';

	if (st_mode & S_IRGRP)
		perm[4] = 'r';
	else
		perm[4] = '-';

	if (st_mode & S_IWGRP)
		perm[5] = 'w';
	else
		perm[5] = '-';

	if (st_mode & S_IXGRP)
		perm[6] = 'x';
	else
		perm[6] = '-';

	if (st_mode & S_IROTH)
		perm[7] = 'r';
	else
		perm[7] = '-';
	if (st_mode & S_IWOTH)
		perm[8] = 'w';
	else
		perm[8] = '-';

	if (st_mode & S_IXOTH)
		perm[9] = 'x';
	else
		perm[9]= '-';

}

int size_total(const char *dir_path)
{  
	int total=0;
	struct stat filestat;
	DIR *dirp=NULL;//OpenDir
	struct dirent *dir_entry=NULL;
	//open dir
	if((dirp=opendir(dir_path))==NULL)
	{
		perror("opendir");
		exit(1);
	}
	else
		perror("opendir");

	//read dir
	while((dir_entry=readdir(dirp))!=NULL)
	{
	//	perror("readdir");
		//get the file or dir stat
		if((stat(dir_entry->d_name,&filestat))<0)
		{
			perror("get file stat");
			exit(1);
		}
		//else
			//perror("get file stat");

		//获取文件字节数
		int size_st=filestat.st_size;
		long nBlocks = size_st / 4096;//得到整数个块数 1块=4K=1024*4=4096
		if (size_st % 4096 > 0)
			nBlocks++;       //整数个块数+1(不足4K的也要占用一个块)
		if (S_ISLNK(filestat.st_mode))
			nBlocks = 0;          //不计算符号链接的文件
		total+=nBlocks;
	//	printf("total:%d\n",total);
	}

	closedir(dirp);

	return total*4;//total的单位是K=块数×4
}
int main(int argc, const char *argv[])
{
	struct dirent **namelist;
	const char *dir_path="./";
	int n;
	struct stat filestat;
	int total=size_total(dir_path);//get total bytes

	n=scandir(dir_path,&namelist,0,alphasort);
//	printf("n=%d\n",n);

	if(n<0)
	{
		perror("scan dir");
		exit(1);
	}
	else
	{
		perror("scan dir");
		int index=0;
		printf("total=%d\n",total);
		while(index<n)
		{
			//printf("d_name=%s\n",namelist[index]->d_name);

			//get the file or dir stat
			if((stat(namelist[index]->d_name,&filestat))<0)
			{   
				perror("get file stat");
				exit(1);
			}
			//else
			//	perror("get file stat");

			//得到文件的权限
			char perm[10];
			getfilepoem(filestat.st_mode,perm);
			//printf("文件权限:%s\n",perm);
			printf("%s  ",perm);

			//获取文件链接数
			int number_lin=filestat.st_nlink;
			//printf("文件连接数:%d\n",filestat.st_nlink);
			printf("%d  ",number_lin);

			//获取用户ID
			struct passwd *user;
			user=getpwuid(filestat.st_uid);
			//printf("UserName:%s\n", user->pw_name);
			printf("%s  ", user->pw_name);

			//获取文件所属组
			struct group *gp;
			gp=getgrgid(filestat.st_gid);
			//printf("GroupName:%s\n",gp->gr_name);
			printf("%s  ",gp->gr_name);

			//获取文件字节数
			int size_st=filestat.st_size;
			//printf("文件字节数:%d\n",filestat.st_size);
			printf("%10d  ",size_st);

			//获取时间 最后一次修改时间
			time_t mtime = filestat.st_mtime;
			struct tm *pTime = localtime(&mtime);
			//printf("%d月  %d  %d:%d\n",pTime->tm_mon+1,pTime->tm_mday,pTime->tm_hour,pTime->tm_min);
			printf("%d月  %2d  %2d:%02d  ",pTime->tm_mon+1,pTime->tm_mday,pTime->tm_hour,pTime->tm_min);

			//打印文件名
			printf("%s\n",namelist[index]->d_name);

			free(namelist[index]);
			index++;
		}
		free(namelist);
	}

	return 0;
}
