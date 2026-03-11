all : clean app

FILES  := $(shell find src/ -name '*.c')
CFLAGS := -std=c89 -Wall -Wpedantic -Wconversion -Wextra -Wno-long-long -O1 -g
CFLAGS += $(shell pkg-config --cflags sdl3)
LIBS   := $(shell pkg-config --libs sdl3)

ifeq ($(OS),Windows_NT)
   LIBS += -ldwmapi
endif

clean :
	rm -f app

app :
	cc $(CFLAGS) -o app $(FILES) app.c -I inc/ $(LIBS)
