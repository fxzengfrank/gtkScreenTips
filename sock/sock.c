#include <glib.h>
#include <gio/gio.h>
#include <gmodule.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>

gpointer test (gpointer data)
{
    GError *error = NULL;

    GSocket *socket = NULL;
    socket = g_socket_new (G_SOCKET_FAMILY_IPV4,
            G_SOCKET_TYPE_STREAM,
            G_SOCKET_PROTOCOL_TCP,
            &error);
    if (socket != NULL) {
        g_printf("new socket success.\n");
        error = NULL;
    } else {
        g_printf("new socket failure.\n");
        error = NULL;
    }

    gint socketfd = g_socket_get_fd (socket);
    g_printf("socket fd is %d\n", socketfd);

    GSocketAddress *sockaddr = NULL;
    sockaddr = g_inet_socket_address_new_from_string ("127.0.0.1", 7777);
    if (sockaddr != NULL) {
        g_printf ("parse socket address success.\n");
    } else {
        g_printf ("parse socket address failure.\n");
    }

    gboolean retflag = FALSE;

    retflag = g_socket_bind (socket, sockaddr, TRUE, &error);
    g_object_unref (sockaddr);
    sockaddr = NULL;
    if (retflag) {
        g_printf("bind socket success.\n");
        error = NULL;
    } else {
        g_printf("bind socket failure.\n");
        error = NULL;
    }

    retflag = g_socket_listen (socket, &error);
    if (retflag) {
        g_printf("listen socket success.\n");
        error = NULL;
    } else {
        g_printf("listen socket failure.\n");
        error = NULL;
    }

    GSocket *acceptsocket = NULL;

    acceptsocket = g_socket_accept (socket, NULL, &error);
    if (acceptsocket != NULL) {
        g_printf("accept socket success.\n");
        error = NULL;
    } else {
        g_printf("accept socket failure.\n");
        error = NULL;
    }

    gint acceptsocketfd = g_socket_get_fd (acceptsocket);
    g_printf("accept socket fd is %d\n", acceptsocketfd);

    GIOChannel *iochannel = NULL;
    iochannel = g_io_channel_unix_new (acceptsocketfd);
    
    GSource *source;
    source = g_io_create_watch (iochannel, G_IO_IN);


    GString *buffer = g_string_new (NULL);
    GIOStatus status;
    
    while (1) {
        status = g_io_channel_read_line_string (iochannel, buffer, NULL, &error);
        if (status == G_IO_STATUS_NORMAL) {
            g_printf("io channel read success.\n");
            g_printf("buffer is: %s\n", buffer->str);
        } else {
            g_thread_yield ();
            g_usleep(50000);
        }
    }

    g_object_unref (acceptsocket);
    acceptsocket = NULL;

    g_object_unref (socket);
    socket = NULL;
}

int main (int argc, char **argv)
{
    /*
    GThread *thread;
    thread = g_thread_new ("socket thread", test, NULL);
     */

    gtk_init (&argc, &argv);
    GtkWidget *window = NULL;
    window = gtk_window_new (GTK_WINDOW_POPUP);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size (GTK_WINDOW(window), 800, 10);
    gtk_window_set_keep_above (GTK_WINDOW(window), TRUE);
    gtk_window_set_decorated (GTK_WINDOW(window), FALSE);
    gtk_window_move (GTK_WINDOW(window), 100, 100);

    GtkWidget *label = NULL;
    label = gtk_label_new (NULL);
    gtk_container_add (GTK_CONTAINER(window), label);
    gtk_label_set_text (GTK_LABEL(label), "some text");

    gtk_widget_show (label);
    gtk_widget_show (window);
    gtk_main ();

    gtk_main_quit();
    //g_thread_join (thread);
}

