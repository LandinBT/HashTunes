#include "userinterface.hpp"

using namespace std;

void UserInterface::addSong() {
    char op; // option

    do {
        Song song;
        string str;
        Time time;
        unsigned short unshrt;

        cout << "Agregar cancion" << endl
             << "Titulo: ";
        getline(cin, str);
        song.setTitle(str);

        cout << "Artista: ";
        getline(cin, str);
        song.setArtist(str);

        cout << "Duracion (MM:SS): ";
        getline(cin, str, ':');
        unshrt = stoi(str);
        time.setMinute(unshrt);
        getline(cin, str);
        unshrt = stoi(str);
        time.setSecond(unshrt);
        song.setDuration(time);

        cout << endl;

        try {
            songsPtr->insertData(song.getId(), song);
            titleToIdMap[song.getTitle()] = song.getId();
            cout << "Cancion agregada correctamente!" << endl;
            }
        catch(const HashTable<int, Song>::Exception& ex) {
            cout << "Algo salio mal: " << ex.what() << endl;
            }

        cout << endl;

        cout << "Desea agregar otra cancion? (s/n): ";
        cin >> op;
        cin.ignore();
        op = toupper(op);

        if(op == 'S') {
            system("cls");
            }
        }
    while(op == 'S');

    if(op != 'S' and op != 'N') {
        cout << "Opcion invalida!, regresando al menu. . ." << endl;
        }
    }

void UserInterface::findSong() {
    Song song;
    string str;

    cout << "Buscar cancion" << endl
         << endl << "Titulo de la cancion: ";
    getline(cin, str);
    song.setTitle(str);

    cout << endl;

    try {
        int id = titleToIdMap.at(str);

        cout << songsPtr->searchData(id).toString() << endl;
        }
    catch(const HashTable<int, Song>::Exception& ex) {
        cout << "Algo salio mal: " << ex.what() << endl << endl;
        }

    cout << endl;

    enterToContinue();
    }

void UserInterface::deleteSong() {
    Song song;
    string str;

    cout << "Borrar cancion" << endl << endl
         << "Titulo de la cancion: ";
    getline(cin, str);
    song.setTitle(str);

    cout << endl;

    try {
        int id = titleToIdMap.at(str);
        cout << songsPtr->searchData(id).toString() << endl << endl;
        char op;

        cout << "Desea eliminar esta cancion? (s/n): ";
        cin >> op;
        cin.ignore();
        op = toupper(op);

        cout << endl;

        if(op == 'S') {
            songsPtr->deleteData(id);
            cout << "Cancion eliminada correctamente!" << endl;
            }
        else if(op == 'N') {
            cout << "Ok, regresando al menu. . ." << endl;
            }
        else {
            cout << "Opcion invalida, regresando al menu. . ." << endl;
            }
        }
    catch(const HashTable<int, Song>::Exception& ex) {
        cout << "Algo salio mal: " << ex.what() << endl;
        }

    enterToContinue();
    }

void UserInterface::showSongs() {
    cout << "C A N C I O N E S" << endl << endl;

    try {
        cout << songsPtr->toString() << endl;
        }
    catch(const HashTable<int, Song>::Exception& ex) {
        cout << "Algo salio mal: " << ex.what() << endl << endl;
        }

    enterToContinue();
    }

void UserInterface::deleteAllSongs() {
    char op;

    cout << "Desea eliminar todas las canciones? (s/n): ";
    cin >> op;
    cin.ignore();
    op = toupper(op);

    cout << endl;

    if(op == 'S') {
        try {
            songsPtr->deleteAll();
            cout << "Canciones eliminadas correctamente!" << endl;
            }
        catch(const HashTable<int, Song>::Exception& ex) {
            cout << "Algo salio mal: " << ex.what() << endl << endl;
            }
        }
    else if(op == 'N') {
        cout << "Ok, regresando al menu. . ." << endl;
        }
    else {
        cout << "Opcion incorrecta!" << endl;
        }

    enterToContinue();
    }

/*void UserInterface::load() {
    string str;

    cout << "Cargar canciones" << endl << endl
         << "Nombre del archivo: ";
    getline(cin, str);

    cout << endl;

    try {
        songsPtr->importFromDisk(str);
        cout << "Datos cargados correctamente!" << endl << endl;
        }
    catch(const ios_base::failure& ex) {
        cout << "Algo salio mal: " << ex.what() << endl;
        }

    enterToContinue();
    }

void UserInterface::save() {
    string str;

    cout << "Guardar canciones" << endl << endl
         << "Nombre del archivo: ";
    getline(cin, str);

    cout << endl;

    try {
        songsPtr->exportToDisk(str);
        cout << "Datos guardados correctamente!" << endl << endl;
        }
    catch(const ios_base::failure& ex) {
        cout << "Algo salio mal: " << ex.what() << endl;
        }

    enterToContinue();
    }*/

void UserInterface::enterToContinue() {
    cout << "Presiona ENTER para continuar. . .";
    getchar();
    }

UserInterface::UserInterface() {
    songsPtr = new HashTable<int, Song>();
    short op; // option

    do {
        system("cls");

        cout << "HashTunes" << endl << endl
             << "1. Agregar cancion" << endl
             << "2. Buscar cancion" << endl
             << "3. Borrar cancion" << endl
             << "4. Mostrar canciones" << endl
             << "5. Borrar todas las canciones" << endl
             //<< "6. Cargar" << endl
             //<< "7. Guardar" << endl
             << "0. Salir" << endl << endl
             << "Opcion: ";
        cin >> op;
        cin.ignore();

        if(op != 0) {
            system("cls");
            }
        else {
            cout << endl;
            }

        switch(op) {
            case 1:
                addSong();
                break;

            case 2:
                findSong();
                break;

            case 3:
                deleteSong();
                break;

            case 4:
                showSongs();
                break;

            case 5:
                deleteAllSongs();
                break;

            /*case 6:
                load();
                break;

            case 7:
                save();
                break;*/

            case 0:
                cout << "Gracias por usar el programa!" << endl;
                exit(0);
                break;

            default:
                cout << "Opcion invalida!" << endl;
                enterToContinue();
                break;
            }
        }
    while(op != 0);
    }

UserInterface::~UserInterface() {
    delete songsPtr;
    }
