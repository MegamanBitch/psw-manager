#include <iostream>
#include <glib.h>
#include "main.h"


static std::string nome_file;
static std::string master_password;
static std::string nome_utente;
static std::string current_user;

static double ris = 0;



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
		gtk_builder_add_from_file(builder,"gui/GUI.glade", NULL);
    gtk_builder_connect_signals(builder, NULL);

    //Get widget
    fileListModel = GTK_LIST_STORE(gtk_builder_get_object(builder, "fileListModel"));

    assert(fileListModel != NULL);

		gtk_main();

}

void addToFileView(entry_t &values){
	//Get file list model
	GtkTreeIter iter;

	//Append the file to the fileListModel
	gtk_list_store_append(fileListModel, &iter);
	gtk_list_store_set (fileListModel, &iter,
						COL_TITLE, values.title.c_str(),
						COL_USERNAME, values.username.c_str(),
						COL_PASSWORD, values.password.c_str(),
						COL_URL, values.url.c_str(),
						COL_NOTE, values.note.c_str(),
						-1);
}


void clearFileView(){
	gtk_list_store_clear(fileListModel);
}

void reloadFileView(){
	GSList* current = lista_utenti;
  GSList *entry;
  utente_t *my_user = (utente_t *)current->data;
  entry = my_user->entries;

	clearFileView();
	while(entry != NULL){
    entry_t *my_entry = (entry_t *)entry->data;
    addToFileView(*my_entry);
		entry = g_slist_next(entry);
	}
}

extern "C" gboolean handler_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    gtk_main_quit();
    g_slist_free(lista_utenti);
    return TRUE;
}

void showMessageDialog(GtkWindow* parent, GtkMessageType type, const gchar* msg){
	GtkWidget* dialog = gtk_message_dialog_new(
														parent,
														GTK_DIALOG_MODAL,
														type,
														GTK_BUTTONS_OK,
														"%s", msg);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

GtkWidget* createFileChooser(GtkWindow* parent, GtkFileChooserAction action, const gchar* title){
  //Prepare file open dialog
  GtkWidget* dialog = gtk_file_chooser_dialog_new (
                                      title,
                                      parent,
                                      action,
                                      "Cancel",
                                      GTK_RESPONSE_CANCEL,
                                      "OK",
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
  GdkGeometry geom;

  //Resize the window
  gtk_window_set_geometry_hints(GTK_WINDOW(dialog), NULL, &geom, GDK_HINT_MIN_SIZE);

  return dialog;
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

  GtkWidget *dialog;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Save File",
                                        GTK_WINDOW(main_window),
                                        action,
                                        ("_Cancel"),
                                        GTK_RESPONSE_CANCEL,
                                        ("_Save"),
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);
  chooser = GTK_FILE_CHOOSER (dialog);

  gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

  gtk_file_chooser_set_current_name (chooser, ("*.txt"));

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
    {
      char *filename;

      filename = gtk_file_chooser_get_filename (chooser);
      nome_file = gtk_file_chooser_get_filename (chooser);
      crea_file (filename);
      g_free (filename);
    }

  gtk_widget_destroy (dialog);




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

  entropy_azzera();

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
  GtkWidget *credits_window = GTK_WIDGET(gtk_builder_get_object(builder, "credits_window"));
  GtkWidget *error_login = GTK_WIDGET(gtk_builder_get_object(builder, "error_login"));


  gtk_widget_hide(credits_window);
  gtk_widget_hide(error_login);
  gtk_widget_hide(login_window);
  gtk_widget_hide(website_window);
  gtk_widget_hide(welcome_window);
  gtk_widget_show_all(main_window);
}

extern "C" void handler_show_credits_window (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *credits_window = GTK_WIDGET(gtk_builder_get_object(builder, "credits_window"));
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));



  gtk_widget_hide(main_window);
  gtk_widget_show_all(credits_window);

}

extern "C" void handler_get_username(GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *initialize_first_user_window = GTK_WIDGET(gtk_builder_get_object(builder, "initialize_first_user_window"));
  GtkWidget *insert_user = GTK_WIDGET(gtk_builder_get_object(builder, "insert_user"));
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  GtkWidget *current_user_name = GTK_WIDGET(gtk_builder_get_object(builder, "current_user_name"));
  GtkWidget *add_entry = GTK_WIDGET(gtk_builder_get_object(builder,"add_entry"));

  GtkEntryBuffer *user_buffer_insert = gtk_entry_get_buffer(GTK_ENTRY(insert_user));
  const gchar *var_user_buffer_insert = gtk_entry_buffer_get_text(user_buffer_insert);
  DBG(std::cout << "Username: " << var_user_buffer_insert << std::endl;);

  nome_utente = var_user_buffer_insert;

  if (strlen(var_user_buffer_insert) == 0) {
    DBG(std::cout << "No user" << std::endl;)
  }
  else{
    aggiungi_utente (nome_utente, master_password);
    GSList * last_user = g_slist_last(lista_utenti);

    utente_t *my_data = (utente_t *)last_user->data;
    current_user = my_data->nome;
    gtk_label_set_text (GTK_LABEL(current_user_name), current_user.c_str());
    clearFileView();


    openssl_encrypt(nome_file, nome_utente, master_password);
    //openssl_decrypt(nome_utente);

    if (g_slist_length(lista_utenti) != 0) {
      gtk_widget_set_sensitive(add_entry, TRUE);
    }

    gtk_widget_show_all(main_window);
    gtk_widget_hide(initialize_first_user_window);

  }

}

extern "C" void handler_show_website (GtkWidget *widget, GdkEvent *event, gpointer user_data){

  if (g_slist_length(lista_utenti) == 0) {
    DBG(std::cout << "Non e' presente nessun utente nel database" << std::endl;)
    return;
  }

  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  GtkWidget *website_window = GTK_WIDGET(gtk_builder_get_object(builder, "website_window"));
  GtkWidget *delete_website_insert_title = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_title"));
  GtkWidget *delete_website_insert_username = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_username"));
  GtkWidget *delete_website_insert_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_password"));
  GtkWidget *delete_website_insert_repeat = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_repeat"));
  GtkWidget *delete_website_insert_url = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_url"));
  GtkWidget *delete_website_insert_note = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_note"));

  gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_title), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_username), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_password), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_repeat), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_url), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_note), 0, -1);

  gtk_widget_hide(main_window);
  gtk_widget_show_all(website_window);

}

extern "C" void handler_get_website (GtkWidget *widget, GdkEvent *event, gpointer user_data){

  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  GtkWidget *website_window = GTK_WIDGET(gtk_builder_get_object(builder, "website_window"));


  GtkWidget *website_insert_title= GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_title"));
  GtkWidget *website_insert_username= GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_username"));
  GtkWidget *website_insert_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_password"));
  GtkWidget *website_insert_url = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_url"));
  GtkWidget *website_insert_note = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_note"));
  GtkWidget *website_generated_password= GTK_WIDGET(gtk_builder_get_object(builder, "website_generated_password"));
  GtkEntryBuffer *website_buffer_insert_title = gtk_entry_get_buffer(GTK_ENTRY(website_insert_title));
  GtkEntryBuffer *website_buffer_insert_username = gtk_entry_get_buffer(GTK_ENTRY(website_insert_username));
  GtkEntryBuffer *website_buffer_insert_password = gtk_entry_get_buffer(GTK_ENTRY(website_insert_password));
  GtkEntryBuffer *website_buffer_insert_url = gtk_entry_get_buffer(GTK_ENTRY(website_insert_url));
  GtkEntryBuffer *website_buffer_insert_note = gtk_entry_get_buffer(GTK_ENTRY(website_insert_note));

  const gchar *var_buffer_insert_title = gtk_entry_buffer_get_text(website_buffer_insert_title);
  DBG(std::cout << "Title:  " << var_buffer_insert_title << std::endl);

  const gchar *var_buffer_insert_username = gtk_entry_buffer_get_text(website_buffer_insert_username);
  DBG(std::cout << "Username:  " << var_buffer_insert_username << std::endl);

  const gchar *var_buffer_insert_password;
  if(gtk_entry_get_text_length (GTK_ENTRY(website_insert_password)) != 0 || gtk_entry_get_text_length (GTK_ENTRY(website_generated_password)) != 0){
    var_buffer_insert_password = gtk_entry_buffer_get_text(website_buffer_insert_password);
    DBG(std::cout << "Password:  " << var_buffer_insert_password << std::endl);

    const gchar *var_buffer_insert_url = gtk_entry_buffer_get_text(website_buffer_insert_url);
    DBG(std::cout << "URL:  " << var_buffer_insert_url << std::endl);

    const gchar *var_buffer_insert_note = gtk_entry_buffer_get_text(website_buffer_insert_note);
    DBG(std::cout << "Note:  " << var_buffer_insert_note << std::endl);

    if (!aggiungi_entry(nome_utente, var_buffer_insert_title, var_buffer_insert_username, var_buffer_insert_password,
          var_buffer_insert_url, var_buffer_insert_note)) {
      DBG(std::cout << "Non esiste questo utente" << std::endl;)
    }
    else{
      save_entries(nome_file, nome_utente);

      entry_t values;
      values.title = var_buffer_insert_title;
      values.username = var_buffer_insert_username;
      values.password = var_buffer_insert_password;
      values.url = var_buffer_insert_url;
      values.note = var_buffer_insert_note;
      addToFileView(values);
    }

    gtk_widget_show_all(main_window);
    gtk_widget_hide(website_window);

  } else {
    DBG(std::cout << "Nessuna password inserita" << std::endl;)
  }


}

extern "C" void handler_freeze_generatePassword (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *switch_generate = GTK_WIDGET(gtk_builder_get_object(builder,"switch_generate"));
  GtkWidget *box25 = GTK_WIDGET(gtk_builder_get_object(builder, "box25"));
  GtkWidget *website_length = GTK_WIDGET(gtk_builder_get_object(builder, "website_length"));
  GtkWidget *website_insert_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_password"));
  GtkWidget *website_insert_repeat = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_repeat"));

  if (gtk_switch_get_active(GTK_SWITCH(switch_generate)) == TRUE) {
    gtk_widget_set_sensitive(box25, TRUE);
    gtk_widget_set_sensitive(website_length, TRUE);
    gtk_widget_set_sensitive(website_insert_password, FALSE);
    gtk_widget_set_sensitive(website_insert_repeat, FALSE);

    GtkWidget *delete_website_insert_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_password"));
    GtkWidget *delete_website_insert_repeat = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_repeat"));
    GtkWidget *delete_website_generated_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_generated_password"));
    gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_password), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_repeat), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(delete_website_generated_password), 0, -1);
    gtk_spin_button_set_value (GTK_SPIN_BUTTON(website_length),0);
  }
  else{
    gtk_widget_set_sensitive(box25, FALSE);
    gtk_widget_set_sensitive(website_length, FALSE);
    gtk_widget_set_sensitive(website_insert_password, TRUE);
    gtk_widget_set_sensitive(website_insert_repeat, TRUE);

  }
}

extern "C" void handler_show_login (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *login_window = GTK_WIDGET(gtk_builder_get_object(builder,"login_window"));
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));


  GtkWidget *dialog = createFileChooser(GTK_WINDOW(main_window), GTK_FILE_CHOOSER_ACTION_OPEN, "Open file");

  //Set file chooser filter
  GtkFileFilter* filter = gtk_file_filter_new();
  GdkGeometry geom;
  geom.min_width = 800;
  geom.min_height = 600;

  //Resize the window
  gtk_window_set_geometry_hints(GTK_WINDOW(dialog), NULL, &geom, GDK_HINT_MIN_SIZE);
  gtk_file_filter_add_pattern(filter, "*.txt");
  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);

  gint res = gtk_dialog_run (GTK_DIALOG (dialog));

  //If ok button is pressed
	if (res == GTK_RESPONSE_ACCEPT){
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);
    nome_file = gtk_file_chooser_get_filename (chooser);
    g_free (filename);

    gtk_widget_show_all(login_window);
  }
  else{
    showMessageDialog(GTK_WINDOW(main_window), GTK_MESSAGE_ERROR, "Invalid file header");
  }


  GtkWidget *delete_insert_user = GTK_WIDGET(gtk_builder_get_object(builder, "login_insert_user"));
  GtkWidget *delete_insert_password = GTK_WIDGET(gtk_builder_get_object(builder, "login_insert_password"));


  gtk_editable_delete_text(GTK_EDITABLE(delete_insert_user), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(delete_insert_password), 0, -1);

  gtk_widget_destroy (dialog);

}

extern "C" void handler_get_login (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *login_window = GTK_WIDGET(gtk_builder_get_object(builder,"login_window"));
  GtkWidget *login_insert_user = GTK_WIDGET(gtk_builder_get_object(builder,"login_insert_user"));
  GtkWidget *login_insert_password = GTK_WIDGET(gtk_builder_get_object(builder,"login_insert_password"));
  GtkWidget *error_login = GTK_WIDGET(gtk_builder_get_object(builder,"error_login"));
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
  GtkWidget *current_user_name = GTK_WIDGET(gtk_builder_get_object(builder, "current_user_name"));
  GtkWidget *add_entry = GTK_WIDGET(gtk_builder_get_object(builder,"add_entry"));


  GtkEntryBuffer *login_buffer_insert_user = gtk_entry_get_buffer(GTK_ENTRY(login_insert_user));
  GtkEntryBuffer *login_buffer_insert_password = gtk_entry_get_buffer(GTK_ENTRY(login_insert_password));

  const gchar *var_login_buffer_insert_user = gtk_entry_buffer_get_text(login_buffer_insert_user);
  DBG(std::cout << "User:  " << var_login_buffer_insert_user << std::endl;);
  const gchar *var_login_buffer_insert_password = gtk_entry_buffer_get_text(login_buffer_insert_password);
  DBG(std::cout << "Password:  " << var_login_buffer_insert_password << std::endl;);

  if (strlen(var_login_buffer_insert_user) == 0 || strlen(var_login_buffer_insert_password) == 0) {
    DBG(std::cout << "User or password empty" << std::endl;)
  }

  else{
    DBG(std::cout << "Nome file che apre: " << nome_file << std::endl;)
    if(!login_check(nome_file, var_login_buffer_insert_user, var_login_buffer_insert_password)){
      DBG(std::cout << "Errore" << std::endl;)
      gtk_widget_show_all(error_login);
      gtk_widget_hide(login_window);
    }
    else{
      current_user = var_login_buffer_insert_user;
      nome_utente = current_user;

      reloadFileView();

      gtk_label_set_text (GTK_LABEL(current_user_name), current_user.c_str());
      gtk_widget_set_sensitive(add_entry, TRUE);
      gtk_widget_show_all(main_window);
      gtk_widget_hide(login_window);
    }
  }
}


extern "C" void handler_entropy (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *insert_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "insert_master_password"));
  GtkWidget *entropy_master_password = GTK_WIDGET(gtk_builder_get_object(builder, "entropy_master_password"));
  GtkWidget *entropy_bits = GTK_WIDGET(gtk_builder_get_object(builder, "entropy_bits"));

  gtk_level_bar_set_min_value (GTK_LEVEL_BAR(entropy_master_password), 0.);
  gtk_level_bar_set_max_value (GTK_LEVEL_BAR(entropy_master_password), 210.);

  const gchar *character = gtk_editable_get_chars (GTK_EDITABLE(insert_master_password),
                            (gtk_entry_get_text_length (GTK_ENTRY(insert_master_password)) - 1), -1);


  ris = get_entropy(character);

  gtk_level_bar_set_value (GTK_LEVEL_BAR(entropy_master_password), ris);

  char buffer[210];
  sprintf(buffer, "%.3lf", ris);
  gtk_label_set_text (GTK_LABEL(entropy_bits), buffer);

  DBG(std::cout << "Carattere: " << character;);
  DBG(std::cout << " Entropia: " << ris << std::endl;);
  //DBG(std::cout << "Numero lowercase: " << has_lowercase << std::endl;);
}


extern "C" void handler_chooseFile (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *pick_file = gtk_file_chooser_widget_new (GTK_FILE_CHOOSER_ACTION_OPEN);
  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

  gtk_widget_show_all(pick_file);
  gtk_widget_hide(main_window);
}

extern "C" void handler_spinButton (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *spin_button = GTK_WIDGET(gtk_builder_get_object(builder, "website_length"));

  gtk_spin_button_spin (GTK_SPIN_BUTTON(spin_button), GTK_SPIN_STEP_FORWARD, 1.);
  gtk_spin_button_update (GTK_SPIN_BUTTON(spin_button));
}


extern "C" void handler_generatePassword (GtkWidget *widget, GdkEvent *event, gpointer user_data){

  GtkWidget *website_length = GTK_WIDGET(gtk_builder_get_object(builder, "website_length"));
  GtkWidget *website_generated_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_generated_password"));

  /**
  * Prendo la lunghezza della password dall'elemento gtk_spin_button e alloco
  * un vettore di interi di quella lunghezza
  */
  unsigned short lun_psw = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(website_length));
  if (lun_psw == 0) {
    DBG(std::cout << "Lunghezza password 0" << std::endl;)
    return;
  }
  DBG(std::cout << "Lunghezza password: " << lun_psw << std::endl;)
  /*
  * dinamico
  */
  char *char_psw = new char [lun_psw + 1];

  srand(time(0));

  parameters_t parameters;
  generate_numbers(parameters, lun_psw);

  DBG(std::cout << "Numero lowercase: " << parameters.lowercase << std::endl;)
  DBG(std::cout << "Numero uppercase: " << parameters.uppercase << std::endl;)
  DBG(std::cout << "Numero digits: " << parameters.digits << std::endl;)
  DBG(std::cout << "Numero special: " << parameters.special << std::endl;)

  unsigned char lowercase_char;
  unsigned char uppercase_char;
  unsigned char digits_char;
  unsigned char special_char;

  unsigned short l = parameters.lowercase;
  unsigned short u = parameters.uppercase;
  unsigned short d = parameters.digits;
  unsigned short s = parameters.special;

  for (unsigned short i = 0; i < l; i++) {
    lowercase_char = std::rand() % RANGE_LOWERCASE;
    DBG(std::cout << "Ho estratto: " << LOWERCASE_CHARACTERS[lowercase_char] << std::endl;)
    char_psw[i] = LOWERCASE_CHARACTERS[lowercase_char];
  }

  for (unsigned short i = l; i < u + l; i++) {
    uppercase_char = std::rand() % RANGE_UPPERCASE;
    DBG(std::cout << "Ho estratto: " << UPPERCASE_CHARACTERS[uppercase_char] << std::endl;)
    char_psw[i] = UPPERCASE_CHARACTERS[uppercase_char];
  }

  for (unsigned short i = u + l; i < d + l + u; i++) {
    digits_char = std::rand() % RANGE_DIGITS;
    DBG(std::cout << "Ho estratto: " << DIGITS_CHARACTERS[digits_char] << std::endl;)
    char_psw[i] = DIGITS_CHARACTERS[digits_char];
  }

  for (unsigned short i = l + u + d; i < l + u + d + s; i++) {
    special_char = std::rand() % RANGE_SPECIAL_CHARACTERS;
    DBG(std::cout << "Ho estratto: " << SPECIAL_CHARACTERS[special_char] << std::endl;)
    char_psw[i] = SPECIAL_CHARACTERS[special_char];
  }

  DBG(std::cout << "Array prima di mescolarlo: ";)
  DBG(for (unsigned short i = 0; i < lun_psw; i++) {
    std::cout << char_psw[i];
  })

  std::random_shuffle(char_psw, char_psw + lun_psw);

  DBG(std::cout << std::endl << "Array dopo averlo mescolato: ";)
  DBG(for (unsigned short i = 0; i < lun_psw; i++) {
    std::cout << char_psw[i];
  })

  gtk_entry_set_text (GTK_ENTRY(website_generated_password), char_psw);

}
