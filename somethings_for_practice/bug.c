#include <gtk/gtk.h>
int main(int argc,char **argv)
{
	GtkWidget *win;
	GtkWidget *button;
	GtkWidget *hbox;
	GtkWidget *entry;
	gtk_init(&argc,&argv);
	win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(win),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	hbox=gtk_hbox_new(FALSE,0);
	button=gtk_button_new_with_label("Hello World!");
	entry=gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox),entry,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,-10);
	gtk_container_add(GTK_CONTAINER(win),hbox);
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}
