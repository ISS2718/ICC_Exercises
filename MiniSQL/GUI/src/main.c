#include <gtk/gtk.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    GtkBuilder *builder; 
    GtkWidget *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "./glade/MiniSQL_GUI.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_Window"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

// called when window is closed
G_MODULE_EXPORT void on_mainWindow_destroy()
{
    gtk_main_quit();
}

G_MODULE_EXPORT void on_main_SearchBar_activate (GtkEntry *entry, gpointer user_data) {
    const char *str_entry = gtk_entry_get_text (entry);
    printf("%s\n", str_entry);
}
 //select Progs.Sigla, Doscentes.Nome from Progs, docentes