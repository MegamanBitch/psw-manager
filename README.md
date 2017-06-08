# psw-manager

The project objective was to realize a free, open-source, simple password manager to store your password safely.

With this program you can:
- **add multiple user**, every user has his own *.txt file;
- **add multiple password** for every user;
- **store your credentials** using [sha-512](https://en.wikipedia.org/wiki/SHA-2);
- **encrypt** your *.txt file with a simple script.

To compile the program use the Makefile inside the repo.
Uncomment #-D NDEBUG if you don't want debug messages.

To encrypt your *.txt file use this command from the console:
```
./pswscript [path to file] --encrypt
```

To decrypt your *.txt.gpg file use this command from the console:
```
./pswscript [path to file] --decrypt
```

To print the help use this command from the console:
```
./pswscript --help
```
**

Requirements
- **[Gtk 3.0]**(http://www.gtk.org/download/index.php)
- **[OpenSSL]**(https://it.wikipedia.org/wiki/OpenSSL)
