CC = gcc
G_LIBS = glib-2.0 gobject-2.0 gio-2.0 gtk+-3.0
CFLAGS = `pkg-config --cflags $(G_LIBS)`
LIBS = `pkg-config --libs $(G_LIBS)`
SRCS = sock.c
TARGET = proc_screen_tip

main : $(SRCS)
	-make clean
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LIBS)

.PHONY: run
run :
	make main
	./$(TARGET)

.PHONY: clean
clean :
	-rm $(TARGET)
