# 定义编译器和编译选项
CC = gcc
CFLAGS = -Wall -O2

# 定义目标和依赖关系
CLIENT = client
SERVER = server
SRCS = $(wildcard *.c)
COBJS = $(patsubst %.c, %.o, $(filter-out $(SERVER).c, $(SRCS)))
SOBJS = $(patsubst %.c, %.o, $(filter-out $(CLIENT).c, $(SRCS)))

# 默认目标，编译所有目标文件
all: $(CLIENT) $(SERVER)

# 目标文件依赖于对应的源文件和头文件
$(CLIENT): $(COBJS)
	$(CC) -o $@ $^

$(SERVER): $(SOBJS)
	$(CC) -o $@ $^

# 编译规则，生成目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理规则，删除所有目标文件和中间文件
clean:
	rm -f $(CLIENT) $(SERVER) $(COBJS) $(SOBJS) *.o
