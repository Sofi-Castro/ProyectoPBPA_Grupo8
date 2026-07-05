CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)

TARGET = programa

OBJS = main.o options.o api.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(GTK_LIBS) -lcurl

main.o: src/main.c include/options.h
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -c src/main.c -o main.o

options.o: src/options.c include/options.h include/api.h
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -c src/options.c -o options.o

api.o: src/api.c include/api.h
	$(CC) $(CFLAGS) -c src/api.c -o api.o

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean