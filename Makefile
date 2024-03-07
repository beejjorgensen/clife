CC=gcc
CCOPTS=-Wall -Wextra -Werror -g

clife: main.o display.o life.o
	$(CC) -o $@ $^

main.o: main.c display.h life.h sysdetect.h
	$(CC) $(CCOPTS) -c -o $@ $<

display.o: display.c display.h life.h
	$(CC) $(CCOPTS) -c -o $@ $<

life.o: life.c life.h
	$(CC) $(CCOPTS) -c -o $@ $<

.PHONY: clean pristine

clean:
	rm -f main.o display.o life.o

pristine: clean
	rm -f clife

