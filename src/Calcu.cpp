#include <gtk/gtk.h>

/* This callback quits the program */
static gboolean delete_event(GtkWidget *widget, GdkEvent *event,
		gpointer data) {
	gtk_main_quit();
	return FALSE;
}

void add_button() {
	char *a;
	a[0] = '1';
	for (int i = 1; i <= 9; i++) {
		a[0] += (i - 1);
		GtkWidget *numbtn = gtk_button_new_with_label(a);
//		g_signal_connect(numbtn, "clicked", G_CALLBACK (callback),
//				(gpointer ) "button 2");
		gtk_table_attach_defaults(GTK_TABLE(table), numbutton, 1, 2, 0, 1);
		gtk_widget_show (numbutton);
	}

//    button = gtk_button_new_with_label ("button 2");

	/* When the button is clicked, we call the "callback" function
	 * with a pointer to "button 2" as its argument */
//    g_signal_connect (button, "clicked",
//                      G_CALLBACK (callback), (gpointer) "button 2");
	/* Insert button 2 into the upper right quadrant of the table */
//    gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 0, 1);
//    gtk_widget_show (button);
}

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *table;

	gtk_init(&argc, &argv);

	/* Create a new window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* Set the window title */
	gtk_window_set_title(GTK_WINDOW(window), "Table");

	/* Set a handler for delete_event that immediately
	 * exits GTK. */
	g_signal_connect(window, "delete-event", G_CALLBACK (delete_event), NULL);

	/* Sets the border width of the window. */
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	/* Create a 2x2 table */
	table = gtk_table_new(13, 13, TRUE);

	/* Put the table in the main window */
	gtk_container_add(GTK_CONTAINER(window), table);

	gtk_widget_show(table);
	gtk_widget_show(window);

	gtk_main();

	return 0;
}
