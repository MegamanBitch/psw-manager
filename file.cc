#include "file.h"


bool save_credentials(std::string filename, std::string username, std::string password, size_t salt){
    std::ofstream f(filename.c_str(), std::ios::app);
    if (f.good()) {
      if (g_slist_length(user_list) != 0) {
        f << username << std::endl;
        f << password << std::endl;
        f << salt << std::endl;
      }
      f.close();
    }
    return f;
  }



bool file_init(std::string name){
      std::ofstream f((name).c_str());
      return f;
}


size_t get_salt(std::string nome){
  std::ifstream f(nome.c_str(), std::ios::out);

  size_t salt;

  f >> salt;

  return salt;
}

bool login_check(std::string filename, std::string username, std::string password){

  std::ifstream f(filename.c_str());
  if (!f.good()) {
    DBG(std::cout << "Non riconosce il nome del file" << std::endl;)
    return f;
  }

  // check if the credentials are the same
  std::string saved_username;
  std::string saved_password;
  size_t saved_salt;

  std::getline(f, saved_username);
  DBG(std::cout << "Ho letto dal file l'username: " << saved_username << std::endl;)

  std::getline(f, saved_password);
  DBG(std::cout << "Ho letto dal file la password: " << saved_password << std::endl;)

  f >> saved_salt;
  DBG(std::cout << "Ho letto dal file il sale: " << saved_salt << std::endl;)


  if(openssl_decrypt(username, password, saved_salt, saved_username, saved_password)){
    DBG( std::cout << "Le credenziali coincidono, accesso effettuato" << std::endl;)
    load_entries(filename, username, password);
    f.close();
    return true;
  }
  else{
    DBG(std::cout << "Le credenziali non coincidono, acesso fallito" << std::endl;)
    f.close();
    return false;
  }

}


bool save_entries(std::string filename, std::string username){
  std::ofstream f;
  if (f.good()) {
    f.open((filename.c_str()), std::ios::app);


    // temporary GSList @users e @entry
    GSList *users = user_list;
    GSList *entry;
    user_t *my_user;
    entry_t *my_entry;

    DBG(std::cout << "Numero di users: " << g_slist_length(user_list) << std::endl;)
    while (users != NULL) {

      // cast @users->data to read its contents
      my_user = (user_t *)users->data;
      DBG(std::cout << "Comparo " << my_user->name << " con " << username << std::endl;)

      if (my_user->name == username) {
        // Assign to the temporary GSList the current user lists
        entry = my_user->entries;

        GSList * last_entry = g_slist_last(entry);
        my_entry = (entry_t *)last_entry->data;

        DBG(std::cout << "Title: " << my_entry->title << std::endl;)
        f << my_entry->title << std::endl;

        DBG(std::cout << "Username: " << my_entry->username << std::endl;)
        f << my_entry->username << std::endl;

        DBG(std::cout << "Password: " << my_entry->password << std::endl;)
        f << my_entry->password << std::endl;

        DBG(std::cout << "URL: " << my_entry->url << std::endl;)
        f << my_entry->url << std::endl;

        DBG(std::cout << "Note: " << my_entry->note << std::endl;)
        f << my_entry->note << std::endl;

        entry = g_slist_next(entry);

      }
      users = g_slist_next(users);
    }
    f.close();
    return true;
  }
  f.close();
  return false;
}



bool load_entries(std::string filename, std::string username, std::string password){
  std::ifstream f;
  if(f.good()){
    g_slist_free(user_list);
    user_list_init();

    user_t *my_user = new user_t;

    my_user->name = username;
    my_user->master_password = password;
    my_user->entries = NULL;

    DBG(std::cout << "Nome utente: " << my_user->name << std::endl;)
    DBG(std::cout << "Password: " << my_user->master_password << std::endl;)

    user_list = g_slist_append(user_list, my_user);

    f.open((filename.c_str()), std::ifstream::in);
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    DBG(std::cout << "Ho saltato le prime 3 righe" << std::endl;)

    unsigned int line_number = 0;
    std::string line;

    entry_t *my_entry;
    my_entry = new entry_t;

    while(f){
      getEntry(f, line);
      line_number = (line_number + 1) % 5;

      switch (line_number) {
        case 1:
          my_entry->title = line;
          break;
        case 2:
          my_entry->username = line;
          break;
        case 3:
          my_entry->password = line;
          break;
        case 4:
          my_entry->url = line;
          break;
        case 0:
          my_entry->note = line;
          break;
      }

      /**
      * Quando sono nel caso 0 ho aggiunto tutti i campi di @entry_t e quindi
      * devo appendere @entry_t alla GSList.
      * In questo caso uso la funzione prepend perche' da documentazione delle GSList
      *
      * Note that g_slist_append() has to traverse the entire list to find the end
      * which is inefficient when adding multiple elements. A common idiom to avoid the
      * inefficiency is to prepend the elements and reverse the list when all elements
      * have been added.
      * 
      */
      if (line_number == 0){
        my_user->entries = g_slist_prepend(my_user->entries, my_entry);
        my_entry = new entry_t;
      }
    }
    my_user->entries = g_slist_reverse(my_user->entries);
  }
  DBG(print_list();)
  f.close();
  return f;

}


void getEntry(std::istream& input, std::string& output){
  char c;
  std::string temp;
  std::getline(input, output);
  while(input.peek() == ' '){
    input >> c;
    std::getline(input, temp);
    output = output + " " + temp;
  }
  DBG(std::cout << "ho letto " << output << std::endl;)
}
