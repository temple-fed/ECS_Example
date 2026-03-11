all : clean app

FILES := $(shell find src/ -name '*.c')

clean :
	rm -f app

app :
	gcc -std=c89 -Wall -Wpedantic -Wconversion -Wextra -Wno-long-long -O1 -g -o app \
	$(FILES) app.c -I inc/ -I 3rd/ -L. -lSDL3 -ldwmapi
