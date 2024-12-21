CC := gcc
CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wfloat-conversion -Wfloat-equal

app.exe: main.o list.o
	$(CC) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.d: %.c
	$(CC) -MM $< > $@

include $(wildcard *.d)

.PHONY: clean build run

build: CFLAGS += -g3
build: app.exe

run: app.exe
	./app.exe

clean:
	$(RM) -r -f *.exe *.o *.txt out/*
