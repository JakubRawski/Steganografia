//
// Created by Jakub on 24.05.2024.
//
#include "Errors.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <fmt/core.h>
#include <filesystem>





auto Check(const std::string& path, const std::string& message) ->bool {
    sf::Image image;
    if(!image.loadFromFile(path)){
        std::cout << "not loaded";
        errFile();
        return false;
    } else {

        auto p = std::filesystem::path(path);
        auto size  =std::filesystem::file_size(p);
        auto name = p.string();
        auto extension = p.extension().string();
        fmt::println("File extension : {} ",extension);
        if(extension != ".png" && extension != ".bmp"){  //This line checks if this file is supported png/bmp
            fmt::println("This extension is not supported");
            return false ;
        }
        fmt::println("This extension is supported: {}",extension);
        fmt::println("File size {} : {} bytes",name,size);
        fmt::println("Message length: {} chars", message.size());
        auto trueSize =  (image.getSize().x * image.getSize().y) *3/8 -32;//number of available bytes to use
        if(trueSize < message.size()){
            errSize();
            return false;
        } else{
            fmt::println("The photo will contain the given message");
            return true;
        }
    }

}





