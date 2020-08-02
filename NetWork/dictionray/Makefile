
CC=gcc#编译器 g++也可以
CFLAGS1=-shared -fPIC -o#编译共享库的编译选项
CFLAGS2=-L. -lwrap -ldatabase -lsqlite3#最终生成的可执行文件时的编译选项


OBJ1=libwrap.so#依赖文件1---共享库
OBJ2=libdatabase.so#依赖文件2---共享库
#OBJ3=libadminm.so#依赖文件3---共享库
#OBJ4=libcollegemanager.so#依赖文件3---共享库
#OBJ5=libgettableno.so#依赖文件3---共享库
#OBJ6=libstumanager.so#依赖文件3---共享库

OBJS1=wrap.c
OBJS2=database.c
#OBJS3=admin_manager.c
#OBJS4=college_manager.c
#OBJS5=get_tableno.c
#OBJS6=stu_manager.c

OBJS+=libwrap.so
OBJS+=libdatabase.so
#OBJS+=libadminmanager.so
#OBJS+=libcollegemanager.so
#OBJS+=libgettableno.so
#OBJS+=libstumanager.so

TARGET ?= server_dic_poll#最终编译的目标文件 服务器端
OBJT=server_dic_poll.c

TARGET1 ?= client_dic_poll#最终编译的目标文件1　客户端1
OBJT1=client_dic_poll.c

TARGET2 ?= client_dic_poll1#最终编译的目标文件2  客户端2
OBJT2=client_dic_poll1.c

TARGET3 ?= client_dic_poll2#最终编译的目标文件3  客户端3
OBJT3=client_dic_poll2.c

TARGET4 ?= client_dic_poll3#最终编译的目标文件4  客户端4
OBJT4=client_dic_poll3.c

#服务器目标文件
all:$(OBJS)
	sudo cp ./*.so /usr/lib/
	$(CC) -o $(TARGET) $(OBJT) $(CFLAGS2)
#	./$(TARGET)

#客户端目标文件
client:$(OBJS)
	sudo cp ./*.so /usr/lib/
	$(CC) -o $(TARGET1) $(OBJT1) $(CFLAGS2)
#	./$(TARGET)

#客户端目标文件

client1:$(OBJS)
	sudo cp ./*.so /usr/lib/
	$(CC) -o $(TARGET2) $(OBJT2) $(CFLAGS2)
#	./$(TARGET)

#客户端目标文件
client2:$(OBJS)
	sudo cp ./*.so /usr/lib/
	$(CC) -o $(TARGET3) $(OBJT3) $(CFLAGS2)
#	./$(TARGET)

#客户端目标文件
client3:$(OBJS)
	sudo cp ./*.so /usr/lib/
	$(CC) -o $(TARGET4) $(OBJT4) $(CFLAGS2)
#	./$(TARGET)

#生成共享库
$(OBJ1):$(OBJS1)
		$(CC) $(CFLAGS1) $@ $^

$(OBJ2):$(OBJS2)
		$(CC) $(CFLAGS1) $@ $^

#$(OBJ3):$(OBJS3)
#		$(CC) $(CFLAGS1) $@ $^

#$(OBJ4):$(OBJS4)
#		$(CC) $(CFLAGS1) $@ $^

#$(OBJ5):$(OBJS5)
#		$(CC) $(CFLAGS1) $@ $^

#$(OBJ6):$(OBJS6)
#		$(CC) $(CFLAGS1) $@ $^

clean:
	rm *.so $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)
