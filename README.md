# psw-manager

The project objective was to realize a free, open-source, simple password manager to store your password safely.

With this program you can:
- **add multiple user**, every user has his own *.txt file;
- **add multiple password** for every user;
- **store your credentials** using [sha-512](https://en.wikipedia.org/wiki/SHA-2);
- **encrypt** your *.txt file with a simple script.

# Documentation
the documentation is in the doc folder and it is made by Doxygen, you can find it in the /doc/html/index.html

# Compile
To compile the program use the Makefile inside the repo.
Uncomment #-D NDEBUG if you don't want debug messages.

```
make [options]
```

These are the available options:
- **compile**
- **dependencies**
- **clean**
- **removeFile**
- **cleanAll**

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

Requirements
- [Gtk 3.0](http://www.gtk.org/download/index.php)
- [OpenSSL](https://it.wikipedia.org/wiki/OpenSSL)

# Bugs
When entering the master password, the entropy bar add entropy if you delete characters
