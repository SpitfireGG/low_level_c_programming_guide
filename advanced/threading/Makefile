CC = gcc
CFLAGS = -Wall -g

TARGET = atomic

# Source and object files
SRCS = atomic.c threading.c
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Phony target to clean up
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

# Phony target to rebuild everything
.PHONY: rebuild
rebuild: clean all
