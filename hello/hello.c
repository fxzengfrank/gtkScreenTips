#include <glib.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
#include <unistd.h>

gpointer thread_func1 (gpointer data)
{
    gint tmp = 0;
    while (1)
    {
        g_printf ("%d\n", tmp);
        tmp++;
        if (tmp > 5) {
            //return 0;
            g_thread_exit (GINT_TO_POINTER(tmp));
        }
        g_thread_yield();
        g_usleep (200000);
    }
}

int main (int argc, char **argv)
{
    g_printf ("main in\n");
    GThread *p_thread = NULL;
    p_thread = g_thread_new ("func1", thread_func1, NULL);
    gpointer rdata = g_thread_join (p_thread);
    g_printf ("rdata = %d\n", GPOINTER_TO_INT(rdata));
    g_printf ("main out\n");
    return 0;
}
