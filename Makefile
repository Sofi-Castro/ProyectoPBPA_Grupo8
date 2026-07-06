CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude
LIBS    = -lcurl

# --- Solo api (prueba de consola) ---
test_api: src/api.c include/api.h
	$(CC) $(CFLAGS) src/api.c $(LIBS) -o test_api

clean:
	rm -f test_api

.PHONY: clean
