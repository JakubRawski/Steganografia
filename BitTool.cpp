//
// Created by Jakub on 08.06.2024.
//

#include "BitTool.h"
#include "Engine.h"

#include <filesystem>
#include <chrono>
#include <string>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <random>
#include <iostream>


//https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t
std::time_t to_time_t(std::filesystem::file_time_type fileTimeType){
    auto sctp = time_point_cast<std::chrono::system_clock::duration>
            (fileTimeType - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(sctp);
}
auto generateKEY() -> void{
    std::ofstream MyFile("keyGEN.txt");
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist2(0,1); // distribution in range [0, 1]
    unsigned int rand;
    bool ifCorr = false;
    for(int i = 0; i < 24; i++){
        rand = dist2(rng);
        if(rand == 1){
            ifCorr = true;
        }
        if((i == 7|| i ==15 || i == 23) && !ifCorr){ //prevents unusable key
            rand =1; //manually sets last bit to 1 IF previous one was only 0 (ignores every bits in encrypting/decrypting)
        }
        MyFile << rand;
        if(i == 7|| i ==15 || i == 23){ //resets every component
            ifCorr = false;
        }
    }
    MyFile.close();
}

auto getBitVector(int a, int len) -> std::vector<int>{ //make a vector of bits, len means length of vector
    std::vector<int> res = std::vector<int>();
    for(int i =0; i < len; i++){
        auto tmp = a & 1;
        res.push_back(tmp);
        a >>= 1;
    }
    std::reverse(res.begin(), res.end()); //reverse vector for accurate integer value
    return res;
}

auto BitVectorToInt(std::vector<int> vec) -> int{
    auto res = 0;
    for(int iter = 0; iter < 8; iter++){
        if(vec[iter] == 1){
            res += pow(2, 7-iter);
        }
    }
    return res;
}
auto BitLENToInt(std::vector<int> vec) -> int{
    auto res = 0;
    for(int iter = 0; iter < 32; iter++){
        if(vec[iter] == 1){
            res += pow(2, 31-iter);
        }
    }
    return res;
}

auto BitVectorToString(std::vector<int> vec) -> std::string {
    std::string res;
    std::vector<int>::iterator it; //iterator of vec
    while (!vec.empty()){
        auto numChar = 0;
        for(int iter = 0; iter < 8; iter++){
            if(vec[0] == 1){
                numChar += pow(2, 7-iter);
            }
            it = vec.begin();
            vec.erase(it);//erasing element every iteration
        }
        char character = char(numChar) ;
        res += character;
    }

    return res;
}

auto BOOLFunction(const std::vector<int>& BitVector) -> int { //return amount of 1
    auto res = 0;
    for(int a: BitVector){
        if(a == 1) res++;
    }
    return res%2;
}

auto getKeyGEN() -> std::vector<int>{
    std::vector<int> res = std::vector<int>();
    if(!std::filesystem::exists("keyGEN.txt")){
        fmt::print("generate key");
        generateKEY();
    }
    std::ifstream MyFile("keyGEN.txt",std::ios_base::in);

    char bit;
    auto x = 0;
    while (MyFile.get(bit)) {
        x = bit - '0';
        res.push_back(x);
    }
    MyFile.close();
    return res;

}
auto masking(std::vector<int> ch, std::vector<int> keyFrag) -> std::vector<int>{ //using for
    auto res = std::vector<int>(); //preparing result
    for(int i = 0; i < keyFrag.size(); i++){
        res.push_back(ch[i] & keyFrag[i]); //masking char by selecting bits base on key fragment
    }
    return res;
}
auto prepareMessage(std::string message) -> std::vector<int>{ //change message to string of bits
    auto res = std::vector<int>();  //preparing result
    for(int i = 0; i < message.size(); i++){ //iterate trough data
        auto tmp = getBitVector((int)message[i],8); //creating temporary vector of char written in bits
        res.insert(std::end(res), std::begin(tmp), std::end(tmp)); //inserting data
    }
    return res;
}

auto setComponent(std::vector<int> vectorToChange, std::vector<int> keyFrag )-> int{
    auto swapBits= 0; //swap bits counter
    auto changedBit = 0;
    for(int iter = vectorToChange.size()-1; iter >=0 ; iter--){
        if(keyFrag[iter] ==1){ //if key matches te changed value
            vectorToChange[iter] = (vectorToChange[iter]==0)?1:0; //swap bit
            changedBit = vectorToChange[iter];
            break;
        }
        swapBits++;
    }
    for(int fin = 8-swapBits; fin < vectorToChange.size(); fin++ ){ //swap bits after change to minimize color component change
        vectorToChange[fin] = (changedBit==0)?1:0;
    }
    return BitVectorToInt(vectorToChange);
}
