#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

//信号灯集用共用体
union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
							   (Linux-specific) */
};

int main(int argc, const char *argv[])
{
	// 1. 创建key 值
	key_t key = ftok("./app", 's');
	if(key == -1) {
		perror("ftok");
		return -1;
	}

	// 2. 创建 或 打开 信号灯集
	// 创建2个信号灯 
	int semid = semget(key, 2, IPC_CREAT|IPC_EXCL|0777);
	if(semid == -1) {
		if(errno == EEXIST) {
			// 打开信号灯 
			semid = semget(key, 0, 0777);
		} else {
			perror("semget");
			return -1;
		}
	}

	// 3.  初始化信号灯 
	union semun myun;
	myun.val = 0;
	semctl(semid, 0, SETVAL, myun);

	myun.val = 1;
	semctl(semid, 1, SETVAL, myun);

	// 创建 共享内存 
	// 1. 2. 3. 
	key_t key_shm;
	char poj_id = 'l';

	//key = ftok("./app", 'l');
	key_shm = ftok("./app", poj_id);

	// 2. 创建/打开共享内存对象.
	int shmid = -1;
	// 创建共享内存
	shmid = shmget(key_shm, 1000, IPC_CREAT|IPC_EXCL|0777);
	if(shmid == -1) {
		// 如果共享内存已经存在
		if(errno == EEXIST) {
			// 打开共享内存 
			shmid = shmget(key_shm, 0, 0777);
		} else {
			perror("shmget");
			return -1;
		}
	}
	
	// 3. 映射共享内存对象 到虚拟地址中	
	void *addr = NULL;
	addr = shmat(shmid, NULL, 0);
	if(addr ==  (void *)(-1))  {
		perror("shmat");
		return -1;
	}
	
	char *str = (char *)addr;
	// 向共享内存中 写入字符串 
	strcpy(str, "aaaaaaaaaabbbbbbbbbbb");

	pid_t pid = fork();
	if(pid == -1) {
		perror("fork");
		return -1;
	} else if(pid == 0) {
		// 子进程
		while(1) {
			// 1 号 信号灯 
			struct sembuf  mysembuf;
			mysembuf.sem_num = 1;
			mysembuf.sem_op = -1;   // P 操作
			mysembuf.sem_flg = 0;
			semop(semid, &mysembuf, 1);	

//			printf("A\n");
			// 打印共享 内存 
			printf("%s \n", str);
			sleep(2);

			
			mysembuf.sem_num = 0;
			mysembuf.sem_op = 1;    // V 操作
			mysembuf.sem_flg = 0;
			semop(semid, &mysembuf, 1);	
		}
	} else {
		// 父进程
		while(1) {
			struct sembuf  mysembuf;
			mysembuf.sem_num = 0;
			mysembuf.sem_op = -1;   // P 操作
			mysembuf.sem_flg = 0;
			semop(semid, &mysembuf, 1);	

//			printf("B\n");
			
			// 对共享内存中的数据 进行倒序  
			int len = strlen(str);
			int i = 0;
			for (i = 0; i < len/2; i++) {
				char tmp = str[i];
				str[i] = str[len-i-1];
				str[len-i-1] = tmp;
			}

			mysembuf.sem_num = 1;
			mysembuf.sem_op = 1;    // V 操作 
			mysembuf.sem_flg = 0;
			semop(semid, &mysembuf, 1);	
		}
	}



	//printf("%d \n", semctl(semid, 0, GETVAL));
	//printf("%d \n", semctl(semid, 1, GETVAL));


	// sleep(5);
	// 删除信号灯 	
	// semctl(semid, 0, IPC_RMID);


	return 0;
}


