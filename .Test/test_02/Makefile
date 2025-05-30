CC=gcc
CFLAGS=-Wall -Wextra -std=c99

all: window.a mock.a app.exe test.exe

window.a: window.o
	ar rcs window.a window.o

mock.a: mock_glfw.o
	ar rcs mock.a mock_glfw.o

window.o: window.c window.h
	$(CC) $(CFLAGS) -c window.c

mock_glfw.o: mock_glfw.c mock_glfw.h
	$(CC) $(CFLAGS) -c mock_glfw.c

app.exe: app.c window.a
	$(CC) $(CFLAGS) app.c window.a -lglfw -o app.exe

test.exe: test.c window.a mock.a
	$(CC) $(CFLAGS) test.c window.a mock.a -o test.exe

clean:
	rm -f *.o *.a *.exe

.PHONY: all clean
