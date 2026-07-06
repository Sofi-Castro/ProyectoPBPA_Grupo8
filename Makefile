CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
LIBS = $(shell pkg-config --libs gtk+-3.0 -lcurl -lcjson)

TARGET = programa

OBJS = main.o interfaz.o api.o json_parseo.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS) 

main.o: main.c include/interfaz.h include/api.h include/json_parseo.h
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -c main.c -o main.o

interfaz.o: src/interfaz.c include/interfaz.h include/api.h include/json_parseo.h
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -c src/interfaz.c -o interfaz.o

api.o: src/api.c include/api.h
	$(CC) $(CFLAGS) -c src/api.c -o api.o

json_parseo.o: src/json_parseo.c include/json_parseo.h
	$(CC) $(CFLAGS) -c src/json_parseo.c -o json_parseo.o

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean