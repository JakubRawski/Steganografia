//
// Created by Jakub on 17.05.2024.
//

#ifndef STEGANOGRAFIA_ENGINE_H
#define STEGANOGRAFIA_ENGINE_H
#pragma once
#include<string>
#include <vector>

auto Encrypt(const std::string& path, std::string message) -> void;
auto Decrypt(const std::string& path) -> std::string;


#endif //STEGANOGRAFIA_ENGINE_H
