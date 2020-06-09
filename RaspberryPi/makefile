humidity.o: humidity.c buzzer.c
	gcc -c humidity.c buzzer.c

install:
	gcc -o humidity humidity.o -lwiringPi -lm

buzzer:
	gcc -o buzzer buzzer.o -lwiringPi
