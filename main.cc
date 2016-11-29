#include <iostream>
#include <glib.h>
#include "main.h"



static std::string master_password;
static std::string nome_utente;
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
		gtk_builder_add_from_file(builder,"GUI.glade", NULL);
    gtk_builder_connect_signals(builder, NULL);

		gtk_main();

}

extern "C" gboolean handler_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data){
    gtk_main_quit();
    g_slist_free(lista_utenti);
    return TRUE;
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
  geom.min_width = 800;
  geom.min_height = 600;

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

  gtk_file_chooser_set_current_name (chooser, ("*.gsx"));

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
    {
      char *filename;

      filename = gtk_file_chooser_get_filename (chooser);
      crea_file (filename, "", 0);
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
  GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder,"box4"));

  gtk_widget_set_sensitive(box, FALSE);

  gtk_widget_hide(credits_window);
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

  GtkEntryBuffer *user_buffer_insert = gtk_entry_get_buffer(GTK_ENTRY(insert_user));
  const gchar *var_user_buffer_insert = gtk_entry_buffer_get_text(user_buffer_insert);
  DBG(std::cout << "Username: " << var_user_buffer_insert << std::endl;);

  nome_utente = var_user_buffer_insert;

  aggiungi_utente (nome_utente, master_password);

  utente_t *my_data = (utente_t *)lista_utenti->data;
  gtk_label_set_text (GTK_LABEL(current_user_name), my_data->nome.c_str());

  openssl_encrypt(nome_utente, master_password);
  //openssl_decrypt(nome_utente);

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

  GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  GtkWidget *website_window = GTK_WIDGET(gtk_builder_get_object(builder, "website_window"));

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

  if (!aggiungi_entry(nome_utente, var_buffer_insert_entry, var_buffer_insert_password,
        var_buffer_insert_url, var_buffer_insert_note)) {
    DBG(std::cout << "Non esiste questo utente" << std::endl;)
  }

  gtk_widget_show_all(main_window);
  gtk_widget_hide(website_window);

}


extern "C" void handler_freeze_generatePassword (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *switch_generate = GTK_WIDGET(gtk_builder_get_object(builder,"switch_generate"));
  GtkWidget *box_password = GTK_WIDGET(gtk_builder_get_object(builder, "box16"));
  GtkWidget *tutto = GTK_WIDGET(gtk_builder_get_object(builder, "box_generate_password"));

  if (gtk_switch_get_active(GTK_SWITCH(switch_generate)) == TRUE) {
    gtk_widget_set_sensitive(tutto, TRUE);
    gtk_widget_set_sensitive(box_password, FALSE);

    GtkWidget *delete_website_insert_password = GTK_WIDGET(gtk_builder_get_object(builder, "website_insert_password"));
    gtk_editable_delete_text(GTK_EDITABLE(delete_website_insert_password), 0, -1);
  }
  else{
    gtk_widget_set_sensitive(tutto, FALSE);
    gtk_widget_set_sensitive(box_password, TRUE);

  }
}

extern "C" void handler_show_login (GtkWidget *widget, GdkEvent *event, gpointer user_data){
  GtkWidget *login_window = GTK_WIDGET(gtk_builder_get_object(builder,"login_window"));
  GtkWidget* mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
  //Create file chooser dialog
  GtkWidget* dialog = createFileChooser(GTK_WINDOW(mainWindow), GTK_FILE_CHOOSER_ACTION_OPEN, "Open file");

  //Set file chooser filter
  GtkFileFilter* filter = gtk_file_filter_new();
  gtk_file_filter_add_pattern(filter, "*.gsx");
  gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);

  //Exec the dialog
	gint res = gtk_dialog_run(GTK_DIALOG(dialog));

  //If ok button is pressed
	if (res == GTK_RESPONSE_ACCEPT){
    //file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    gtk_widget_show_all(login_window);
    gtk_widget_destroy(dialog);
  }
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

  flag_parameters_t PARAMETERS;
  unsigned short lun_psw = 10;
  unsigned short char_psw[lun_psw];

  //GtkWidget *spin_button = GTK_WIDGET(gtk_builder_get_object(builder, "website_length"));

  GtkWidget *uppercase = GTK_WIDGET(gtk_builder_get_object(builder, "uppercase"));
  GtkWidget *space = GTK_WIDGET(gtk_builder_get_object(builder, "space"));
  GtkWidget *lowercase = GTK_WIDGET(gtk_builder_get_object(builder, "lowercase"));
  GtkWidget *special = GTK_WIDGET(gtk_builder_get_object(builder, "special"));
  GtkWidget *digits = GTK_WIDGET(gtk_builder_get_object(builder, "digits"));
  GtkWidget *brackets = GTK_WIDGET(gtk_builder_get_object(builder, "brackets"));
  GtkWidget *minus = GTK_WIDGET(gtk_builder_get_object(builder, "minus"));
  GtkWidget *underscore = GTK_WIDGET(gtk_builder_get_object(builder, "underscore"));

  PARAMETERS.uppercase = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(uppercase));
  PARAMETERS.lowercase = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(lowercase));
  PARAMETERS.space = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(space));
  PARAMETERS.special = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(special));
  PARAMETERS.digits = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(digits));
  PARAMETERS.brackets = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(brackets));
  PARAMETERS.minus = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(minus));
  PARAMETERS.underscore = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(underscore));


  //lun_psw = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spin_button));
  DBG(std::cout << "Spin button value: " << lun_psw << std::endl;)

  srand(time(NULL));

  unsigned short temp;
  unsigned short contatore = 0;

  do {
    temp = 32 + (rand() % (126 - 32));
    DBG(std::cout << "Numero random: " << temp << std::endl;)
    if (getRandom_char(PARAMETERS, temp) != -1) {
      char_psw[contatore] = getRandom_char(PARAMETERS, temp);
      contatore++;
    }
  } while(contatore < lun_psw);

  for (size_t i = 0; i < lun_psw; i++) {
    DBG(std::cout << (char)char_psw[i] << std::endl;)
  }
}
