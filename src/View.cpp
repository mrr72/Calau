/*
 * View.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mrr
 */

#include "Mvc.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include<iostream>

View::View(int*argc, char***argv,Control c) {
	// TODO Auto-generated constructor stub
	GtkWidget *window;
	GtkWidget *table;
	control = c;
	gtk_init(argc, argv);

	/* Create a new window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* Set the window title */
	gtk_window_set_title(GTK_WINDOW(window), "Calculator");

	/* Set a handler for delete_event that immediately
	 * exits GTK. */
	g_signal_connect(window, "delete-event", G_CALLBACK (View::delete_event),
			NULL);

	/* Sets the border width of the window. */
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	/* Create a 2x2 table */
	table = gtk_table_new(17, 13, TRUE);
	entry = gtk_entry_new();
//	g_signal_connect(entry, "insert-at-cursor", G_CALLBACK (enter_callback),
//			entry);
	g_signal_connect(entry, "key_press_event", G_CALLBACK (enter_callback), entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry, 1, 12, 1, 3);
	gtk_widget_show(entry);
	add_button(table, entry);
	/* Put the table in the main window */
	gtk_container_add(GTK_CONTAINER(window), table);

	gtk_widget_show(table);
	gtk_widget_show(window);

	gtk_main();
}

View::~View() {
	// TODO Auto-generated destructor stub
}

gboolean View::delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
	gtk_main_quit();
	return FALSE;
}

bool View::enter_callback(GtkEntry *entry,GdkEventKey *event, gpointer user_data) {
//		const gchar *entry_text;
//		entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
//		gtk_entry_append_text(GTK_ENTRY(entry),event->string);
		control.handle_entry(event->string);
//		gtk_editable_insert_text(GTK_EDITABLE(entry),event->string,0,0);
		printf("Entry contents: %s\n", event->string);
	return true;
}
//void View::enter_callback(GtkWidget *widget, GtkWidget *entry) {
//	const gchar *entryf_text;
//	entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
//	printf("Entry contents: %s\n", entry_text);
//}

gboolean View::numberbtn_callback(GtkWidget *numbtn, gpointer callback_data) {
	char* a = (char*) gtk_button_get_label((GtkButton*) numbtn);
	int num = atoi(a);
	GtkEntry* entry = GTK_ENTRY(callback_data);
	gint tmp_pos = gtk_entry_get_text_length(entry);
/*	switch (atoi(a)) {
	case 1:
		gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
		break;
	case 2:
		gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
		break;
	case 3:
		gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
		break;
	case 4:
		gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
		break;
	case 5:
		gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
		break;
	case 6:
		gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
		break;
	case 7:
		gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
		break;
	case 8:
		gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
		break;
	case 9:
		gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
		break;
	default:
		break;
	}*/
}

void View::add_button(GtkWidget *table, GtkWidget* Display) {
	char aa[] = "0";
	for (int i = 0; i <= 8; i++) {
		aa[0] += 1;
		GtkWidget *numbtn = gtk_button_new_with_label(aa);
		g_signal_connect(numbtn, "clicked", G_CALLBACK (numberbtn_callback),
				(gpointer ) Display);
		gtk_table_attach_defaults(GTK_TABLE(table), numbtn, 1 + ((i * 2) % 6),
				3 + ((i * 2) % 6), 4 + ((i / 3) * 2), 6 + ((i / 3) * 2));
		gtk_widget_show(numbtn);
	}
//	TODO : complete button adding
}
