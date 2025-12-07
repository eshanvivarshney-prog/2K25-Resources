CC = gcc
TARGET = socialmedia
SRCS = $(wildcard code/*.c)
OBJS = $(SRCS:.c=.o)

.SILENT:

all: $(TARGET) run clean

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

.c.o:
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

run: $(TARGET)
	./$(TARGET)

