//
// Created by Jakub on 26.05.2024.
//

#include "Errors.h"

#include <iostream>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <fmt/core.h>
#include <fmt/format.h>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <fmt/chrono.h>

auto errFlag() -> int{
    fmt::println("Błąd: nierozpoznana lub niekompletna flaga, sprobuj: "
                 "> Steganografia.cpp -h");
    exit(1);
}

auto errArg() -> int{
    fmt::println("Błąd: nieprawidlowa ilosc argumentow, sprobuj: "
                 "> Steganografia.cpp -h");
    exit(2);
}
auto errFile() -> int{
    fmt::println("Błąd: nie mozna otworzyc pliku, sprobuj: "
                 "> Steganografia.cpp -h");
    exit(3);
}


auto errSize() -> int {
    fmt::println("Plik jest za maly lub wiadomosc jest za dluga, zdjecie nie pomiesci podanej wiadomosci");
    exit(4);
}






