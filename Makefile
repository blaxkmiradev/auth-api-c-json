CC=gcc
CFLAGS=-Wall

SRC=main.c cJSON.c auth.c fileio.c server.c
OUT=auth

all:
	$(CC) $(SRC) -o $(OUT)

run:
	./auth
