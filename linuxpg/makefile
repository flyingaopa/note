OBJS = daemon_create.o daemon.o daemonhup.o
CC = gcc

all: daemon daemonhup

$(OBJS): %.o: %.c
	$(CC) -c $< -o $@

daemon: daemon.o daemon_create.o
	$(CC) -o daemon  daemon.o daemon_create.o
daemonhup: daemonhup.o daemon_create.o
	$(CC) -o daemonhup daemonhup.o daemon_create.o

clean:
	rm daemon daemonhup
	rm $(OBJS)
