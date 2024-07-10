//
// Created by Jakub on 26.05.2024.
//
#include "help.h"

#include <fmt/core.h>
//-i	–info 1 argument (path) {argc = 3}
//-e	–encrypt 2 arguments (path, message) {argc = 4}
//-d	–decrypt 1 argument (path) {argc = 3}
//-c	–check 2 arguments (path, message) {argc = 4}
//-h	–help  0 arguments  {argc = 1}


auto help()->void {
    fmt::print("Program do Steganografii obrazowej.\n"
               "Obecnie rozszerzenia ktore program wspiera:\n"
               "    > .png\n"
               "    > .bmp\n"
               "Uzycie:\n"
               "    -i –-info --> wyswietla informacje o podanym pliku.\n"
               "    Przyklad uzycia: \n"
               "        > Steganografia.cpp -i \\plik.png\n"
               "        > Steganografia.cpp --info \\plik.bmp\n"
               "    -e –-encrypt --> podana wiadomosc szufruje do pliku zdjeciowego:\n"
               "    Przyklad uzycia: \n"
               "        > Steganografia.cpp -e \\plik.png \"ala ma kota\"\n"
               "        > Steganografia.cpp --encrypt C:\\Users\\User\\Desktop\\zdj.png \"ala ma kota\"\n"
               "    -d –-decrypt --> podana wiadomosc odszyfruje z pliku zdjeciowego:\n"
               "    Przyklad uzycia: \n"
               "        > Steganografia.cpp -d \\plik.png \n"
               "        > Steganografia.cpp --decrypt C:\\Users\\User\\Desktop\\plik.png \n"
               "    -c –-check --> sprawdza czy do danego pliku mozna zaszyfrowac wiadomosc:\n"
               "    Przyklad uzycia: \n"
               "        > Steganografia.cpp -c \\plik.png \"ala ma kota\" \n"
               "        > Steganografia.cpp –-check C:\\Users\\User\\Desktop\\plik.png \"ala ma kota\" \n"
               "    -h –-help --> wyswietla informacje o programie:\n"
               "    Przyklad uzycia: \n"
               "        > Steganografia.cpp -h\n"
               "        > Steganografia.cpp --help\n "
    );

}