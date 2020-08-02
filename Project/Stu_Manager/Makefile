
CC=gcc#编译器 g++也可以
CFLAGS1=-shared -fPIC -o#编译共享库的编译选项
CFLAGS2=-L. -lusermanager -luserregist -ladminmanager -lcollegemanager -lgettableno -lstumanager -lmysqlclient#最终生成的可执行文件时的编译选项


OBJ1=libusermanager.so#依赖文件1---共享库
OBJ2=libuserregist.so#依赖文件2---共享库
OBJ3=libadminmanager.so#依赖文件3---共享库
OBJ4=libcollegemanager.so#依赖文件3---共享库
OBJ5=libgettableno.so#依赖文件3---共享库
OBJ6=libstumanager.so#依赖文件3---共享库

OBJS1=user_manager.c
OBJS2=user_regist.c
OBJS3=admin_manager.c
OBJS4=college_manager.c
OBJS5=get_tableno.c
OBJS6=stu_manager.c

OBJS+=libusermanager.so
OBJS+=libuserregist.so
OBJS+=libadminmanager.so
OBJS+=libcollegemanager.so
OBJS+=libgettableno.so
OBJS+=libstumanager.so

TARGET ?= stu_main#最终编译的目标文件
OBJT=stu_main.c
	
all:$(OBJS)
	sudo cp ./*.so /usr/lib/
	$(CC) -o $(TARGET) $(OBJT) $(CFLAGS2)
#	./$(TARGET)
#生成共享库
$(OBJ1):$(OBJS1)
		$(CC) $(CFLAGS1) $@ $^

$(OBJ2):$(OBJS2)
		$(CC) $(CFLAGS1) $@ $^

$(OBJ3):$(OBJS3)
		$(CC) $(CFLAGS1) $@ $^

$(OBJ4):$(OBJS4)
		$(CC) $(CFLAGS1) $@ $^

$(OBJ5):$(OBJS5)
		$(CC) $(CFLAGS1) $@ $^

$(OBJ6):$(OBJS6)
		$(CC) $(CFLAGS1) $@ $^

clean:
	rm *.so $(TARGET)
