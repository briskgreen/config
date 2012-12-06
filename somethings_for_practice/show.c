#include <gtk/gtk.h>
void sig_fun(GtkWidget *win)
{
	g_signal_connect_swapped(G_OBJECT(win),"destroy"\
			,G_CALLBACK(gtk_main_quit),NULL);
}
void show_pic(const char *argv)
{
	GtkWidget *win,*img;
	int w,h;
	GdkPixbuf *pixbuf;
	GError *error=NULL;
	pixbuf=gdk_pixbuf_new_from_file(argv,&error);
	if(!pixbuf)
		gtk_main_quit();
	w=gdk_pixbuf_get_width(pixbuf);
	h=gdk_pixbuf_get_height(pixbuf);
	win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	img=gtk_image_new_from_file(argv);
	gtk_widget_set_size_request(img,w,h);
	gtk_window_set_title(GTK_WINDOW(win),argv);
	gtk_container_add(GTK_CONTAINER(win),img);
	gtk_widget_show_all(win);
	sig_fun(win);

}
int main(int argc,char **argv)
{
	gtk_init(&argc,&argv);
	show_pic(argv[1]);
	gtk_main();
	return 0;
}
