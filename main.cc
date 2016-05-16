#include <iostream>
#include <glib.h>
#include "main.h"



static std::string master_password;
static std::string nome_utente;

int main(int argc, char *argv[]) {

  inizializza();
  openssl_inizializza();

  initGUI(argc, argv);

  openssl_quit();


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

extern "C" void handler_freezeAll(GtkWidget *widget, GdkEvent *event, gpointer user_data){
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
  GtkWidget *initialize_master_password_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_master_password_window"));
  GtkWidget *error_match_password = GTK_WIDGET(gtk_builder_get_object(builder, "error_match_password_window"));

  gtk_widget_hide(error_match_password);
  gtk_widget_hide(main_window);
  gtk_widget_show_all(initialize_master_password_window);


  GtkWidget *delete_insert_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "insert_master_password"));
  GtkWidget *delete_repeat_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "repeat_master_password"));


  gtk_editable_delete_text(GTK_EDITABLE(delete_insert_master_password), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(delete_repeat_master_password), 0, -1);
}

extern "C" void handler_get_masterPassword(GtkWidget *widget, GdkEvent *event, gpointer user_data){

  GtkWidget *initialize_master_password_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_master_password_window"));
  GtkWidget *error_match_password = GTK_WIDGET(gtk_builder_get_object(builder, "error_match_password_window"));
  GtkWidget *initialize_first_user_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_first_user_window"));

  GtkWidget *insert_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "insert_master_password"));
  GtkWidget *repeat_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "repeat_master_password"));
  GtkEntryBuffer *password_buffer_insert = gtk_entry_get_buffer(GTK_ENTRY(insert_master_password));
  GtkEntryBuffer *password_buffer_repeat = gtk_entry_get_buffer(GTK_ENTRY(repeat_master_password));

  GtkWidget *delete_insert_user = GTK_WIDGET(gtk_builder_get_object(builder, "insert_user"));
  gtk_editable_delete_text(GTK_EDITABLE(delete_insert_user), 0, -1);

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

  gtk_widget_show_all(welcome_window);
  gtk_widget_hide(initialize_master_password_window);
}

extern "C" void handler_show_main_window(GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  GtkWidget *welcome_window = GTK_WIDGET(gtk_builder_get_object(builder, "welcome_window"));
  GtkWidget *website_window = GTK_WIDGET(gtk_builder_get_object(builder, "website_window"));
  GtkWidget *login_window = GTK_WIDGET(gtk_builder_get_object(builder,"login_window"));
  GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder,"box4"));

  gtk_widget_set_sensitive(box, FALSE);

  gtk_widget_hide(login_window);
  gtk_widget_hide(website_window);
  gtk_widget_hide(welcome_window);
  gtk_widget_show_all(main_window);
}

extern "C" void handler_get_username(GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *initialize_first_user_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_first_user_window"));
  GtkWidget *insert_user = GTK_WIDGET(gtk_builder_get_object(builder, "insert_user"));
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

  GtkEntryBuffer *user_buffer_insert = gtk_entry_get_buffer(GTK_ENTRY(insert_user));
  const gchar *var_user_buffer_insert = gtk_entry_buffer_get_text(user_buffer_insert);
  DBG(std::cout << "Username: " << var_user_buffer_insert << std::endl;);

  nome_utente = var_user_buffer_insert;

  aggiungi_utente(nome_utente, master_password);
  openssl_encrypt(nome_utente, master_password);
  openssl_decrypt(nome_utente);

  gtk_widget_show_all(main_window);
  gtk_widget_hide(initialize_first_user_window);

}

extern "C" void handler_show_website (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  GtkWidget *website_window = GTK_WIDGET(gtk_builder_get_object(builder, "website_window"));

  gtk_widget_hide(main_window);
  gtk_widget_show_all(website_window);

}

extern "C" void handler_get_website (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *website_insert_entry= GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_entry"));
  GtkWidget *website_insert_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_password"));
  GtkWidget *website_insert_url = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_url"));
  GtkWidget *website_insert_note = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_note"));
  GtkEntryBuffer *website_buffer_insert_entry = gtk_entry_get_buffer(GTK_ENTRY(website_insert_entry));
  GtkEntryBuffer *website_buffer_insert_password = gtk_entry_get_buffer(GTK_ENTRY(website_insert_password));
  GtkEntryBuffer *website_buffer_insert_url = gtk_entry_get_buffer(GTK_ENTRY(website_insert_url));
  GtkEntryBuffer *website_buffer_insert_note = gtk_entry_get_buffer(GTK_ENTRY(website_insert_note));

  const gchar *var_buffer_insert_entry = gtk_entry_buffer_get_text(website_buffer_insert_entry);
  DBG(std::cout << "Entry:  " << var_buffer_insert_entry << std::endl);

  const gchar *var_buffer_insert_password = gtk_entry_buffer_get_text(website_buffer_insert_password);
  DBG(std::cout << "Password:  " << var_buffer_insert_password << std::endl);

  const gchar *var_buffer_insert_url = gtk_entry_buffer_get_text(website_buffer_insert_url);
  DBG(std::cout << "URL:  " << var_buffer_insert_url << std::endl);

  const gchar *var_buffer_insert_note = gtk_entry_buffer_get_text(website_buffer_insert_note);
  DBG(std::cout << "Note:  " << var_buffer_insert_note << std::endl);

  aggiungi_entry(nome_utente, var_buffer_insert_entry, var_buffer_insert_password, var_buffer_insert_url, var_buffer_insert_note);

}


extern "C" void handler_freeze_generatePassword (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *switch_generate = GTK_WIDGET(gtk_builder_get_object(builder,"switch_generate"));
  GtkWidget *website_insert_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_password"));
  GtkWidget *website_length = GTK_WIDGET(gtk_builder_get_object(builder, "website_length"));
  GtkWidget *generate_password = GTK_WIDGET(gtk_builder_get_object(builder, "generate_password"));
  GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder, "box25"));

  if (gtk_switch_get_active(GTK_SWITCH(switch_generate)) == TRUE) {
    gtk_editable_set_editable(GTK_EDITABLE(website_insert_password), FALSE);
    gtk_editable_set_editable(GTK_EDITABLE(generate_password), TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(website_length), TRUE);

    gtk_widget_set_sensitive(box, TRUE);

    GtkWidget *delete_website_insert_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_password"));
    gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_password), 0, -1);
  }
  else{
    gtk_editable_set_editable(GTK_EDITABLE(website_insert_password), TRUE);
    gtk_editable_set_editable(GTK_EDITABLE(website_length), FALSE);
    gtk_editable_set_editable(GTK_EDITABLE(generate_password), FALSE);

    gtk_widget_set_sensitive(box, FALSE);

  }
}

extern "C" void handler_show_login (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *login_window = GTK_WIDGET(gtk_builder_get_object(builder,"login_window"));

  gtk_widget_show_all(login_window);
}

extern "C" void handler_get_login (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *login_insert_user = GTK_WIDGET(gtk_builder_get_object(builder,"login_insert_user"));
  GtkWidget *login_insert_password = GTK_WIDGET(gtk_builder_get_object(builder,"login_insert_password"));

  GtkEntryBuffer *login_buffer_insert_user = gtk_entry_get_buffer(GTK_ENTRY(login_insert_user));
  GtkEntryBuffer *login_buffer_insert_password = gtk_entry_get_buffer(GTK_ENTRY(login_insert_password));

  const gchar *var_login_buffer_insert_user = gtk_entry_buffer_get_text(login_buffer_insert_user);
  DBG(std::cout << "User:  " << var_login_buffer_insert_user << std::endl;);
  const gchar *var_login_buffer_insert_password = gtk_entry_buffer_get_text(login_buffer_insert_password);
  DBG(std::cout << "Password:  " << var_login_buffer_insert_password << std::endl;);
}

extern "C" void handler_entropy (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *insert_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "insert_master_password"));

  const gchar *character = gtk_editable_get_chars (GTK_EDITABLE(insert_master_password),
                            (gtk_entry_get_text_length (GTK_ENTRY(insert_master_password)) - 1), -1);


  //ris += get_entropy(character);
  DBG(std::cout << "Carattere: " << character;);
  //DBG(std::cout << " Entropia: " << ris << std::endl;);
  //DBG(std::cout << "Numero lowercase: " << has_lowercase << std::endl;);
}
