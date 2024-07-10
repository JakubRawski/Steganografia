//
// Created by Jakub on 17.05.2024.
//
#include "BitTool.h"
#include "Engine.h"

#include "SFML/System/FileInputStream.hpp"
#include "SFML/Graphics.hpp"
#include <string>
#include "fmt/core.h"
#include <iostream>




auto Encrypt(const std::string& path, std::string message) -> void{
    sf::FileInputStream stream;
    sf::Image image;
    bool Finished = false;

    if(!image.loadFromFile(path)){
        std::cout << "not loaded\n";
    }
    auto KEY = getKeyGEN();
    auto dimension = image.getSize();
    auto numberCOUNT = 0; //count of bits reserved for length information (MAX: 32)
    auto bitMessage = prepareMessage(message);
    std::vector<int>::iterator it; //iterator of bitMessage
    auto len = getBitVector(message.size(), 32);
    for(int i = 0; i < dimension.y; i++){ //by width y
        for (int j = 0; j < dimension.x; j++) { //by length x
            auto pixel = image.getPixel(j,i);
            auto colorVALUE = 0;
            auto keyFragment = std::vector<int>(); //framnegt of the key
            auto encryptedColor = std::vector<int>(); //value which decide of if bit is changed
            for(int currColor = 0; currColor <= 2; currColor++){// 0 -> red, 1 -> green, 2 -> blue
                if(Finished){
                    image.saveToFile(path); //after finishing encrypting
                    fmt::print("Encrypt finished");

                    return;
                }
                keyFragment.clear(); //prevents  memory leak
                encryptedColor.clear();
                switch (currColor) {
                    case 0:{
                        colorVALUE = pixel.r; //select red component
                        for(int iter = 0; iter < 8; iter++){
                            keyFragment.push_back(KEY[iter]); //select key fragmet
                        }
                        break;
                    }
                    case 1:{
                        colorVALUE = pixel.g; //select green component
                        for(int iter = 8; iter < 16; iter++){ //select key fragmet
                            keyFragment.push_back(KEY[iter]);
                        }
                        break;
                    }
                    case 2:{
                        colorVALUE = pixel.b; //select blue component
                        for(int iter = 16; iter < 24; iter++){ //select key fragmet
                            keyFragment.push_back(KEY[iter]);
                        }
                        break;
                    }
                }
                encryptedColor = masking(getBitVector(colorVALUE,8),keyFragment); //prepare value
                //even number of 1 -> 1
                //odd number of 1 -> 0
                if(numberCOUNT < 32){

                    if(BOOLFunction(encryptedColor) != len[numberCOUNT++]){
                        colorVALUE = setComponent(getBitVector(colorVALUE,8),keyFragment);
                    }
                    if(BOOLFunction(masking(getBitVector(colorVALUE,8),keyFragment)) != len[numberCOUNT-1]){
                        fmt::println("ERROR WHEN ENCODING, CHECK KEY");
                    }
                }
                else{
                    if(BOOLFunction(encryptedColor) != bitMessage[0]){
                        colorVALUE = setComponent(getBitVector(colorVALUE,8),keyFragment);
                    }
                    if(BOOLFunction(masking(getBitVector(colorVALUE,8),keyFragment)) != bitMessage[0]){
                        fmt::println("ERROR WHEN ENCODING, CHECK KEY");
                    }

                    it = bitMessage.begin();
                    bitMessage.erase(it);
                    if(bitMessage.empty()){
                        Finished = true;
                    }
                }

                auto color = image.getPixel(j,i);
                switch (currColor) {
                    case 0:{
                        color = sf::Color(colorVALUE,color.g,color.b);
                        break;
                    }
                    case 1:{
                        color = sf::Color(color.r,colorVALUE,color.b);
                        break;
                    }
                    case 2:{
                        color = sf::Color(color.r,color.g,colorVALUE);
                        break;
                    }
                }
                image.setPixel(j,i,color);
            }

        }
    }

}

auto Decrypt(const std::string& path) -> std::string {
    std::string res; //preparing decrypted message
    sf::FileInputStream stream;
    sf::Image image;
    bool Finished = false;
    bool retrievingLength = false;

    if (!image.loadFromFile(path)) {
        std::cout << "not loaded\n";
    }

    auto KEY = getKeyGEN();
    auto dimension = image.getSize();
    auto numberCOUNT = 0; //count of bits reserved for length information (MAX: 32)
    auto len = std::vector<int>(); //is responsible to hold value of lenght in bits
    auto trueLen = 0;//decryption will decide the lenght of words
    auto bitMessage = std::vector<int>();
    for (int i = 0; i < dimension.y; i++) { //by width y
        for (int j = 0; j < dimension.x; j++) { //by length x
            auto pixel = image.getPixel(j, i);

            auto colorVALUE = 0;
            auto keyFragment = std::vector<int>(); //framnegt of the key
            auto encryptedColor = std::vector<int>(); //value which decide of if bit is changed
            for (int currColor = 0; currColor <= 2; currColor++) {// 0 -> red, 1 -> green, 2 -> blue
                if (Finished) {
                    res = BitVectorToString(bitMessage);
                    fmt::print("Decrypt finished \n");//after finishing decrypting
                    return res;
                }
                keyFragment.clear();
                encryptedColor.clear();
                switch (currColor) {
                    case 0: {
                        colorVALUE = pixel.r; //select red component
                        for (int iter = 0; iter < 8; iter++) {
                            keyFragment.push_back(KEY[iter]); //select key fragmet
                        }
                        break;
                    }
                    case 1: {
                        colorVALUE = pixel.g; //select green component
                        for (int iter = 8; iter < 16; iter++) { //select key fragmet
                            keyFragment.push_back(KEY[iter]);
                        }
                        break;
                    }
                    case 2: {
                        colorVALUE = pixel.b; //select blue component
                        for (int iter = 16; iter < 24; iter++) { //select key fragmet
                            keyFragment.push_back(KEY[iter]);
                        }
                        break;
                    }
                }
                encryptedColor = masking(getBitVector(colorVALUE, 8), keyFragment); //prepare value
                //even number of 1 -> 1
                //odd number of 1 -> 0
                if (numberCOUNT++ < 32) {
                    len.push_back(BOOLFunction(encryptedColor));

                }else  if(numberCOUNT > 32 and !retrievingLength){ //will make after reading lenght of message
                    trueLen = BitLENToInt(len)*8; //length of bits
                    retrievingLength = true;
                }
                if (retrievingLength) {
                    bitMessage.push_back(BOOLFunction(encryptedColor));
                    if(--trueLen == 0){
                        Finished = true;
                    }


                }

            }
        }
    }
    return res; //should have never been executed
}


