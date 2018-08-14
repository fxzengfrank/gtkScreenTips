CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0 gobject-2.0 gio-2.0 gtk+-3.0`
LIBS = `pkg-config --libs glib-2.0 gobject-2.0 gio-2.0 gtk+-3.0`
SRCS = sock.c
TARGET = sock

main : $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LIBS)

clean :
	rm -f $(TARGET)

run :
	./$(TARGET)
