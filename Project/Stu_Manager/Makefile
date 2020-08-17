
CC=gcc#编译器 g++也可以
CFLAGS1=-shared -fPIC -o#编译共享库的编译选项
CFLAGS2=-L. -lusermanager -luserregist -luserloginmanager -ladminmanager -lcollegemanager -lgettableno -lstumanager -lprofsmanager -lsubinfomanager -lyearinfomanager\
			-lmysqlclient#最终生成的可执行文件时的编译选项


OBJ1=libusermanager.so#依赖文件1---共享库
OBJ2=libuserregist.so#依赖文件2---共享库
OBJ3=libadminmanager.so#依赖文件3---共享库
OBJ4=libcollegemanager.so#依赖文件3---共享库
OBJ5=libgettableno.so#依赖文件3---共享库
OBJ6=libstumanager.so#依赖文件3---共享库
OBJ7=libprofsmanager.so#依赖文件3---共享库
OBJ8=libuserloginmanager.so#依赖文件3---共享库
OBJ9=libsubinfomanager.so
OBJ10=libyearinfomanager.so

OBJS1=user_manager.c
OBJS2=user_regist.c
OBJS3=admin_manager.c
OBJS4=college_manager.c
OBJS5=get_tableno.c
OBJS6=stu_manager.c
OBJS7=profs_manager.c
OBJS8=user_login.c
OBJS9=subinfo_manager.c
OBJS10=yerinfo_manager.c

OBJS+=libusermanager.so
OBJS+=libuserregist.so
OBJS+=libadminmanager.so
OBJS+=libcollegemanager.so
OBJS+=libgettableno.so
OBJS+=libstumanager.so
OBJS+=libprofsmanager.so
OBJS+=libuserloginmanager.so
OBJS+=libsubinfomanager.so
OBJS+=libyearinfomanager.so

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

$(OBJ7):$(OBJS7)
	$(CC) $(CFLAGS1) $@ $^

$(OBJ8):$(OBJS8)
	$(CC) $(CFLAGS1) $@ $^

$(OBJ9):$(OBJS9)
	$(CC) $(CFLAGS1) $@ $^

$(OBJ10):$(OBJS10)
	$(CC) $(CFLAGS1) $@ $^

clean:
	rm *.so $(TARGET)
