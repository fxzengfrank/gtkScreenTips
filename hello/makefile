CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0 gthread-2.0`
LIBS = `pkg-config --libs glib-2.0 gthread-2.0`
SRCS = hello.c
TARGET = hello

main : $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LIBS)

clean :
	rm -f $(TARGET)

run :
	./$(TARGET)
