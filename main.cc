#include <iostream>
#include <glib.h>
#include "main.h"



static std::string master_password;

int main(int argc, char *argv[]) {

  inizializza();
  openssl_inizializza();


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

extern "C" gboolean handler_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    gtk_main_quit();
    g_slist_free(lista_utenti);
    return TRUE;
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
  GtkWidget *initialize_master_password_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_master_password_window"));
  GtkWidget *error_match_password = GTK_WIDGET(gtk_builder_get_object(builder, "error_match_password_window"));

  gtk_widget_hide(error_match_password);
  GtkWidget *delete_insert_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "insert_master_password"));
  GtkWidget *delete_repeat_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "repeat_master_password"));


  gtk_editable_delete_text(GTK_EDITABLE(delete_insert_master_password), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(delete_repeat_master_password), 0, -1);


  if (g_slist_length(lista_utenti) == 0) {
    gtk_widget_show_all(initialize_master_password_window);
    gtk_widget_hide(welcome_window);
  }
	else {
  	gtk_widget_show_all(main_window);
  	gtk_widget_hide(welcome_window);
  }
}

extern "C" void handler_get_masterPassword(GtkWidget *widget, GdkEvent *event, gpointer user_data){

  GtkWidget *initialize_master_password_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_master_password_window"));
  GtkWidget *error_match_password = GTK_WIDGET(gtk_builder_get_object(builder, "error_match_password_window"));
  GtkWidget *initialize_first_user_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_first_user_window"));

  GtkWidget *insert_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "insert_master_password"));
  GtkWidget *repeat_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "repeat_master_password"));
  GtkEntryBuffer *password_buffer_insert = gtk_entry_get_buffer(GTK_ENTRY(insert_master_password));
  GtkEntryBuffer *password_buffer_repeat = gtk_entry_get_buffer(GTK_ENTRY(repeat_master_password));


  const gchar *var_password_buffer_insert = gtk_entry_buffer_get_text(password_buffer_insert);
  master_password = var_password_buffer_insert;
  DBG(std::cout << "Insert: " << var_password_buffer_insert << std::endl);

  const gchar *var_password_buffer_repeat = gtk_entry_buffer_get_text(password_buffer_repeat);
  DBG(std::cout << "Repeat: " <<var_password_buffer_repeat << std::endl);

  if (!strcmp(var_password_buffer_repeat, var_password_buffer_insert) && strlen(var_password_buffer_insert) != 0) {
    DBG(std::cout << "same passwords, access granted" << std::endl;)

    gtk_widget_show_all(initialize_first_user_window);
    gtk_widget_hide(initialize_master_password_window);
  }
  else{
    DBG(std::cout << "passwords does not match, access failed" << std::endl;)
    gtk_widget_show_all(error_match_password);
    gtk_widget_hide(initialize_master_password_window);
  }
}

extern "C" void handler_show_welcome_window(GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *welcome_window = GTK_WIDGET(gtk_builder_get_object(builder, "welcome_window"));
  GtkWidget *initialize_master_password_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_master_password_window"));

  GtkWidget *delete_insert_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "insert_master_password"));
  GtkWidget *delete_repeat_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "repeat_master_password"));


  gtk_editable_delete_text(GTK_EDITABLE(delete_insert_master_password), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(delete_repeat_master_password), 0, -1);

  gtk_widget_show_all(welcome_window);
  gtk_widget_hide(initialize_master_password_window);
}

extern "C" void handler_show_main_window(GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *initialize_first_user_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_first_user_window"));
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

  gtk_widget_show_all(main_window);
  gtk_widget_hide(initialize_first_user_window);
}

extern "C" void handler_get_username(GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *initialize_first_user_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_first_user_window"));
  GtkWidget *insert_user = GTK_WIDGET(gtk_builder_get_object(builder, "insert_user"));
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));


  GtkEntryBuffer *user_buffer_insert = gtk_entry_get_buffer(GTK_ENTRY(insert_user));

  const gchar *var_user_buffer_insert = gtk_entry_buffer_get_text(user_buffer_insert);
  DBG(std::cout << "Username: " << var_user_buffer_insert << std::endl;);

  std::string nome_utente = var_user_buffer_insert;
  std::string password = master_password;

  aggiungi_utente(nome_utente, password);

  gtk_widget_show_all(main_window);
  gtk_widget_hide(initialize_first_user_window);

}
