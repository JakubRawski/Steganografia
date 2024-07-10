//
// Created by Jakub on 26.05.2024.
//

#include "info.h"
#include "BitTool.h"
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




auto Info(const std::string& path) ->void{
    sf::Image image;
    if(!image.loadFromFile(path)){
        std::cout << "not loaded";
    } else {
        https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t
        std::filesystem::file_time_type file_time = std::filesystem::last_write_time(path);
        std::time_t tt = to_time_t(file_time);
        std::tm *tm = std::localtime(&tt);
        std::string res =  fmt::format("{:%Y-%m-%d %H:%M}", *tm);
        auto p = std::filesystem::path(path);
        auto size  =std::filesystem::file_size(p);
        auto name = p.string();
        auto extension = p.extension().string();
        fmt::println("File extension : {} ",extension);
        if(extension != ".png" && extension != ".bmp"){ //This line checks if this file is supported png/bmp
            fmt::println("This extension is not supported");
            return;
        }
        fmt::println("This extension is supported: {}",extension);
        fmt::println("File size {} : {} bytes",name,size);
        fmt::print("File dimension: {}x{}\n", image.getSize().x,image.getSize().y);
        fmt::print("Last time edit: {}\n", res);
    }
}

