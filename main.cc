#include <iostream>

using namespace std;

#include "struttura_dati.h"
#include "funzioni.h"
#include "main.h"
#include <glib.h>

extern "C" gboolean handler_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
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
	GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder,"box4"));
	if (gtk_widget_is_sensitive(main_window)) {
		//gtk_lock_button_get_permission(GTK_LOCK_BUTTON(widget))->allowed = FALSE;
		gtk_widget_set_sensitive(main_window, FALSE);
	}
	else{
		//gtk_lock_button_set_permission(GTK_LOCK_BUTTON(widget), TRUE);
		gtk_widget_set_sensitive(main_window, TRUE);
	}
}

extern "C" void handler_add_user(GtkWidget *widget, GdkEvent *event, gpointer user_data){
	GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	GtkWidget *welcome_window = GTK_WIDGET(gtk_builder_get_object(builder, "welcome_window"));
  GtkWidget *initialize_configuration_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_configuration_window"));

  if (lista_utenti == NULL) {
    gtk_widget_show_all(initialize_configuration_window);
    gtk_widget_hide(welcome_window);
  }
	else {
    aggiungi_utente();

  	gtk_widget_show_all(main_window);
  	gtk_widget_hide(welcome_window);
  }
}

extern "C" void setup_masterPassword_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data){

}
