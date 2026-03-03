all: build run

build: ./main

./main: ./main.c ./charList.h
	gcc main.c -o main

./charList.h: ./main.py
	python main.py

run:
	./main

clean:
	rm -f main charList.h

.PHONY: all build run clean