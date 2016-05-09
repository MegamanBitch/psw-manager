#include <iostream>

using namespace std;

#include "struttura_dati.h"
#include "funzioni.h"
#include "main.h"
#include <glib.h>

extern "C" gboolean handler_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    /*
     * mediante compilazione condizionale facciamo compilare prima la
     * versione con la stampa, poi quella con l'uscita dal main loop
     * (per far compilare la seconda versione basta scrivere false al posto
     * di true nella seguente direttiva)
     */
    gtk_main_quit();
    return TRUE;
}


int main(int argc, char *argv[]) {

  inizializza();
  initGUI(argc, argv);

  return 0;
}

void initGUI(int argc, char* argv[]){
		gtk_init(&argc, &argv);

		//Load gui
		builder = gtk_builder_new();
		gtk_builder_add_from_file(builder,"GUI.glade", NULL);
		gtk_builder_connect_signals(builder, NULL);

		gtk_main();
}

extern "C" void freezeAll_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	GtkWidget *mainWindow = GTK_WIDGET(gtk_builder_get_object(builder,"box4"));
	if (gtk_widget_is_sensitive(mainWindow)) {
		//gtk_lock_button_get_permission(GTK_LOCK_BUTTON(widget))->allowed = FALSE;
		gtk_widget_set_sensitive(mainWindow, FALSE);
	}
	else{
		//gtk_lock_button_set_permission(GTK_LOCK_BUTTON(widget), TRUE);
		gtk_widget_set_sensitive(mainWindow, TRUE);
	}
}

extern "C" void add_user_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	GtkWidget *window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	GtkWidget *window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));

	aggiungi_utente();

	gtk_widget_show_all(window1);
	gtk_widget_hide(window2);
}
