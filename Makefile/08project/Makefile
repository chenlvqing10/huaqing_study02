CC := gcc 
CFLAGS = -c -o
OBJS += main.o
OBJS += add.o
OBJS += sub.o
OBJS += mul.o
OBJS += div.o

TARGET ?= demo

%.o:%.c
	@ #main.c ---> main.o
	@ #sub.c  ---> sub.o
	@ # ....
	$(CC) $(CFLAGS) $@ $<

all:$(OBJS)
	$(CC) $^ -o $(TARGET)

clean:
	rm *.o $(TARGET)



